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
	
}


/*

Sol1:
//OnShow//
generateMap(int map_stage) {switch case複寫map[29][40]}
showMap()
Good/Bad:只需產生一組mapResource再隨map_stage覆蓋即可	/	一直重複讀取地圖

Sol2:
//OnInit//
generateMap1()
generateMap2()
generateMap3()
generateMap4()
generateMap5()

//OnShow//
showMap(map_stage)
Good/Bad:不用一直重複讀取地圖,依據map_stage選擇要生成的地圖/	一開始需先Init5個map[29][40]

*/