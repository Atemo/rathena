// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "skill_impl.hpp"

#include "map/clif.hpp"
#include "map/status.hpp"

SkillImpl::SkillImpl(e_skill skill_id){
	this->skill_id_ = skill_id;
}

e_skill SkillImpl::getSkillId() const {
	return skill_id_;
}

void SkillImpl::castendNoDamageId(block_list* src, block_list* target, uint16 skill_lv, t_tick tick, int32& flag) const {
	// no-op
}

void SkillImpl::castendDamageId(block_list* src, block_list* target, uint16 skill_lv, t_tick tick, int32& flag) const {
	// no-op
}

void SkillImpl::castendPos2(block_list* src, int32 x, int32 y, uint16 skill_lv, t_tick tick, int32& flag) const {
	// no-op
}

void SkillImpl::calculateSkillRatio(const Damage*, const block_list*, const block_list*, uint16, int32&, int32) const {
	// no-op
}

void SkillImpl::modifyHitRate(int16&, const block_list*, const block_list*, uint16) const {
	// no-op
}

void SkillImpl::applyAdditionalEffects(block_list*, block_list*, uint16, t_tick, int32, enum damage_lv) const {
	// no-op
}

void SkillImpl::applyCounterAdditionalEffects(block_list*, block_list*, uint16, t_tick, int32&) const {
	// no-op
}

void SkillImpl::modifyDamageData(Damage&, const block_list&, const block_list&, uint16) const {
	// no-op
}

void SkillImpl::modifyElement(const Damage&, const block_list&, const block_list&, uint16, int32&, int32) const {
	// no-op
}

static int32 skill_ratio_get_stat(const status_data* sstatus, int32 stat_constant) {
	switch (stat_constant) {
		case SP_STR: return sstatus->str;
		case SP_AGI: return sstatus->agi;
		case SP_VIT: return sstatus->vit;
		case SP_INT: return sstatus->int_;
		case SP_DEX: return sstatus->dex;
		case SP_LUK: return sstatus->luk;
		case SP_POW: return sstatus->pow;
		case SP_STA: return sstatus->sta;
		case SP_WIS: return sstatus->wis;
		case SP_SPL: return sstatus->spl;
		case SP_CON: return sstatus->con;
		case SP_CRT: return sstatus->crt;
		default:      return 0;
	}
}

void SkillImpl::applySkillRatioFromDB(const Damage* wd, const block_list* src, const block_list* target, uint16 skill_lv, int32& skillratio, int32 mflag) const {
	std::shared_ptr<s_skill_db> skill = skill_db.find(getSkillId());

	if (skill == nullptr || !skill->ratio_defined || skill_lv == 0 || skill_lv > MAX_SKILL_LEVEL)
		return;

	int32 idx = skill_lv - 1;
	int32 base = skill->ratio[idx];

	if (target != nullptr && !skill->ratio_race.empty()) {
		const status_data* tstatus = status_get_status_data(*target);
		auto it = skill->ratio_race.find(tstatus->race);

		if (it != skill->ratio_race.end())
			base = it->second[idx];
	}

	skillratio += -100 + base;

	if (!skill->ratio_skillmod.empty()) {
		const map_session_data* sd = BL_CAST(BL_PC, src);

		for (const auto& [mod_skill_id, arr] : skill->ratio_skillmod)
			skillratio += arr[idx] * pc_checkskill(sd, mod_skill_id);
	}

	if (!skill->ratio_statmod.empty()) {
		const status_data* sstatus = status_get_status_data(*src);

		for (const auto& [stat, multiplier] : skill->ratio_statmod)
			skillratio += multiplier * skill_ratio_get_stat(sstatus, stat);
	}

	if (skill->ratio_baselvmod)
		RE_LVL_DMOD(100);
}

StatusSkillImpl::StatusSkillImpl(e_skill skillId, bool end_if_running) : SkillImpl(skillId) {
	this->end_if_running = end_if_running;
};

void StatusSkillImpl::castendNoDamageId(block_list *src, block_list *target, uint16 skill_lv, t_tick tick, int32& flag) const
{
	sc_type type = skill_get_sc(getSkillId());

	if (type == SC_NONE) {
		return;
	}

	if (this->end_if_running) {
		status_change* tsc = status_get_sc(target);

		if (tsc != nullptr && tsc->hasSCE(type)) {
			clif_skill_nodamage(src, *target, getSkillId(), skill_lv, status_change_end(target, type));
			return;
		}
	}

	clif_skill_nodamage(src, *target, getSkillId(), skill_lv, sc_start(src, target, type, 100, skill_lv, skill_get_time(getSkillId(), skill_lv)));
}

WeaponSkillImpl::WeaponSkillImpl(e_skill skill_id) : SkillImpl(skill_id) {
}

void WeaponSkillImpl::castendDamageId(block_list* src, block_list* target, uint16 skill_lv, t_tick tick, int32& flag) const {
	skill_attack(BF_WEAPON, src, src, target, getSkillId(), skill_lv, tick, flag);
}

SkillImplRecursiveDamageSplash::SkillImplRecursiveDamageSplash(e_skill skill_id) : SkillImpl(skill_id){
}

void SkillImplRecursiveDamageSplash::castendDamageId(block_list* src, block_list* target, uint16 skill_lv, t_tick tick, int32& flag) const {
	status_change* tsc = status_get_sc(target);

	if (flag & 1){
		// Recursive invocation
		int32 sflag = skill_area_temp[0] & 0xFFF;
		std::bitset<INF2_MAX> inf2 = skill_db.find(getSkillId())->inf2;

		if (tsc && tsc->getSCE(SC_HOVERING) && inf2[INF2_IGNOREHOVERING])
			return; // Under Hovering characters are immune to select trap and ground target skills.

		if (flag & SD_LEVEL)
			sflag |= SD_LEVEL; // -1 will be used in packets instead of the skill level
		if (skill_area_temp[1] != target->id && !inf2[INF2_ISNPC])
			sflag |= SD_ANIMATION; // original target gets no animation (as well as all NPC skills)

		this->splashDamage(src, target, skill_lv, tick, sflag);
	}else{
		skill_area_temp[0] = 0;
		skill_area_temp[1] = target->id;
		skill_area_temp[2] = 0;

		this->splashSearch(src, target, skill_lv, tick, flag);
	}
}

void SkillImplRecursiveDamageSplash::castendPos2(block_list* src, int32 x, int32 y, uint16 skill_lv, t_tick tick, int32& flag) const {
	// Cast center might be relevant later (e.g. for knockback direction)
	skill_area_temp[4] = x;
	skill_area_temp[5] = y;

	int16 size = this->getSplashSearchSize(src, skill_lv);

	map_foreachinarea(skill_area_sub, src->m, x - size, y - size, x + size, y + size, this->getSplashTarget(src), src, this->getSkillId(), skill_lv, tick, flag | BCT_ENEMY | 1, skill_castend_damage_id);
}

int16 SkillImplRecursiveDamageSplash::getSearchSize(block_list* src, uint16 skill_lv) const {
	return skill_get_splash( this->getSkillId(), skill_lv );
}

int16 SkillImplRecursiveDamageSplash::getSplashSearchSize(block_list* src, uint16 skill_lv) const {
	return skill_get_splash( this->getSkillId(), skill_lv );
}

int32 SkillImplRecursiveDamageSplash::getSplashTarget(block_list* src) const {
	return BL_CHAR|BL_SKILL;
}

void SkillImplRecursiveDamageSplash::splashSearch(block_list* src, block_list* target, uint16 skill_lv, t_tick tick, int32 flag) const {
	// if skill damage should be split among targets, count them
	// SD_LEVEL -> Forced splash damage -> count targets
	if (flag & SD_LEVEL || skill_get_nk(getSkillId(), NK_SPLASHSPLIT)){
		skill_area_temp[0] = map_foreachinallrange(skill_area_sub, target, this->getSearchSize(src, skill_lv), BL_CHAR, src, getSkillId(), skill_lv, tick, BCT_ENEMY, skill_area_sub_count);
		// If there are no characters in the area, then it always counts as if there was one target
		// This happens when targetting skill units such as icewall
		skill_area_temp[0] = std::max(1, skill_area_temp[0]);
	}

	// recursive invocation of skill_castend_damage_id() with flag|1
	map_foreachinrange(skill_area_sub, target, this->getSplashSearchSize(src, skill_lv), this->getSplashTarget(src), src, getSkillId(), skill_lv, tick, flag | BCT_ENEMY | SD_SPLASH | 1, skill_castend_damage_id);
}

int64 SkillImplRecursiveDamageSplash::splashDamage(block_list* src, block_list* target, uint16 skill_lv, t_tick tick, int32 flag) const {
	return skill_attack(skill_get_type(getSkillId()), src, src, target, getSkillId(), skill_lv, tick, flag);
}
