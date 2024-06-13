#pragma once
#include "Critter.h"
#include <vector>

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

//Specific macros.

#define forxy loop(x, 0, MAP_COLUMNS) { loop(y, 0, MAP_ROWS) {
#define _forxy }}

#define n(x, y, c) nodes[x][y]->Add(c);
#define nodes_3x3_add(x, y, c) n(x - 1, y - 1, c) n(x, y - 1, c) n(x + 1, y - 1, c) n(x - 1, y, c) n(x, y, c) n(x + 1, y, c) n(x - 1, y + 1, c) n(x, y + 1, c) n(x + 1, y + 1, c)

using namespace std;

//Static constant sizes assigned before running the program.
static const size_t MAP_COLUMNS = 6;
static const size_t MAP_ROWS = 6;

static const size_t SCREEN_WIDTH = 800;
static const size_t SCREEN_HEIGHT = 450;

static const size_t NODE_WIDTH = SCREEN_WIDTH / MAP_COLUMNS;
static const size_t NODE_HEIGHT = SCREEN_HEIGHT / MAP_ROWS;
static const size_t NODE_CAPACITY = 25;
static const size_t CRITTER_COUNT = NODE_CAPACITY * 2;
static const size_t MAX_VELOCITY = 80;