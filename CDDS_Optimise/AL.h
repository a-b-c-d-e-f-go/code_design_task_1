//Contains macros and static constant variables for everything else to access.
#pragma once

#define ifv(ptr) if (ptr != nullptr) //If valid (for pointers).
#define ifn(ptr) if (ptr == nullptr) //If null (for pointers).
#define loop(var, start, end) for (int var = start; var < end; var++) //For loop preset.

//Delete array (for cleanup).
#define del_arr(arr, size)					\
ifv (arr) {									\
	loop (i, 0, size) { 					\
		ifv (arr[i]) {						\
			delete arr[i];					\
		}									\
	}										\
	delete arr;								\
	arr = nullptr;							\
}

//Specific macro for looping through the map's nodes.
#define forxy loop(x, 0, MAP_COLUMNS) { loop(y, 0, MAP_ROWS) {
#define _forxy }}

using namespace std;

//Static constant sizes assigned before running the program.
static const size_t MAP_COLUMNS = 12;
static const size_t MAP_ROWS = 12;

static const size_t SCREEN_WIDTH = 800;
static const size_t SCREEN_HEIGHT = 450;

static const size_t NODE_WIDTH = SCREEN_WIDTH / MAP_COLUMNS;
static const size_t NODE_HEIGHT = SCREEN_HEIGHT / MAP_ROWS;
static const size_t CRITTER_COUNT = 51; //Includes the destroyer (51 is 50 critters and 1 destroyer).
static const size_t MAX_VELOCITY = 80;