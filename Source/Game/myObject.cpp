#include "stdafx.h"
#include "../Game/myObject.h"

void Object::Object::generateObject() { }

void Object::Object::showObject(int map_stage) { }

//Door
void Object::Door::generateObject() {
	door1.LoadBitmapByString({ "Resources/door100.bmp",
							   "Resources/door101.bmp",
							   "Resources/door102.bmp",
							   "Resources/door103.bmp",
							   "Resources/door104.bmp",
							   "Resources/door105.bmp" });

	door2.LoadBitmapByString({ "Resources/door200.bmp",
							   "Resources/door201.bmp",
							   "Resources/door202.bmp",
							   "Resources/door203.bmp",
							   "Resources/door204.bmp",
							   "Resources/door205.bmp" });
}

void Object::Door::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		door1.SetTopLeft(1200, 95);
		door1.SetAnimation(100, true);

		door2.SetTopLeft(1100, 95);
		door2.SetAnimation(100, true);
		break;
	
	case 2:
		door1.SetTopLeft(50, 70);
		door1.SetAnimation(100, true);

		door2.SetTopLeft(150, 70);
		door2.SetAnimation(100, true);
		break;
	
	}
	

}

void Object::Door::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		door1.ShowBitmap();
		door2.ShowBitmap();
		break;

	case 2:
		door1.ShowBitmap();
		door2.ShowBitmap();
		break;
	}

}

//Button
void Object::Button::generateObject() {
	button1.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	button2.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
}

void Object::Button::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		button1_y = 435;
		button2_y = 317;
		button1.SetTopLeft(400, button1_y);
		button2.SetTopLeft(1000, button2_y);
		break;

	case 2:
		button1_y = 555;
		button2_y = 555;
		button1.SetTopLeft(300, button1_y);
		button2.SetTopLeft(1050, button2_y);
		break;
	}
}

void Object::Button::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		button1.ShowBitmap();
		button2.ShowBitmap();
		break;

	case 2:
		button1.ShowBitmap();
		button2.ShowBitmap();
		break;

	}
	

}

//Ramp
void Object::Ramp::generateObject() {
	ramp.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
	ramp2.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
}

void Object::Ramp::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		ramp_y1 = 450;
		ramp_y2 = 558;
		ramp.SetTopLeft(50, ramp_y1);

		ramp2_y1 = 330;
		ramp2_y2 = 440;
		ramp2.SetTopLeft(1245, ramp2_y1);
		break;
	
	case 2:
		ramp_y1 = 0;
		ramp_y2 = 0;
		ramp.SetTopLeft(0, ramp_y1);

		ramp2_y1 = 0;
		ramp2_y2 = 0;
		ramp2.SetTopLeft(0, ramp2_y1);
		break;
	}
	
}

void Object::Ramp::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		ramp.ShowBitmap();
		ramp2.ShowBitmap();
		break;

	case 2:
		break;
	}
}

//Box
void Object::Box::generateObject() {
	box.LoadBitmapByString({ "Resources/box.bmp" }, RGB(255, 255, 255));
	box_left.LoadBitmapByString({ "Resources/box_side.bmp" }, RGB(255, 255, 255));
	box_right.LoadBitmapByString({ "Resources/box_side.bmp" }, RGB(255, 255, 255));
}

void Object::Box::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		box.SetTopLeft(700, 250);
		break;

	case 2:
		box.SetTopLeft(0, 0);
		break;
	}
}

void Object::Box::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		box.ShowBitmap();
		box_left.ShowBitmap();
		box_right.ShowBitmap();
		break;

	case 2:
		
		break;
	}
}

//Pond
void Object::Pond::generateObject() {
	pond.LoadBitmapByString({ "Resources/pond.bmp" }, RGB(255, 255, 255));
	red_pond.LoadBitmapByString({ "Resources/red_pond.bmp" }, RGB(255, 255, 255));
	blue_pond.LoadBitmapByString({ "Resources/blue_pond.bmp" }, RGB(255, 255, 255));

	for (int i = 0; i < 2; i++) {
		long_pond[i].LoadBitmapByString({ "Resources/long_green_pond.bmp" }, RGB(255, 255, 255));
		long_red_pond[i].LoadBitmapByString({ "Resources/long_red_pond.bmp" }, RGB(255, 255, 255));
		long_blue_pond[i].LoadBitmapByString({ "Resources/long_blue_pond.bmp" }, RGB(255, 255, 255));
	}
	
}

void Object::Pond::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		pond.SetTopLeft(840, 660);
		red_pond.SetTopLeft(630, 840);
		blue_pond.SetTopLeft(872, 840);
		break;

	case 2:
		pond.SetTopLeft(0, 0);
		red_pond.SetTopLeft(0, 0);
		blue_pond.SetTopLeft(0, 0);
		long_pond[0].SetTopLeft(308, 420);
		long_pond[1].SetTopLeft(807, 420);
		long_red_pond[0].SetTopLeft(280, 840);
		long_red_pond[1].SetTopLeft(770, 720);
		long_blue_pond[0].SetTopLeft(280, 720);
		long_blue_pond[1].SetTopLeft(770, 840);
		break;
	}
}

void Object::Pond::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		pond.ShowBitmap();
		red_pond.ShowBitmap();
		blue_pond.ShowBitmap();
		break;

	case 2:
		long_pond[0].ShowBitmap();
		long_red_pond[0].ShowBitmap();
		long_blue_pond[0].ShowBitmap();
		long_pond[1].ShowBitmap();
		long_red_pond[1].ShowBitmap();
		long_blue_pond[1].ShowBitmap();
		break;
	}
}

//Diamond
void Object::Diamond::generateObject() {
	for (int i = 0; i < 4; i++) {
		blue_diamond[i].LoadBitmapByString({ "Resources/blue_diamond.bmp", "Resources/diamond_ignore.bmp" }, RGB(255, 255, 255));
		red_diamond[i].LoadBitmapByString({ "Resources/red_diamond.bmp", "Resources/diamond_ignore.bmp" }, RGB(255, 255, 255));
	}
}

void Object::Diamond::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		red_diamond[0].SetTopLeft(700, 780);
		red_diamond[1].SetTopLeft(300, 400);
		red_diamond[2].SetTopLeft(400, 100);
		red_diamond[3].SetTopLeft(0, 0);

		blue_diamond[0].SetTopLeft(935, 780);
		blue_diamond[1].SetTopLeft(850, 420);
		blue_diamond[2].SetTopLeft(80, 150);
		blue_diamond[3].SetTopLeft(750, 130);
		break;

	case 2:
		red_diamond[0].SetTopLeft(700, 780);
		red_diamond[1].SetTopLeft(300, 400);
		red_diamond[2].SetTopLeft(400, 100);
		red_diamond[3].SetTopLeft(0, 0);

		blue_diamond[0].SetTopLeft(935, 780);
		blue_diamond[1].SetTopLeft(850, 420);
		blue_diamond[2].SetTopLeft(80, 150);
		blue_diamond[3].SetTopLeft(750, 130);
		break;
	}
}

void Object::Diamond::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		for (int i = 0; i < 4; i++) {
			red_diamond[i].ShowBitmap();
			blue_diamond[i].ShowBitmap();

		}
		break;

	case 2:
		for (int i = 0; i < 4; i++) {
			red_diamond[i].ShowBitmap();
			blue_diamond[i].ShowBitmap();

		}
		break;
	}
}

//Joystick
void Object::Joystick::generateObject() {
	joystick.LoadBitmapByString({ "Resources/joystick_1.bmp", "Resources/joystick_2.bmp" , "Resources/joystick_3.bmp" }, RGB(255, 255, 255));
}

void Object::Joystick::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		joystick.SetTopLeft(300, 535);
		joystick.SetAnimation(100, true);
		joystick.SetFrameIndexOfBitmap(0);
		break;

	case 2:
		joystick.SetTopLeft(0, 0);
		joystick.SetAnimation(100, true);
		joystick.SetFrameIndexOfBitmap(0);
		break;
	}
}

void Object::Joystick::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		joystick.ShowBitmap();
		break;

	case 2:
		break;
	}
}

