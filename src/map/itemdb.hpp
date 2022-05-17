// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef ITEMDB_HPP
#define ITEMDB_HPP

#include <map>
#include <vector>

#include "../common/database.hpp"
#include "../common/db.hpp"
#include "../common/malloc.hpp"
#include "../common/mmo.hpp" // ITEM_NAME_LENGTH

#include "script.hpp"
#include "status.hpp"

enum e_ammo_type : uint8;

///Use apple for unknown items.
const t_itemid UNKNOWN_ITEM_ID = 512;
/// The maximum number of item delays
#define MAX_ITEMDELAYS	10
///Designed for search functions, species max number of matches to display.
#define MAX_SEARCH	5

#define MAX_ROULETTE_LEVEL 7 /** client-defined value **/
#define MAX_ROULETTE_COLUMNS 9 /** client-defined value **/

const t_itemid CARD0_FORGE = 0x00FF;
const t_itemid CARD0_CREATE = 0x00FE;
const t_itemid CARD0_PET = 0x0100;

///Marks if the card0 given is "special" (non-item id used to mark pets/created items. [Skotlex]
#define itemdb_isspecial(i) (i == CARD0_FORGE || i == CARD0_CREATE || i == CARD0_PET)

///Enum of item id (for hardcoded purpose)
enum item_itemid : t_itemid
{
	ITEMID_DUMMY						= 499,
	ITEMID_RED_POTION					= 501,
	ITEMID_YELLOW_POTION				= 503,
	ITEMID_WHITE_POTION					= 504,
	ITEMID_BLUE_POTION					= 505,
	ITEMID_APPLE						= 512,
	ITEMID_HOLY_WATER					= 523,
	ITEMID_PUMPKIN						= 535,
	ITEMID_RED_SLIM_POTION				= 545,
	ITEMID_YELLOW_SLIM_POTION			= 546,
	ITEMID_WHITE_SLIM_POTION			= 547,
	ITEMID_WING_OF_FLY					= 601,
	ITEMID_WING_OF_BUTTERFLY			= 602,
	ITEMID_ANODYNE						= 605,
	ITEMID_ALOEBERA						= 606,
	ITEMID_MAGNIFIER					= 611,
	ITEMID_POISON_BOTTLE				= 678,
	ITEMID_EMPTY_BOTTLE					= 713,
	ITEMID_EMPERIUM						= 714,
	ITEMID_RED_GEMSTONE					= 716,
	ITEMID_BLUE_GEMSTONE				= 717,
	ITEMID_ORIDECON_STONE				= 756,
	ITEMID_ALCOHOL						= 970,
	ITEMID_ORIDECON						= 984,
	ITEMID_ANVIL						= 986,
	ITEMID_ORIDECON_ANVIL				= 987,
	ITEMID_GOLDEN_ANVIL					= 988,
	ITEMID_EMPERIUM_ANVIL				= 989,
	ITEMID_BLOODY_RED					= 990,
	ITEMID_CRYSTAL_BLUE					= 991,
	ITEMID_WIND_OF_VERDURE				= 992,
	ITEMID_YELLOW_LIVE					= 993,
	ITEMID_FLAME_HEART					= 994,
	ITEMID_MISTIC_FROZEN				= 995,
	ITEMID_ROUGH_WIND					= 996,
	ITEMID_GREAT_NATURE					= 997,
	ITEMID_IRON							= 998,
	ITEMID_STEEL						= 999,
	ITEMID_STAR_CRUMB					= 1000,
	ITEMID_IRON_ORE						= 1002,
	ITEMID_PHRACON						= 1010,
	ITEMID_EMVERETARCON					= 1011,
	ITEMID_TRAP							= 1065,
	ITEMID_ANGRA_MANYU					= 1599,
	ITEMID_PAINT_BRUSH					= 6122,
	ITEMID_MAGIC_GEAR_FUEL				= 6146,
	ITEMID_NEW_INSURANCE				= 6413,
	ITEMID_STRANGE_EMBRYO				= 6415,
	ITEMID_BLACKSMITH_BLESSING			= 6635,
	ITEMID_STONE						= 7049,
	ITEMID_FIRE_BOTTLE					= 7135,
	ITEMID_ACID_BOTTLE					= 7136,
	ITEMID_MAN_EATER_BOTTLE				= 7137,
	ITEMID_MINI_BOTTLE					= 7138,
	ITEMID_COATING_BOTTLE				= 7139,
	ITEMID_FRAGMENT_OF_CRYSTAL			= 7321,
	ITEMID_SKULL_						= 7420,
	ITEMID_TRAP_ALLOY					= 7940,
	ITEMID_COOKIE_BAT					= 11605,
	ITEMID_MERCENARY_RED_POTION			= 12184,
	ITEMID_MERCENARY_BLUE_POTION		= 12185,
	ITEMID_GIANT_FLY_WING				= 12212,
	ITEMID_NEURALIZER					= 12213,
	ITEMID_M_CENTER_POTION				= 12241,
	ITEMID_M_AWAKENING_POTION			= 12242,
	ITEMID_M_BERSERK_POTION				= 12243,
	ITEMID_N_FLY_WING					= 12323,
	ITEMID_N_BUTTERFLY_WING				= 12324,
	ITEMID_NOVICE_MAGNIFIER				= 12325,
	ITEMID_ANCILLA						= 12333,
	ITEMID_DUN_TELE_SCROLL3				= 12352,
	ITEMID_REINS_OF_MOUNT				= 12622,
	ITEMID_NOBLE_NAMEPLATE				= 12705,
	ITEMID_SILVER_BULLET				= 13201,
	ITEMID_PURIFICATION_BULLET			= 13220,
	ITEMID_SILVER_BULLET_				= 13221,
	ITEMID_DUN_TELE_SCROLL1				= 14527,
	ITEMID_DUN_TELE_SCROLL2				= 14581,
	ITEMID_WOB_RUNE						= 14582,
	ITEMID_WOB_SCHWALTZ					= 14583,
	ITEMID_WOB_RACHEL					= 14584,
	ITEMID_WOB_LOCAL					= 14585,
	ITEMID_SIEGE_TELEPORT_SCROLL		= 14591,
	ITEMID_INVENTORY_EX_EVT				= 25791,
	ITEMID_INVENTORY_EX_DIS				= 25792,
	ITEMID_INVENTORY_EX					= 25793,
	ITEMID_WL_MB_SG						= 100065,
	ITEMID_HOMUNCULUS_SUPPLEMENT		= 100371,
};

///Rune Knight
enum rune_item_list : t_itemid
{
	ITEMID_NAUTHIZ		= 12725,
	ITEMID_RAIDO,
	ITEMID_BERKANA,
	ITEMID_ISA,
	ITEMID_OTHILA,
	ITEMID_URUZ,
	ITEMID_THURISAZ,
	ITEMID_WYRD,
	ITEMID_HAGALAZ,
	ITEMID_LUX_ANIMA	= 22540,
};

///Mechanic
enum mechanic_item_list : t_itemid
{
	ITEMID_ACCELERATOR				= 2800,
	ITEMID_SUICIDAL_DEVICE				= 2802,
	ITEMID_SHAPE_SHIFTER,
	ITEMID_COOLING_DEVICE,
	ITEMID_MAGNETIC_FIELD_GENERATOR,
	ITEMID_BARRIER_BUILDER,
	ITEMID_REPAIR_KIT,
	ITEMID_CAMOUFLAGE_GENERATOR,
	ITEMID_HIGH_QUALITY_COOLER,
	ITEMID_SPECIAL_COOLER,
	ITEMID_SCARLET_PTS				= 6360,
	ITEMID_INDIGO_PTS,
	ITEMID_YELLOW_WISH_PTS,
	ITEMID_LIME_GREEN_PTS,
	ITEMID_REPAIR_A              = 12392,
	ITEMID_REPAIR_B,
	ITEMID_REPAIR_C,
};

///Genetic
enum genetic_item_list : t_itemid
{
	ITEMID_SEED_OF_HORNY_PLANT			= 6210,
	ITEMID_BLOODSUCK_PLANT_SEED,
	ITEMID_BOMB_MUSHROOM_SPORE,
	ITEMID_HP_INCREASE_POTION_SMALL		= 12422,
	ITEMID_HP_INCREASE_POTION_MEDIUM,
	ITEMID_HP_INCREASE_POTION_LARGE,
	ITEMID_SP_INCREASE_POTION_SMALL,
	ITEMID_SP_INCREASE_POTION_MEDIUM,
	ITEMID_SP_INCREASE_POTION_LARGE,
	ITEMID_CONCENTRATED_WHITE_POTION_Z,
	ITEMID_SAVAGE_FULL_ROAST,
	ITEMID_COCKTAIL_WARG_BLOOD,
	ITEMID_MINOR_STEW,
	ITEMID_SIROMA_ICED_TEA,
	ITEMID_DROSERA_HERB_SALAD,
	ITEMID_PETITE_TAIL_NOODLES,
	ITEMID_BLACK_MASS,
	ITEMID_VITATA500,
	ITEMID_CONCENTRATED_CEROMAIN_SOUP,
	ITEMID_CURE_FREE					= 12475,
	ITEMID_APPLE_BOMB					= 13260,
	ITEMID_COCONUT_BOMB,
	ITEMID_MELON_BOMB,
	ITEMID_PINEAPPLE_BOMB,
	ITEMID_BANANA_BOMB,
	ITEMID_BLACK_LUMP,
	ITEMID_BLACK_HARD_LUMP,
	ITEMID_VERY_HARD_LUMP,
	ITEMID_MYSTERIOUS_POWDER,
	ITEMID_HP_INC_POTS_TO_THROW			= 13275,
	ITEMID_HP_INC_POTM_TO_THROW,
	ITEMID_HP_INC_POTL_TO_THROW,
	ITEMID_SP_INC_POTS_TO_THROW,
	ITEMID_SP_INC_POTM_TO_THROW,
	ITEMID_SP_INC_POTL_TO_THROW,
};

///Guillotine Cross
enum poison_item_list : t_itemid
{
	ITEMID_PARALYSE = 12717,
	ITEMID_LEECHESEND,
	ITEMID_OBLIVIONCURSE,
	ITEMID_DEATHHURT,
	ITEMID_TOXIN,
	ITEMID_PYREXIA,
	ITEMID_MAGICMUSHROOM,
	ITEMID_VENOMBLEED,
};

///Item job
enum e_item_job : uint16
{
	ITEMJ_NONE        = 0x00,
	ITEMJ_NORMAL      = 0x01,
	ITEMJ_UPPER       = 0x02,
	ITEMJ_BABY        = 0x04,
	ITEMJ_THIRD       = 0x08,
	ITEMJ_THIRD_UPPER = 0x10,
	ITEMJ_THIRD_BABY  = 0x20,
	ITEMJ_FOURTH      = 0x40,
	ITEMJ_MAX         = 0xFF,

	ITEMJ_ALL_UPPER = ITEMJ_UPPER | ITEMJ_THIRD_UPPER | ITEMJ_FOURTH,
	ITEMJ_ALL_BABY = ITEMJ_BABY | ITEMJ_THIRD_BABY,
	ITEMJ_ALL_THIRD = ITEMJ_THIRD | ITEMJ_THIRD_UPPER | ITEMJ_THIRD_BABY,

#ifdef RENEWAL
	ITEMJ_ALL = ITEMJ_NORMAL | ITEMJ_UPPER | ITEMJ_BABY | ITEMJ_THIRD | ITEMJ_THIRD_UPPER | ITEMJ_THIRD_BABY | ITEMJ_FOURTH,
#else
	ITEMJ_ALL = ITEMJ_NORMAL | ITEMJ_UPPER | ITEMJ_BABY,
#endif
};

#define AMMO_TYPE_ALL ((1<<MAX_AMMO_TYPE)-1)

enum e_random_item_group {
	IG_BOMB = 42,
	IG_CASH_FOOD = 72,
	IG_ELEMENT = 114,
	IG_FINDINGORE = 147,
	IG_GEMSTONE = 174,
	IG_MERCENARY = 276,
	IG_POISON = 342,
	IG_POTION = 344,
	IG_PRIVATE_AIRSHIP = 345,
	IG_THROWABLE = 452,
	IG_TOKEN_OF_SIEGFRIED = 454,
};

/// Enum for bound/sell restricted selling
enum e_itemshop_restrictions {
	ISR_NONE = 0x0,
	ISR_BOUND = 0x1,
	ISR_SELLABLE = 0x2,
	ISR_BOUND_SELLABLE = 0x4,
	ISR_BOUND_GUILDLEADER_ONLY = 0x8,
};

/// Enum for item drop effects
enum e_item_drop_effect : uint16 {
	DROPEFFECT_NONE = 0,
	DROPEFFECT_CLIENT,
#if PACKETVER < 20200304
	DROPEFFECT_WHITE_PILLAR,
#endif
	DROPEFFECT_BLUE_PILLAR,
	DROPEFFECT_YELLOW_PILLAR,
	DROPEFFECT_PURPLE_PILLAR,
#if PACKETVER < 20200304
	DROPEFFECT_ORANGE_PILLAR,
#else
	DROPEFFECT_GREEN_PILLAR,
#endif
#if PACKETVER >= 20200304
	DROPEFFECT_RED_PILLAR,
#endif
	DROPEFFECT_MAX,
#if PACKETVER >= 20200304
	// White was removed in 2020-03-04
	DROPEFFECT_WHITE_PILLAR,
	// Orange was replaced by green in 2020-03-04
	DROPEFFECT_ORANGE_PILLAR,
#else
	// Not supported before 2020-03-04
	DROPEFFECT_GREEN_PILLAR,
	DROPEFFECT_RED_PILLAR,
#endif
};

/// Enum for items with delayed consumption
enum e_delay_consume : uint8 {
	DELAYCONSUME_NONE = 0x0,
	DELAYCONSUME_TEMP = 0x1, // Items that are not consumed immediately upon double-click
	DELAYCONSUME_NOCONSUME = 0x2, // Items that are not removed upon double-click
};

/// Item combo struct
struct s_item_combo {
	std::vector<t_itemid> nameid;
	script_code *script;
	uint16 id;

	~s_item_combo() {
		if (this->script) {
			script_free_code(this->script);
			this->script = nullptr;
		}

		this->nameid.clear();
	}
};

class ComboDatabase : public TypesafeYamlDatabase<uint16, s_item_combo> {
private:
	uint16 combo_num;
	uint16 find_combo_id( const std::vector<t_itemid>& items );

public:
	ComboDatabase() : TypesafeYamlDatabase("COMBO_DB", 1) {

	}

	void clear() override{
		TypesafeYamlDatabase::clear();
		this->combo_num = 0;
	}
	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
	void loadingFinished() override;
};

extern ComboDatabase itemdb_combo;

// Struct for item random option [Secret]
struct s_random_opt_data
{
	uint16 id;
	std::string name;
	script_code *script;

	~s_random_opt_data() {
		if (script)
			script_free_code(script);
	}
};

/// Struct for random option group entry
struct s_random_opt_group_entry {
	uint16 id;
	int16 min_value, max_value;
	int8 param;
	uint16 chance;
};

/// Struct for Random Option Group
struct s_random_opt_group {
	uint16 id;
	std::string name;
	std::map<uint16, std::vector<std::shared_ptr<s_random_opt_group_entry>>> slots;
	uint16 max_random;
	std::vector<std::shared_ptr<s_random_opt_group_entry>> random_options;

public:
	void apply( struct item& item );
};

class RandomOptionDatabase : public TypesafeYamlDatabase<uint16, s_random_opt_data> {
public:
	RandomOptionDatabase() : TypesafeYamlDatabase("RANDOM_OPTION_DB", 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
	void loadingFinished() override;

	// Additional
	bool option_exists(std::string name);
	bool option_get_id(std::string name, uint16 &id);
};

extern RandomOptionDatabase random_option_db;

class RandomOptionGroupDatabase : public TypesafeYamlDatabase<uint16, s_random_opt_group> {
public:
	RandomOptionGroupDatabase() : TypesafeYamlDatabase("RANDOM_OPTION_GROUP", 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;

	// Additional
	bool add_option(const ryml::NodeRef& node, std::shared_ptr<s_random_opt_group_entry> &entry);
	bool option_exists(std::string name);
	bool option_get_id(std::string name, uint16 &id);
};

extern RandomOptionGroupDatabase random_option_group;

/// Struct of item group entry
struct s_item_group_entry
{
	t_itemid nameid; /// Item ID
	uint16 rate;
	uint16 duration, /// Duration if item as rental item (in minutes)
		amount; /// Amount of item will be obtained
	bool isAnnounced, /// Broadcast if player get this item
		GUID, /// Gives Unique ID for items in each box opened
		isStacked, /// Whether stackable items are given stacked
		isNamed; /// Named the item (if possible)
	uint8 bound; /// Makes the item as bound item (according to bound type)
	std::shared_ptr<s_random_opt_group> randomOptionGroup;
	uint16 refineMinimum;
	uint16 refineMaximum;
};

/// Struct of random group
struct s_item_group_random
{
	uint32 total_rate;
	std::unordered_map<t_itemid, std::shared_ptr<s_item_group_entry>> data; /// item ID, s_item_group_entry

	std::shared_ptr<s_item_group_entry> get_random_itemsubgroup();
};

/// Struct of item group that will be used for db
struct s_item_group_db
{
	uint16 id; /// Item Group ID
	std::string name;
	std::unordered_map<uint16, std::shared_ptr<s_item_group_random>> random;	/// group ID, s_item_group_random
};

/// Struct of Roulette db
struct s_roulette_db {
	t_itemid *nameid[MAX_ROULETTE_LEVEL]; /// Item ID
	unsigned short *qty[MAX_ROULETTE_LEVEL]; /// Amount of Item ID
	int *flag[MAX_ROULETTE_LEVEL]; /// Whether the item is for loss or win
	int items[MAX_ROULETTE_LEVEL]; /// Number of items in the list for each
};
extern struct s_roulette_db rd;

///Main item data struct
struct item_data
{
	t_itemid nameid;
	std::string name, ename;

	uint32 value_buy;
	uint32 value_sell;
	item_types type;
	uint8 subtype;
	int maxchance; //For logs, for external game info, for scripts: Max drop chance of this item (e.g. 0.01% , etc.. if it = 0, then monsters don't drop it, -1 denotes items sold in shops only) [Lupus]
	uint8 sex;
	uint32 equip;
	uint32 weight;
	uint32 atk;
	uint32 def;
	uint16 range;
	uint16 slots;
	uint32 look;
	uint16 elv;
	uint16 weapon_level;
	uint16 armor_level;
	t_itemid view_id;
	uint16 elvmax; ///< Maximum level for this item
#ifdef RENEWAL
	uint32 matk;
#endif

//Lupus: I rearranged order of these fields due to compatibility with ITEMINFO script command
//		some script commands should be revised as well...
	uint64 class_base[3];	//Specifies if the base can wear this item (split in 3 indexes per type: 1-1, 2-1, 2-2)
	uint16 class_upper; //Specifies if the class-type can equip it (See e_item_job)
	struct {
		int chance;
		int id;
	} mob[MAX_SEARCH]; //Holds the mobs that have the highest drop rate for this item. [Skotlex]
	struct script_code *script;	//Default script for everything.
	struct script_code *equip_script;	//Script executed once when equipping.
	struct script_code *unequip_script;//Script executed once when unequipping.
	struct {
		unsigned available : 1;
		uint32 no_equip;
		unsigned no_refine : 1;	// [celest]
		unsigned delay_consume;	// [Skotlex]
		struct {
			bool drop, trade, trade_partner, sell, cart, storage, guild_storage, mail, auction;
		} trade_restriction;	//Item restrictions mask [Skotlex]
		unsigned autoequip: 1;
		bool buyingstore;
		bool dead_branch; // As dead branch item. Logged at `branchlog` table and cannot be used at 'nobranch' mapflag [Cydh]
		bool group; // As item group container [Cydh]
		unsigned guid : 1; // This item always be attached with GUID and make it as bound item! [Cydh]
		bool broadcast; ///< Will be broadcasted if someone obtain the item [Cydh]
		bool bindOnEquip; ///< Set item as bound when equipped
		e_item_drop_effect dropEffect; ///< Drop Effect Mode
	} flag;
	struct {// item stacking limitation
		uint16 amount;
		bool inventory, cart, storage, guild_storage;
	} stack;
	struct {
		uint16 override;
		bool sitting;
	} item_usage;
	short gm_lv_trade_override;	//GM-level to override trade_restriction
	std::vector<std::shared_ptr<s_item_combo>> combos;
	struct {
		uint32 duration;
		sc_type sc; ///< Use delay group if any instead using player's item_delay data [Cydh]
	} delay;

	~item_data() {
		if (this->script){
			script_free_code(this->script);
			this->script = nullptr;
		}

		if (this->equip_script){
			script_free_code(this->equip_script);
			this->equip_script = nullptr;
		}

		if (this->unequip_script){
			script_free_code(this->unequip_script);
			this->unequip_script = nullptr;
		}

		this->combos.clear();
	}

	bool isStackable();
	int inventorySlotNeeded(int quantity);
};

class ItemDatabase : public TypesafeCachedYamlDatabase<t_itemid, item_data> {
private:
	std::unordered_map<std::string, std::shared_ptr<item_data>> nameToItemDataMap;
	std::unordered_map<std::string, std::shared_ptr<item_data>> aegisNameToItemDataMap;

	e_sex defaultGender( const ryml::NodeRef& node, std::shared_ptr<item_data> id );

public:
	ItemDatabase() : TypesafeCachedYamlDatabase("ITEM_DB", 2, 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
	void loadingFinished() override;
	void clear() override{
		TypesafeCachedYamlDatabase::clear();

		this->nameToItemDataMap.clear();
		this->aegisNameToItemDataMap.clear();
	}

	// Additional
	std::shared_ptr<item_data> searchname( const char* name );
	std::shared_ptr<item_data> search_aegisname( const char *name );
};

extern ItemDatabase item_db;

class ItemGroupDatabase : public TypesafeCachedYamlDatabase<uint16, s_item_group_db> {
public:
	ItemGroupDatabase() : TypesafeCachedYamlDatabase("ITEM_GROUP_DB", 2, 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
	void loadingFinished() override;

	// Additional
	bool group_exists(std::string name);
	bool item_exists(uint16 group_id, t_itemid nameid);
	int16 item_exists_pc(map_session_data *sd, uint16 group_id);
	t_itemid get_random_item_id(uint16 group_id, uint8 sub_group);
	std::shared_ptr<s_item_group_entry> get_random_entry(uint16 group_id, uint8 sub_group);
	uint8 pc_get_itemgroup(uint16 group_id, bool identify, map_session_data *sd);
};

extern ItemGroupDatabase itemdb_group;

struct s_laphine_synthesis_requirement{
	t_itemid item_id;
	uint16 amount;
};

struct s_laphine_synthesis{
	t_itemid item_id;
	uint16 minimumRefine;
	uint16 maximumRefine;
	uint16 requiredRequirements;
	std::unordered_map<t_itemid, std::shared_ptr<s_laphine_synthesis_requirement>> requirements;
	uint16 rewardGroupId;
};

class LaphineSynthesisDatabase : public TypesafeYamlDatabase<t_itemid, s_laphine_synthesis>{
public:
	LaphineSynthesisDatabase() : TypesafeYamlDatabase( "LAPHINE_SYNTHESIS_DB", 1 ){

	}

	const std::string getDefaultLocation();
	uint64 parseBodyNode( const ryml::NodeRef& node );
};

extern LaphineSynthesisDatabase laphine_synthesis_db;

struct s_laphine_upgrade{
	t_itemid item_id;
	std::vector<t_itemid> target_item_ids;
	uint16 minimumRefine;
	uint16 maximumRefine;
	uint16 requiredRandomOptions;
	bool cardsAllowed;
	std::shared_ptr<s_random_opt_group> randomOptionGroup;
	uint16 resultRefine;
	uint16 resultRefineMinimum;
	uint16 resultRefineMaximum;
};

class LaphineUpgradeDatabase : public TypesafeYamlDatabase<t_itemid, s_laphine_upgrade>{
public:
	LaphineUpgradeDatabase() : TypesafeYamlDatabase( "LAPHINE_UPGRADE_DB", 1 ){

	}

	const std::string getDefaultLocation();
	uint64 parseBodyNode( const ryml::NodeRef& node );
};

extern LaphineUpgradeDatabase laphine_upgrade_db;

int itemdb_searchname_array(struct item_data** data, int size, const char *str);
struct item_data* itemdb_search(t_itemid nameid);
struct item_data* itemdb_exists(t_itemid nameid);
#define itemdb_name(n) itemdb_search(n)->name.c_str()
#define itemdb_ename(n) itemdb_search(n)->ename.c_str()
#define itemdb_type(n) itemdb_search(n)->type
#define itemdb_subtype(n) itemdb_search(n)->subtype
#define itemdb_atk(n) itemdb_search(n)->atk
#define itemdb_def(n) itemdb_search(n)->def
#define itemdb_look(n) itemdb_search(n)->look
#define itemdb_weight(n) itemdb_search(n)->weight
#define itemdb_equip(n) itemdb_search(n)->equip
#define itemdb_usescript(n) itemdb_search(n)->script
#define itemdb_equipscript(n) itemdb_search(n)->script
#define itemdb_wlv(n) itemdb_search(n)->weapon_level
#define itemdb_range(n) itemdb_search(n)->range
#define itemdb_slots(n) itemdb_search(n)->slots
#define itemdb_available(n) (itemdb_search(n)->flag.available)
#define itemdb_traderight(n) (itemdb_search(n)->flag.trade_restriction)
#define itemdb_viewid(n) (itemdb_search(n)->view_id)
#define itemdb_autoequip(n) (itemdb_search(n)->flag.autoequip)
#define itemdb_dropeffect(n) (itemdb_search(n)->flag.dropEffect)
const char* itemdb_typename(enum item_types type);
const char *itemdb_typename_ammo (e_ammo_type ammo);

#define itemdb_value_buy(n) itemdb_search(n)->value_buy
#define itemdb_value_sell(n) itemdb_search(n)->value_sell
#define itemdb_canrefine(n) (!itemdb_search(n)->flag.no_refine)
//Item trade restrictions [Skotlex]
bool itemdb_isdropable_sub(struct item_data *itd, int gmlv, int unused);
bool itemdb_cantrade_sub(struct item_data *itd, int gmlv, int gmlv2);
bool itemdb_canpartnertrade_sub(struct item_data *itd, int gmlv, int gmlv2);
bool itemdb_cansell_sub(struct item_data *itd, int gmlv, int unused);
bool itemdb_cancartstore_sub(struct item_data *itd, int gmlv, int unused);
bool itemdb_canstore_sub(struct item_data *itd, int gmlv, int unused);
bool itemdb_canguildstore_sub(struct item_data *itd, int gmlv, int unused);
bool itemdb_canmail_sub(struct item_data *itd, int gmlv, int unused);
bool itemdb_canauction_sub(struct item_data *itd, int gmlv, int unused);
bool itemdb_isrestricted(struct item* item, int gmlv, int gmlv2, bool (*func)(struct item_data*, int, int));
bool itemdb_ishatched_egg(struct item* item);
#define itemdb_isdropable(item, gmlv) itemdb_isrestricted(item, gmlv, 0, itemdb_isdropable_sub)
#define itemdb_cantrade(item, gmlv, gmlv2) itemdb_isrestricted(item, gmlv, gmlv2, itemdb_cantrade_sub)
#define itemdb_canpartnertrade(item, gmlv, gmlv2) itemdb_isrestricted(item, gmlv, gmlv2, itemdb_canpartnertrade_sub)
#define itemdb_cansell(item, gmlv) itemdb_isrestricted(item, gmlv, 0, itemdb_cansell_sub)
#define itemdb_cancartstore(item, gmlv)  itemdb_isrestricted(item, gmlv, 0, itemdb_cancartstore_sub)
#define itemdb_canstore(item, gmlv) itemdb_isrestricted(item, gmlv, 0, itemdb_canstore_sub)
#define itemdb_canguildstore(item, gmlv) itemdb_isrestricted(item , gmlv, 0, itemdb_canguildstore_sub)
#define itemdb_canmail(item, gmlv) itemdb_isrestricted(item , gmlv, 0, itemdb_canmail_sub)
#define itemdb_canauction(item, gmlv) itemdb_isrestricted(item , gmlv, 0, itemdb_canauction_sub)

bool itemdb_isequip2(struct item_data *id);
#define itemdb_isequip(nameid) itemdb_isequip2(itemdb_search(nameid))
char itemdb_isidentified(t_itemid nameid);
bool itemdb_isstackable2(struct item_data *id);
#define itemdb_isstackable(nameid) itemdb_isstackable2(itemdb_search(nameid))
bool itemdb_isNoEquip(struct item_data *id, uint16 m);

bool itemdb_parse_roulette_db(void);

void itemdb_reload(void);

void do_final_itemdb(void);
void do_init_itemdb(void);

#endif /* ITEMDB_HPP */
