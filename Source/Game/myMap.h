#pragma once

#ifndef MYMAP_H

#define MYMAP_H
#include "../Library/gameutil.h"

class Map {
public:
	int int_map[3][29][40];

	game_framework::CMovingBitmap map1[3][29][40];
	
	void generateMap();
	void showMap(int map_stage);
};

#endif // !MYMAP_H