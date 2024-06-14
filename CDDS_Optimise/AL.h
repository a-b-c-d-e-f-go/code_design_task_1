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


// All of the static variables that determine the size/attributes/performance of the program before runtime.

//How much the map is partitioned/subdivided. Keep in mind these are both used to determine the size of a 2D array, so even small changes affect memory usage significantly.
static const size_t MAP_COLUMNS = 12;
static const size_t MAP_ROWS = 12;

//Width and height of the screen - used by the map to size the nodes and by raylib to initialize the window.
static const size_t SCREEN_WIDTH = 800;
static const size_t SCREEN_HEIGHT = 450;

//Width and height of individual nodes in the map - calculated based on screen size / how much it is subdivided.
static const size_t NODE_WIDTH = SCREEN_WIDTH / MAP_COLUMNS;
static const size_t NODE_HEIGHT = SCREEN_HEIGHT / MAP_ROWS;

static const size_t CRITTER_COUNT = 51; //Includes the destroyer (51 is 50 critters and 1 destroyer).
static const size_t MAX_VELOCITY = 80; //The speed critters move at.