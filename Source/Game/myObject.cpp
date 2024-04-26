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
	door1.SetTopLeft(1200, 95);
	door1.SetAnimation(100, true);

	door2.LoadBitmapByString({ "Resources/door200.bmp",
							   "Resources/door201.bmp",
							   "Resources/door202.bmp",
							   "Resources/door203.bmp",
							   "Resources/door204.bmp",
							   "Resources/door205.bmp" });
	door2.SetTopLeft(1100, 95);
	door2.SetAnimation(100, true);
}

void Object::Door::showObject(int map_stage) {
	if (map_stage == 1) {
		door1.ShowBitmap();
		door2.ShowBitmap();
	}
}

//Button
void Object::Button::generateObject() {
	button1.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	button2.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	

	button1_y = 435;
	button2_y = 317;
	button1.SetTopLeft(400, button1_y);
	button2.SetTopLeft(1000, button2_y);
}

void Object::Button::showObject(int map_stage) {
	if (map_stage == 1) {
		button1.ShowBitmap();
		button2.ShowBitmap();
	}
}

//Ramp
void Object::Ramp::generateObject() {
	ramp.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
	ramp2.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });

	ramp_y1 = 450;
	ramp_y2 = 558;
	ramp.SetTopLeft(50, ramp_y1);

	ramp2_y1 = 330;
	ramp2_y2 = 440;
	ramp2.SetTopLeft(1245, ramp2_y1);
}

void Object::Ramp::showObject(int map_stage) {
	if (map_stage == 1) {
		ramp.ShowBitmap();
		ramp2.ShowBitmap();
	}
}

//Box
void Object::Box::generateObject() {
	box.LoadBitmapByString({ "Resources/box.bmp" }, RGB(255, 255, 255));
	box_left.LoadBitmapByString({ "Resources/box_side.bmp" });
	box_right.LoadBitmapByString({ "Resources/box_side.bmp" });
	
	box.SetTopLeft(700, 250);
	//box_left.SetTopLeft(box.GetLeft() - 5, box.GetTop());
	//box_right.SetTopLeft(box.GetLeft() + 43, box.GetTop());
	
	
}

void Object::Box::showObject(int map_stage) {
	if (map_stage == 1) {
		box.ShowBitmap();
		box_left.ShowBitmap();
		box_right.ShowBitmap();
	}
}

//Pond
void Object::Pond::generateObject() {
	pond.LoadBitmapByString({ "Resources/pond.bmp" }, RGB(255, 255, 255));
	red_pond.LoadBitmapByString({ "Resources/red_pond.bmp" }, RGB(255, 255, 255));
	blue_pond.LoadBitmapByString({ "Resources/blue_pond.bmp" }, RGB(255, 255, 255));

	pond.SetTopLeft(840, 660);
	red_pond.SetTopLeft(630, 840);
	blue_pond.SetTopLeft(872, 840);
}

void Object::Pond::showObject(int map_stage) {
	if (map_stage == 1) {
		pond.ShowBitmap();
		red_pond.ShowBitmap();
		blue_pond.ShowBitmap();
	}
}

//Diamond
void Object::Diamond::generateObject() {
	for (int i = 0; i < 4; i++) {
		blue_diamond[i].LoadBitmapByString({ "Resources/blue_diamond.bmp", "Resources/diamond_ignore.bmp" }, RGB(255, 255, 255));
		red_diamond[i].LoadBitmapByString({ "Resources/red_diamond.bmp", "Resources/diamond_ignore.bmp" }, RGB(255, 255, 255));
	}

	red_diamond[0].SetTopLeft(700, 780);
	red_diamond[1].SetTopLeft(300, 400);
	red_diamond[2].SetTopLeft(400, 100);
	red_diamond[3].SetTopLeft(0, 0);

	blue_diamond[0].SetTopLeft(935, 780);
	blue_diamond[1].SetTopLeft(850, 420);
	blue_diamond[2].SetTopLeft(80, 150);
	blue_diamond[3].SetTopLeft(750, 130);
}

void Object::Diamond::showObject(int map_stage) {
	if (map_stage == 1) {
		for (int i = 0; i < 4; i++) {
			red_diamond[i].ShowBitmap();
			blue_diamond[i].ShowBitmap();
			
		}
	}
}

//Joystick
void Object::Joystick::generateObject() {
	joystick.LoadBitmapByString({ "Resources/joystick_1.bmp", "Resources/joystick_2.bmp" , "Resources/joystick_3.bmp" }, RGB(255, 255, 255));
	joystick.SetTopLeft(300, 535);
	joystick.SetAnimation(100, true);
}

void Object::Joystick::showObject(int map_stage) {
	if (map_stage == 1) {
		joystick.ShowBitmap();
	}
}

