// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef MAPINDEX_HPP
#define MAPINDEX_HPP

#include "../common/mmo.hpp"
#include "../common/database.hpp"

#define MAX_MAPINDEX 2000

//Some definitions for the major city maps.
#define MAP_PRONTERA "prontera"
#define MAP_GEFFEN "geffen"
#define MAP_MORROC "morocc"
#define MAP_ALBERTA "alberta"
#define MAP_PAYON "payon"
#define MAP_IZLUDE "izlude"
#define MAP_ALDEBARAN "aldebaran"
#define MAP_LUTIE "xmas"
#define MAP_COMODO "comodo"
#define MAP_YUNO "yuno"
#define MAP_AMATSU "amatsu"
#define MAP_GONRYUN "gonryun"
#define MAP_UMBALA "umbala"
#define MAP_NIFLHEIM "niflheim"
#define MAP_LOUYANG "louyang"
#define MAP_JAWAII "jawaii"
#define MAP_AYOTHAYA "ayothaya"
#define MAP_EINBROCH "einbroch"
#define MAP_LIGHTHALZEN "lighthalzen"
#define MAP_EINBECH "einbech"
#define MAP_HUGEL "hugel"
#define MAP_RACHEL "rachel"
#define MAP_VEINS "veins"
#define MAP_JAIL "sec_pri"
#ifdef RENEWAL
	#define MAP_NOVICE "iz_int"
#else
	#define MAP_NOVICE "new_1-1"
#endif
#define MAP_MOSCOVIA "moscovia"
#define MAP_MIDCAMP "mid_camp"
#define MAP_MANUK "manuk"
#define MAP_SPLENDIDE "splendide"
#define MAP_BRASILIS "brasilis"
#define MAP_DICASTES "dicastes01"
#define MAP_MORA "mora"
#define MAP_DEWATA "dewata"
#define MAP_MALANGDO "malangdo"
#define MAP_MALAYA "malaya"
#define MAP_ECLAGE "eclage"
#define MAP_ECLAGE_IN "ecl_in01"
#define MAP_LASAGNA "lasagna"

const char* mapindex_getmapname(const char* string, char* output);
const char* mapindex_getmapname_ext(const char* string, char* output);

#define mapindex_name2id(mapname) mapindex_db.name2idx((mapname), __FUNCTION__)
#define mapindex_id2name(mapindex) mapindex_db.idx2name((mapindex), __FUNCTION__)



void mapindex_init(void);
void mapindex_final(void);





class MapIndexDatabase : public YamlDatabase {
private:
	int32 last_index;
	int32 max_index;
	std::unordered_map<const char*, int32> mapindex;

public:
	MapIndexDatabase() : YamlDatabase("MAP_DB", 1) {

	}

	void clear() {
		mapindex.clear();
		last_index = 0;
		max_index = 0;
	}
	const std::string getDefaultLocation();
	uint64 parseBodyNode(const YAML::Node &node);

	// Additional
	const char* get_map(int index);
	int addmap(int index, const char* name);
	void removemap(int index);
	uint16 name2idx(const char* name, const char *func);
	const char* idx2name(unsigned short id, const char *func);
	void check_mapdefault(const char *mapname);
};

extern MapIndexDatabase mapindex_db;


#endif /* MAPINDEX_HPP */
