#pragma once

#ifndef MYMAP_H

#define MYMAP_H
#include "../Game/myObject.h"
#include "../Library/gameutil.h"

class Map {
public:
	int int_map[5][29][40];
	game_framework::CMovingBitmap map1[5][29][40];
	
	void generateMap();
	void showMap(int map_stage);
	bool IsBlock(int stage, int x, int y);
};

#endif // !MYMAP_H