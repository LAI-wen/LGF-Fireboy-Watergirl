#include "stdafx.h"
#include "../Game/myMap.h"
#include <fstream>


void Map::generateMap() {
	
	std::ifstream map1("map/map1.map");
	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 40; j++) {
			map1 >> this->int_map[0][i][j];
			if (this->int_map[0][i][j] == 1){
				this->map1[0][i][j].LoadBitmapByString({ "Resources/cube.bmp" });
				this->map1[0][i][j].SetTopLeft(j * 35, i * 30);
			}
			
		}
	}
	map1.close();

	std::ifstream map2("map/map2.map");
	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 40; j++) {
			map2 >> this->int_map[1][i][j];
			if (this->int_map[1][i][j] == 1) {
				this->map1[1][i][j].LoadBitmapByString({ "Resources/cube.bmp" });
				this->map1[1][i][j].SetTopLeft(j * 35, i * 30);

			}
		}
	}
	map2.close();

	std::ifstream map3("map/map3.map");
	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 40; j++) {
			map3 >> this->int_map[2][i][j];
			if (this->int_map[2][i][j] == 1) {
				this->map1[2][i][j].LoadBitmapByString({ "Resources/cube.bmp" });
				this->map1[2][i][j].SetTopLeft(j * 35, i * 30);

			}
		}
	}
	map3.close();

	std::ifstream map4("map/map4.map");
	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 40; j++) {
			map4 >> this->int_map[3][i][j];
			if (this->int_map[3][i][j] == 1) {
				this->map1[3][i][j].LoadBitmapByString({ "Resources/cube.bmp" });
				this->map1[3][i][j].SetTopLeft(j * 35, i * 30);
			}

		}
	}
	map4.close();

	std::ifstream map5("map/map5.map");
	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 40; j++) {
			map5 >> this->int_map[4][i][j];
			if (this->int_map[4][i][j] == 1) {
				this->map1[4][i][j].LoadBitmapByString({ "Resources/cube.bmp" });
				this->map1[4][i][j].SetTopLeft(j * 35, i * 30);
			}

		}
	}
	map5.close();
	
}

void Map::showMap(int map_stage) {
	
	if(map_stage == 1) {
		for (int i = 0; i < 29; i++) {
			for (int j = 0; j < 40; j++) {
				if (this->int_map[0][i][j] == 1) {
					this->map1[0][i][j].ShowBitmap();
				}
				
			}
		}
	}
	else if (map_stage == 2) {
		for (int i = 0; i < 29; i++) {
			for (int j = 0; j < 40; j++) {
				if (this->int_map[1][i][j] == 1) {
					this->map1[1][i][j].ShowBitmap();
				}
			}
		}

	}
	else if (map_stage == 3) {
		for (int i = 0; i < 29; i++) {
			for (int j = 0; j < 40; j++) {
				if (this->int_map[2][i][j] == 1) {
					this->map1[2][i][j].ShowBitmap();
				}
			}
		}

	}
	else if (map_stage == 4) {
		for (int i = 0; i < 29; i++) {
			for (int j = 0; j < 40; j++) {
				if (this->int_map[3][i][j] == 1) {
					this->map1[3][i][j].ShowBitmap();
				}
			}
		}

	}
	else if (map_stage == 5) {
		for (int i = 0; i < 29; i++) {
			for (int j = 0; j < 40; j++) {
				if (this->int_map[4][i][j] == 1) {
					this->map1[4][i][j].ShowBitmap();
				}
			}
		}

	}
	
}
