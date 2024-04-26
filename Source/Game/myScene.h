#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H
#include "../Library/gameutil.h"

class Scene {
public:

	game_framework::CMovingBitmap window[4];

	void loadScene();
	void showScene(int page_phase);

};
#endif // !MYSCENE_H