#pragma once

#ifndef MYMAP_H

#define MYMAP_H
#include "../Game/myObject.h"
#include "../Library/gameutil.h"

enum ComponentType {
	DOOR1 = 0,
	DOOR2 = 1
};

class Map {
public:
	int int_map[5][29][40];
	game_framework::CMovingBitmap map1[5][29][40];
	Component door1 = Component({ "Resources/door100.bmp",
									"Resources/door101.bmp",
									"Resources/door102.bmp",
									"Resources/door103.bmp",
									"Resources/door104.bmp",
									"Resources/door105.bmp" });
	Component door2 = Component({ "Resources/door200.bmp",
									"Resources/door201.bmp",
									"Resources/door202.bmp",
									"Resources/door203.bmp",
									"Resources/door204.bmp",
									"Resources/door205.bmp" });
	
	void generateMap();
	void placeComponent(ComponentType name, int x, int y);
	void showMap(int map_stage);
	bool IsBlock(int stage, int x, int y);
};

#endif // !MYMAP_H