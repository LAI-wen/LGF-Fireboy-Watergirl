#include "stdafx.h"
#include "myScene.h"



void Scene::loadScene() {

	//死掉介面 0
	//繼續_ALL寶石介面 1
	//繼續_NOT ALL寶石介面 2
	// 初始選單介面 3

	//window(setting paused die pass)
	window[0].LoadBitmapByString({ "Resources/w_game_over.bmp" });				//死掉介面
	window[1].LoadBitmapByString({ "Resources/w_continue_all.bmp" });			//繼續_ALL寶石介面
	window[2].LoadBitmapByString({ "Resources/w_continue.bmp" });				//繼續_NOT ALL寶石介面
	window[3].LoadBitmapByString({ "Resources/w_choose0.bmp" });				// 初始選單介面
	for (int i = 0; i < 4; i++) {
		window[i].SetTopLeft(0, 0);
	}

}

void Scene::showScene(int page_phase) {

	//setting window
	if (page_phase == 0) {
		window[0].ShowBitmap();		//window
	}

	//paused window
	if (page_phase == 1) {
		window[1].ShowBitmap();		//window
	}

	//die window
	if (page_phase == 2) {
		window[2].ShowBitmap();		//window
	}

	//pass window
	if (page_phase == 3) {
		window[3].ShowBitmap();		//window
	}



}