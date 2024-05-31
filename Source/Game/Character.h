#pragma once
#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <string>
#include "../Library/gameutil.h"

using namespace game_framework;

class Character {
public:
	string name;
	int bodyFrame = 0;
	CMovingBitmap head;
	CMovingBitmap leftArm;
	CMovingBitmap rightArm;
	CMovingBitmap foot;
	CMovingBitmap body[3];

	Character(string name) {
		this->name = name;
	}

	~Character() = default;
	
	void OnInit(){
		vector<string> leftAnimation(7);
		vector<string> rightAnimation(7);

		for (int i = 0; i < 7; i++) {
			rightAnimation[i] = "Resources/" + name + "(1_" + std::to_string(i) + ").bmp";
			leftAnimation[i] = "Resources/" + name + "(2_" + std::to_string(i) + ").bmp";
		}

		body[0].LoadBitmapByString(
			{ "Resources/" + name + ".bmp", "Resources/character_ignore.bmp" }, 
			RGB(255, 255, 255)
		);
		body[1].LoadBitmapByString(rightAnimation, RGB(255, 255, 255));
		body[2].LoadBitmapByString(leftAnimation, RGB(255, 255, 255));
		foot.LoadBitmapByString({ "Resources/foot.bmp" }, RGB(255, 255, 255));
		head.LoadBitmapByString({ "Resources/head.bmp" }, RGB(255, 255, 255));
		leftArm.LoadBitmapByString({ "Resources/left.bmp" }, RGB(255, 255, 255));
		rightArm.LoadBitmapByString({ "Resources/left.bmp" }, RGB(255, 255, 255));
	}

	void SetTopLeft(int x, int y) {
		for (int i = 0; i < 3; i++) {
			body[i].SetTopLeft(x, y);
			foot.SetTopLeft(body[i].GetLeft() + 25, body[i].GetTop() + 82);
			head.SetTopLeft(body[i].GetLeft() + 25, body[i].GetTop() + 10);
			leftArm.SetTopLeft(body[i].GetLeft() + 5, body[i].GetTop() + 25);
			rightArm.SetTopLeft(body[i].GetLeft() + 50, body[i].GetTop() + 25);
		}
	}

	void OnPressRight() {
		bodyFrame = 1;
		body[bodyFrame].SetAnimation(100, false);
	}

	void OnPressLeft() {
		bodyFrame = 2;
		body[bodyFrame].SetAnimation(100, false);
	}

	void OnPressUp() {
		bodyFrame = 0;
	}

	void OnShow() {
		head.ShowBitmap();
		leftArm.ShowBitmap();
		rightArm.ShowBitmap();
		foot.ShowBitmap();
		body[bodyFrame].ShowBitmap();
	}

	bool IsRightWalking() {
		return bodyFrame == 1;
	}

	bool IsLeftWalking() {
		return bodyFrame == 2;
	}

	CMovingBitmap GetBody() {
		return body[0];
	}

	int GetLeft() {
		return body[0].GetLeft();
	}

	int GetTop() {
		return body[0].GetTop();
	}
};