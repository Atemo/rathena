// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "mapindex.hpp"

#include <stdlib.h>

#include "core.hpp"
#include "mmo.hpp"
#include "showmsg.hpp"
#include "strlib.hpp"




const char* MapIndexDatabase::get_map(int index) {
	for (const auto &it : this->mapindex) {
		if (it.second == index)
			return it.first;
	}
	return nullptr;
}

/// Retrieves the map name from 'string' (removing .gat extension if present).
/// Result gets placed either into 'buf' or in a static local buffer.
const char* mapindex_getmapname(const char* string, char* output) {
	static char buf[MAP_NAME_LENGTH];
	char* dest = (output != NULL) ? output : buf;

	size_t len = strnlen(string, MAP_NAME_LENGTH_EXT);
	if (len == MAP_NAME_LENGTH_EXT) {
		ShowWarning("(mapindex_normalize_name) Map name '%*s' is too long!\n", 2*MAP_NAME_LENGTH_EXT, string);
		len--;
	}
	if (len >= 4 && stricmp(&string[len-4], ".gat") == 0)
		len -= 4; // strip .gat extension

	len = zmin(len, MAP_NAME_LENGTH-1);
	safestrncpy(dest, string, len+1);
	memset(&dest[len], '\0', MAP_NAME_LENGTH-len);

	return dest;
}

/// Retrieves the map name from 'string' (adding .gat extension if not already present).
/// Result gets placed either into 'buf' or in a static local buffer.
const char* mapindex_getmapname_ext(const char* string, char* output) {
	static char buf[MAP_NAME_LENGTH_EXT];
	char* dest = (output != NULL) ? output : buf;

	size_t len;

	strcpy(buf,string);
	sscanf(string,"%*[^#]%*[#]%15s",buf);

	len = safestrnlen(buf, MAP_NAME_LENGTH);

	if (len == MAP_NAME_LENGTH) {
		ShowWarning("(mapindex_normalize_name) Map name '%*s' is too long!\n", 2*MAP_NAME_LENGTH, buf);
		len--;
	}
	safestrncpy(dest, buf, len+1);

	if (len < 4 || stricmp(&dest[len-4], ".gat") != 0) {
		strcpy(&dest[len], ".gat");
		len += 4; // add .gat extension
	}

	memset(&dest[len], '\0', MAP_NAME_LENGTH_EXT-len);

	return dest;
}

/// Adds a map to the specified index
/// Returns 1 if successful, 0 oherwise
int MapIndexDatabase::addmap(int index, const char* name) {
	char map_name[MAP_NAME_LENGTH];

	if (index == -1 && this->mapindex.size() < MAX_MAPINDEX) // auto increment index
		index = this->max_index;

	if (index <= 0) {
		ShowError("(MapIndexDatabase::addmap) Map index (%d) for \"%s\" out of range.\n", index, name);
		return 0;
	}

	if (this->mapindex.size() >= MAX_MAPINDEX) {
		ShowError("(MapIndexDatabase::addmap) Too many index (%d) defined, failed to add \"%s\" (max size is %d)\n", index, name, MAX_MAPINDEX);
		return 0;
	}

	mapindex_getmapname(name, map_name);

	if (map_name[0] == '\0') {
		ShowError("(MapIndexDatabase::addmap) Cannot add maps with no name.\n");
		return 0;
	}

	if (strlen(map_name) >= MAP_NAME_LENGTH) {
		ShowError("(MapIndexDatabase::addmap) Map name %s is too long. Maps are limited to %d characters.\n", map_name, MAP_NAME_LENGTH);
		return 0;
	}

	const char* previous_name = this->get_map(index);
	if (previous_name != nullptr) {
		ShowWarning("(MapIndexDatabase::addmap) Overriding index %d: map \"%s\" -> \"%s\"\n", index, previous_name, map_name);
		this->mapindex.erase(previous_name);
	}

	this->mapindex[map_name] = index;

	if (this->max_index <= index)
		this->max_index = index+1;

	return index;
}

uint16 MapIndexDatabase::name2idx(const char* name, const char *func) {
	char map_name[MAP_NAME_LENGTH];
	mapindex_getmapname(name, map_name);

	if (this->mapindex.count(map_name) > 0)
		return this->mapindex[map_name];

	if (func)
		ShowDebug("(%s) mapindex_name2id: Map \"%s\" not found in index list!\n", func, map_name);
	return 0;
}

const char* MapIndexDatabase::idx2name(uint16 id, const char *func) {
	const char* name = this->get_map(id);
	if (id >= this->max_index || name == nullptr) {
		ShowDebug("(%s) mapindex_id2name: Requested name for non-existant map index [%d] in cache.\n", func, id);
		return "\0"; // dummy empty string so that the callee doesn't crash
	}
	return name;
}

/**
 * Check default map (only triggered once by char-server)
 * @param mapname
 **/
void MapIndexDatabase::check_mapdefault(const char *mapname) {
	mapname = mapindex_getmapname(mapname, NULL);
	if (this->mapindex.count(mapname) > 0) {
		ShowError("mapindex_init: Default map '%s' not found in cache! Please change in (by default in) char_athena.conf!\n", mapname);
	}
}

void MapIndexDatabase::removemap(int index) {
	const char* name = this->get_map(index);
	if (name != nullptr)
		this->mapindex.erase(name);
}

const std::string MapIndexDatabase::getDefaultLocation() {
	return std::string(db_path) + "/map_index.yml";
}

/**
 * Reads and parses an entry from the map_index.
 * @param node: YAML node containing the entry.
 * @return count of successfully parsed rows
 */
uint64 MapIndexDatabase::parseBodyNode(const YAML::Node &node) {
	std::string map_name;

	if (!this->asString(node, "Map", map_name))
		return 0;

	int32 index;

	if (this->nodeExists(node, "Index")) {
		if (!this->asInt32(node, "Id", index))
			return 0;

		this->last_index = index;
	} else {
		index = this->last_index++;	// inccrement from the last index given by the user
	}

	return this->addmap(index, map_name.c_str()) > 0;
}

void mapindex_init(void) {
	if (!mapindex_db.load())
		exit(EXIT_FAILURE); //Server can't really run without this file.
}
	
void mapindex_final(void) {
	mapindex_db.clear();
}
