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

	window[4].LoadBitmapByString({ "Resources/w_choose1.bmp" });				// 通過第一關
	window[5].LoadBitmapByString({ "Resources/w_choose2.bmp" });				// 通過第二關
	window[6].LoadBitmapByString({ "Resources/w_choose3.bmp" });				// 通過第三關
	window[7].LoadBitmapByString({ "Resources/w_choose4.bmp" });				// 通過第四關
	window[8].LoadBitmapByString({ "Resources/w_choose5.bmp" });				// 通過第五關
	window[9].LoadBitmapByString({ "Resources/w_pause.bmp" });				// pause
	window[10].LoadBitmapByString({ "Resources/w_END.bmp" });				// END


	for (int i = 0; i < 11; i++) {
		window[i].SetTopLeft(0, 0);
	}

}

void Scene::showScene(int page_phase) {

	window[page_phase].ShowBitmap();		//window




}