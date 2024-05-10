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

		door1.SetFrameIndexOfBitmap(0);
		door2.SetFrameIndexOfBitmap(0);
		break;

	case 2:
		door1.SetTopLeft(50, 70);
		door1.SetAnimation(100, true);

		door2.SetTopLeft(150, 70);
		door2.SetAnimation(100, true);

		door1.SetFrameIndexOfBitmap(0);
		door2.SetFrameIndexOfBitmap(0);
		break;

	case 3:
		door1.SetTopLeft(410, 245);
		door1.SetAnimation(100, true);

		door2.SetTopLeft(765, 245);
		door2.SetAnimation(100, true);

		door1.SetFrameIndexOfBitmap(0);
		door2.SetFrameIndexOfBitmap(0);
		break;

	case 4:
		door1.SetTopLeft(50, 150);
		door1.SetAnimation(100, true);

		door2.SetTopLeft(150, 150);
		door2.SetAnimation(100, true);

		door1.SetFrameIndexOfBitmap(0);
		door2.SetFrameIndexOfBitmap(0);
		break;

	case 5:
		door1.SetTopLeft(380, 370);
		door1.SetAnimation(100, true);

		door2.SetTopLeft(940, 370);
		door2.SetAnimation(100, true);

		door1.SetFrameIndexOfBitmap(0);
		door2.SetFrameIndexOfBitmap(0);
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

	case 3:
		door1.ShowBitmap();
		door2.ShowBitmap();
		break;
	case 4:
		door1.ShowBitmap();
		door2.ShowBitmap();
		break;
	case 5:
		door1.ShowBitmap();
		door2.ShowBitmap();
		break;
	}

}

//Button
void Object::Button::generateObject() {
	button1.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	button2.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	purple_button[0].LoadBitmapByString({ "Resources/purple_button.bmp" }, RGB(255, 255, 255));
	purple_button[1].LoadBitmapByString({ "Resources/purple_button.bmp" }, RGB(255, 255, 255));
	white_button.LoadBitmapByString({ "Resources/white_button.bmp" }, RGB(255, 255, 255));

}

void Object::Button::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		button1_y = 435;
		button2_y = 315;
		button1.SetTopLeft(400, button1_y);
		button2.SetTopLeft(1000, button2_y);

		white_button_y = 0;
		white_button.SetTopLeft(0, white_button_y);

		purple_button_y[0] = 0;
		purple_button_y[1] = 0;
		purple_button[0].SetTopLeft(0, purple_button_y[0]);
		purple_button[1].SetTopLeft(0, purple_button_y[1]);
		break;

	case 2:
		button1_y = 555;	//¥Õ¦â
		button2_y = 555;
		button1.SetTopLeft(300, button1_y);
		button2.SetTopLeft(1050, button2_y);

		white_button_y = 0;
		white_button.SetTopLeft(0, white_button_y);

		purple_button_y[0] = 135; 
		purple_button_y[1] = 135; 
		purple_button[0].SetTopLeft(300, purple_button_y[0]);
		purple_button[1].SetTopLeft(900, purple_button_y[1]);
		break;

	case 3:
		button1_y = 0;
		button2_y = 0;
		button1.SetTopLeft(0, button1_y);
		button2.SetTopLeft(0, button2_y);

		white_button_y = 825;
		white_button.SetTopLeft(1185, white_button_y);

		purple_button_y[0] = 825;
		purple_button_y[1] = 0;
		purple_button[0].SetTopLeft(1290, purple_button_y[0]);
		purple_button[1].SetTopLeft(0, purple_button_y[1]);
		break;
	case 4:
		button1_y = 344;
		button2_y = 0;
		button1.SetTopLeft(1100, button1_y);
		button2.SetTopLeft(0, button2_y);

		white_button_y = 0;
		white_button.SetTopLeft(0, white_button_y);

		purple_button_y[0] = 0;
		purple_button_y[1] = 0;
		purple_button[0].SetTopLeft(0, purple_button_y[0]);
		purple_button[1].SetTopLeft(0, purple_button_y[1]);
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
		purple_button[0].ShowBitmap();
		purple_button[1].ShowBitmap();
		break;

	case 3:
		white_button.ShowBitmap();
		purple_button[0].ShowBitmap();
		break;
	case 4:
		button1.ShowBitmap();
		break;

	}
	

}

//Ramp
void Object::Ramp::generateObject() {
	ramp.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
	ramp2.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
	purple_ramp.LoadBitmapByString({ "Resources/purple_ramp.bmp" });
	white_ramp.LoadBitmapByString({ "Resources/white_ramp2.bmp" });
	green_ramp.LoadBitmapByString({ "Resources/green_ramp.bmp" });
	red_ramp.LoadBitmapByString({ "Resources/red_ramp.bmp" });
	short_white_ramp.LoadBitmapByString({ "Resources/white_ramp3.bmp" });
	purple_ramp3.LoadBitmapByString({ "Resources/purple_ramp3.bmp" });
}

void Object::Ramp::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		ramp_y1 = 450;
		ramp_y2 = 558;
		ramp.SetTopLeft(50, ramp_y1);

		ramp2_y1 = 325;
		ramp2_y2 = 440;
		ramp2.SetTopLeft(1245, ramp2_y1);

		purple_ramp_x1 = 0;
		purple_ramp_x2 = 0;
		purple_ramp.SetTopLeft(purple_ramp_x1, 0);

		white_ramp_y1 = 0;
		white_ramp_y2 = 0;
		white_ramp.SetTopLeft(0, white_ramp_y1);

		green_ramp_y1 = 0;
		green_ramp_y2 = 0;
		green_ramp.SetTopLeft(0, green_ramp_y1);

		red_ramp_y1 = 0;
		red_ramp_y2 = 0;
		red_ramp.SetTopLeft(0, red_ramp_y1);
		break;
	
	case 2:
		ramp_y1 = 0;
		ramp_y2 = 0;
		ramp.SetTopLeft(0, ramp_y1);

		ramp2_y1 = 0;
		ramp2_y2 = 0;
		ramp2.SetTopLeft(0, ramp2_y1);

		purple_ramp_x1 = 740;
		purple_ramp_x2 = 595;
		purple_ramp.SetTopLeft(purple_ramp_x1, 150);

		white_ramp_y1 = 460;
		white_ramp_y2 = 350;
		white_ramp.SetTopLeft(680, white_ramp_y1);

		green_ramp_y1 = 0;
		green_ramp_y2 = 0;
		green_ramp.SetTopLeft(0, green_ramp_y1);

		red_ramp_y1 = 0;
		red_ramp_y2 = 0;
		red_ramp.SetTopLeft(0, red_ramp_y1);

		break;

	case 3:
		ramp_y1 = 0;
		ramp_y2 = 0;
		ramp.SetTopLeft(0, ramp_y1);

		ramp2_y1 = 0;
		ramp2_y2 = 0;
		ramp2.SetTopLeft(0, ramp2_y1);

		purple_ramp_x1 = 0;
		purple_ramp_x2 = 0;
		purple_ramp.SetTopLeft(purple_ramp_x1, 0);

		white_ramp_y1 = 0;
		white_ramp_y2 = 0;
		white_ramp.SetTopLeft(0, white_ramp_y1);

		green_ramp_y1 = 195;
		green_ramp_y2 = 60;
		green_ramp.SetTopLeft(540, green_ramp_y1);

		red_ramp_y1 = 195;
		red_ramp_y2 = 60;
		red_ramp.SetTopLeft(700, red_ramp_y1);

		short_white_ramp_y1 = 370;
		short_white_ramp_y2 = 480;
		short_white_ramp.SetTopLeft(700, short_white_ramp_y1);

		purple_ramp3_x1 = 1180;
		purple_ramp3_x2 = 1225;
		purple_ramp3.SetTopLeft(purple_ramp3_x1, 750);
		break;
	case 4:
		ramp_y1 = 0;
		ramp_y2 = 0;
		ramp.SetTopLeft(0, ramp_y1);

		ramp2_y1 = 180;
		ramp2_y2 = 250;
		ramp2.SetTopLeft(600, ramp2_y1);

		purple_ramp_x1 = 0;
		purple_ramp_x2 = 0;
		purple_ramp.SetTopLeft(purple_ramp_x1, 0);

		white_ramp_y1 = 0;
		white_ramp_y2 = 0;
		white_ramp.SetTopLeft(0, white_ramp_y1);

		green_ramp_y1 = 0;
		green_ramp_y2 = 0;
		green_ramp.SetTopLeft(0, green_ramp_y1);

		red_ramp_y1 = 0;
		red_ramp_y2 = 0;
		red_ramp.SetTopLeft(0, red_ramp_y1);

		short_white_ramp_y1 = 0;
		short_white_ramp_y2 = 0;
		short_white_ramp.SetTopLeft(0, short_white_ramp_y1);

		purple_ramp3_x1 = 0;
		purple_ramp3_x2 = 0;
		purple_ramp3.SetTopLeft(purple_ramp3_x1, 0);
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
		purple_ramp.ShowBitmap();
		white_ramp.ShowBitmap();
		break;

	case 3:
		green_ramp.ShowBitmap();
		red_ramp.ShowBitmap();
		short_white_ramp.ShowBitmap();
		purple_ramp3.ShowBitmap();
		break;
	case 4:
		ramp2.ShowBitmap();
		break;
	}
}

//Box
void Object::Box::generateObject() {
	box.LoadBitmapByString({ "Resources/box.bmp" }, RGB(255, 255, 255));
	box_left.LoadBitmapByString({ "Resources/box_side.bmp" });
	box_right.LoadBitmapByString({ "Resources/box_side.bmp" });
}

void Object::Box::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		box.SetTopLeft(700, 250);
		break;

	case 2:
		box.SetTopLeft(0, 0);
		break;
	case 3:
		box.SetTopLeft(0, 0);
		break;
	case 4:
		box.SetTopLeft(900, 100);
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
	case 3:
		break;
	case 4:
		box.ShowBitmap();
		box_left.ShowBitmap();
		box_right.ShowBitmap();
		break;
	}
}

//Pond
void Object::Pond::generateObject() {
	pond.LoadBitmapByString({ "Resources/pond.bmp" }, RGB(255, 255, 255));
	red_pond.LoadBitmapByString({ "Resources/red_pond.bmp" }, RGB(255, 255, 255));
	blue_pond[0].LoadBitmapByString({ "Resources/blue_pond.bmp" }, RGB(255, 255, 255));
	short_red_pond.LoadBitmapByString({ "Resources/red_short_pond.bmp" }, RGB(255, 255, 255));
	mid_blue_pond.LoadBitmapByString({ "Resources/blue_mid_pond.bmp" }, RGB(255, 255, 255));

	for (int i = 0; i < 2; i++) {
		long_pond[i].LoadBitmapByString({ "Resources/long_green_pond.bmp" }, RGB(255, 255, 255));
		long_red_pond[i].LoadBitmapByString({ "Resources/long_red_pond.bmp" }, RGB(255, 255, 255));
		long_blue_pond[i].LoadBitmapByString({ "Resources/long_blue_pond.bmp" }, RGB(255, 255, 255));
		mid_red_pond[i].LoadBitmapByString({ "Resources/red_mid_pond.bmp" }, RGB(255, 255, 255));
	}

	for (int i = 0; i < 3; i++) {
		blue_pond[i].LoadBitmapByString({ "Resources/blue_pond.bmp" }, RGB(255, 255, 255));
	}
	
}

void Object::Pond::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		pond.SetTopLeft(840, 660);
		red_pond.SetTopLeft(630, 840);
		blue_pond[0].SetTopLeft(872, 840);
		blue_pond[1].SetTopLeft(0, 0);
		blue_pond[2].SetTopLeft(0, 0);
		long_pond[0].SetTopLeft(0, 0);
		long_pond[1].SetTopLeft(0, 0);
		long_red_pond[0].SetTopLeft(0, 0);
		long_red_pond[1].SetTopLeft(0, 0);
		long_blue_pond[0].SetTopLeft(0, 0);
		long_blue_pond[1].SetTopLeft(0, 0);
		short_red_pond.SetTopLeft(0, 0);
		mid_red_pond[0].SetTopLeft(0, 0);
		mid_red_pond[1].SetTopLeft(0, 0);
		mid_blue_pond.SetTopLeft(0, 0);
		break;

	case 2:
		pond.SetTopLeft(0, 0);
		red_pond.SetTopLeft(0, 0);
		blue_pond[0].SetTopLeft(0, 0);
		blue_pond[1].SetTopLeft(0, 0);
		blue_pond[2].SetTopLeft(0, 0);
		long_pond[0].SetTopLeft(308, 420);
		long_pond[1].SetTopLeft(807, 420);
		long_red_pond[0].SetTopLeft(280, 840);
		long_red_pond[1].SetTopLeft(770, 720);
		long_blue_pond[0].SetTopLeft(280, 720);
		long_blue_pond[1].SetTopLeft(770, 840);
		short_red_pond.SetTopLeft(0, 0);
		mid_red_pond[0].SetTopLeft(0, 0);
		mid_red_pond[1].SetTopLeft(0, 0);
		mid_blue_pond.SetTopLeft(0, 0);
		break;

	case 3:
		pond.SetTopLeft(0, 0);
		red_pond.SetTopLeft(0, 0);
		blue_pond[0].SetTopLeft(385, 150);
		blue_pond[1].SetTopLeft(695, 150);
		blue_pond[2].SetTopLeft(240, 690);
		long_pond[0].SetTopLeft(0, 0);
		long_pond[1].SetTopLeft(0, 0);
		long_red_pond[0].SetTopLeft(0, 0);
		long_red_pond[1].SetTopLeft(0, 0);
		long_blue_pond[0].SetTopLeft(0, 0);
		long_blue_pond[1].SetTopLeft(0, 0);
		short_red_pond.SetTopLeft(580, 150);
		mid_red_pond[0].SetTopLeft(770, 720);
		mid_red_pond[1].SetTopLeft(730, 840);
		mid_blue_pond.SetTopLeft(0, 0);
		break;
	case 4:
		pond.SetTopLeft(0, 0);
		red_pond.SetTopLeft(0, 0);
		blue_pond[0].SetTopLeft(0, 0);
		blue_pond[1].SetTopLeft(0, 0);
		blue_pond[2].SetTopLeft(0, 0);
		long_pond[0].SetTopLeft(0, 0);
		long_pond[1].SetTopLeft(0, 0);
		long_red_pond[0].SetTopLeft(0, 0);
		long_red_pond[1].SetTopLeft(0, 0);
		long_blue_pond[0].SetTopLeft(0, 0);
		long_blue_pond[1].SetTopLeft(0, 0);
		short_red_pond.SetTopLeft(0, 0);
		mid_red_pond[0].SetTopLeft(0, 0);
		mid_red_pond[1].SetTopLeft(0, 0);
		mid_blue_pond.SetTopLeft(0, 0);
		break;

	case 5:
		pond.SetTopLeft(0, 0);
		red_pond.SetTopLeft(0, 0);
		blue_pond[0].SetTopLeft(0, 0);
		blue_pond[1].SetTopLeft(0, 0);
		blue_pond[2].SetTopLeft(0, 0);
		long_pond[0].SetTopLeft(0, 0);
		long_pond[1].SetTopLeft(0, 0);
		long_red_pond[0].SetTopLeft(910, 600);
		long_red_pond[1].SetTopLeft(200, 840);
		long_blue_pond[0].SetTopLeft(200, 600);
		long_blue_pond[1].SetTopLeft(910, 840);
		short_red_pond.SetTopLeft(0, 0);
		mid_red_pond[0].SetTopLeft(345, 300);
		mid_red_pond[1].SetTopLeft(0, 0);
		mid_blue_pond.SetTopLeft(905, 300);
		break;

	}
}

void Object::Pond::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		pond.ShowBitmap();
		red_pond.ShowBitmap();
		blue_pond[0].ShowBitmap();
		break;

	case 2:
		long_pond[0].ShowBitmap();
		long_red_pond[0].ShowBitmap();
		long_blue_pond[0].ShowBitmap();
		long_pond[1].ShowBitmap();
		long_red_pond[1].ShowBitmap();
		long_blue_pond[1].ShowBitmap();
		break;

	case 3:
		blue_pond[0].ShowBitmap();
		blue_pond[1].ShowBitmap();
		blue_pond[2].ShowBitmap();
		short_red_pond.ShowBitmap();
		mid_red_pond[0].ShowBitmap();
		mid_red_pond[1].ShowBitmap();
		break;
	case 4:
		break;

	case 5:
		mid_red_pond[0].ShowBitmap();
		long_red_pond[0].ShowBitmap();
		long_blue_pond[0].ShowBitmap();
		long_red_pond[1].ShowBitmap();
		long_blue_pond[1].ShowBitmap();
		mid_blue_pond.ShowBitmap();
		break;
	}
}

//Diamond
void Object::Diamond::generateObject() {
	for (int i = 0; i < 8; i++) {
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
		red_diamond[4].SetTopLeft(0, 0);
		red_diamond[5].SetTopLeft(0, 0);
		red_diamond[6].SetTopLeft(0, 0);
		red_diamond[7].SetTopLeft(0, 0);

		blue_diamond[0].SetTopLeft(935, 780);
		blue_diamond[1].SetTopLeft(850, 420);
		blue_diamond[2].SetTopLeft(80, 150);
		blue_diamond[3].SetTopLeft(750, 130);
		blue_diamond[4].SetTopLeft(0, 0);
		blue_diamond[5].SetTopLeft(0, 0);
		blue_diamond[6].SetTopLeft(0, 0);
		blue_diamond[7].SetTopLeft(0, 0);
		break;

	case 2:
		red_diamond[0].SetTopLeft(350, 785);
		red_diamond[1].SetTopLeft(450, 785);
		red_diamond[2].SetTopLeft(840, 665);
		red_diamond[3].SetTopLeft(940, 665);
		red_diamond[4].SetTopLeft(940, 510);
		red_diamond[5].SetTopLeft(550, 510);
		red_diamond[6].SetTopLeft(650, 330);
		red_diamond[7].SetTopLeft(620, 100);

		blue_diamond[0].SetTopLeft(350, 665);
		blue_diamond[1].SetTopLeft(450, 665);
		blue_diamond[2].SetTopLeft(840, 785);
		blue_diamond[3].SetTopLeft(940, 785);
		blue_diamond[4].SetTopLeft(840, 510);
		blue_diamond[5].SetTopLeft(450, 510);
		blue_diamond[6].SetTopLeft(710, 330);
		blue_diamond[7].SetTopLeft(680, 100);
		break;

	case 3:
		red_diamond[0].SetTopLeft(1280, 50);
		red_diamond[1].SetTopLeft(150, 470);
		red_diamond[2].SetTopLeft(820, 660);
		red_diamond[3].SetTopLeft(780, 790);
		red_diamond[4].SetTopLeft(0, 0);
		red_diamond[5].SetTopLeft(0, 0);
		red_diamond[6].SetTopLeft(0, 0);
		red_diamond[7].SetTopLeft(0, 0);

		blue_diamond[0].SetTopLeft(450, 100);
		blue_diamond[1].SetTopLeft(765, 100);
		blue_diamond[2].SetTopLeft(50, 430);
		blue_diamond[3].SetTopLeft(860, 410);
		blue_diamond[4].SetTopLeft(310, 640);
		blue_diamond[5].SetTopLeft(380, 100);
		blue_diamond[6].SetTopLeft(0, 0);
		blue_diamond[7].SetTopLeft(0, 0);
		break;
	case 4:
		red_diamond[0].SetTopLeft(170, 530);
		red_diamond[1].SetTopLeft(750, 470);
		red_diamond[2].SetTopLeft(920, 670);
		red_diamond[3].SetTopLeft(500, 670);
		red_diamond[4].SetTopLeft(70, 440);
		red_diamond[5].SetTopLeft(270, 310);
		red_diamond[6].SetTopLeft(640, 300);
		red_diamond[7].SetTopLeft(380, 130);	

		blue_diamond[0].SetTopLeft(70, 520);
		blue_diamond[1].SetTopLeft(640, 450);
		blue_diamond[2].SetTopLeft(940, 480);
		blue_diamond[3].SetTopLeft(690, 720);
		blue_diamond[4].SetTopLeft(310, 710);
		blue_diamond[5].SetTopLeft(450, 300);
		blue_diamond[6].SetTopLeft(450, 130);
		blue_diamond[7].SetTopLeft(0, 0);
		break;
	}
}

void Object::Diamond::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		for (int i = 0; i < 8; i++) {
			red_diamond[i].ShowBitmap();
			blue_diamond[i].ShowBitmap();

		}
		break;

	case 2:
		for (int i = 0; i < 8; i++) {
			red_diamond[i].ShowBitmap();
			blue_diamond[i].ShowBitmap();

		}
		break;

	case 3:
		for (int i = 0; i < 8; i++) {
			red_diamond[i].ShowBitmap();
			blue_diamond[i].ShowBitmap();

		}
		break;
	case 4:
		for (int i = 0; i < 8; i++) {
			red_diamond[i].ShowBitmap();
			blue_diamond[i].ShowBitmap();

		}
		break;
	}
}

//Joystick
void Object::Joystick::generateObject() {
	joystick.LoadBitmapByString({ "Resources/joystick_1.bmp", "Resources/joystick_2.bmp" , "Resources/joystick_3.bmp" }, RGB(255, 255, 255));
	green_joystick.LoadBitmapByString({ "Resources/green_joystick.bmp", "Resources/green_joystick1.bmp" }, RGB(255, 255, 255));
	red_joystick.LoadBitmapByString({ "Resources/red_joystick.bmp", "Resources/red_joystick1.bmp" }, RGB(255, 255, 255));

}

void Object::Joystick::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		joystick.SetTopLeft(300, 535);
		joystick.SetAnimation(100, true);
		joystick.SetFrameIndexOfBitmap(0);

		green_joystick.SetTopLeft(0, 0);
		red_joystick.SetTopLeft(0, 0);
		break;

	case 2:
		joystick.SetTopLeft(0, 0);
		joystick.SetAnimation(100, true);
		joystick.SetFrameIndexOfBitmap(0);

		green_joystick.SetTopLeft(0, 0);
		red_joystick.SetTopLeft(0, 0);
		break;

	case 3:
		joystick.SetTopLeft(0, 0);
		joystick.SetAnimation(100, true);
		joystick.SetFrameIndexOfBitmap(0);

		green_joystick.SetTopLeft(180, 805); 
		red_joystick.SetTopLeft(450, 805);
		break;
	case 4:
		joystick.SetTopLeft(0, 0);
		joystick.SetAnimation(0, true);
		joystick.SetFrameIndexOfBitmap(0);

		green_joystick.SetTopLeft(0, 0);
		red_joystick.SetTopLeft(0, 0);
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

	case 3:
		green_joystick.ShowBitmap();
		red_joystick.ShowBitmap();
		break;
	case 4:

		break;
	}
}

//Ball
void Object::Ball::generateObject() {
	for (int i = 0; i < 2; i++) {
		ball[i].LoadBitmapByString({ "Resources/ball.bmp" }, RGB(255, 255, 255));
	}
}

void Object::Ball::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		ball[0].SetTopLeft(0, 0);
		ball[1].SetTopLeft(0, 0);
		break;

	case 2:
		ball[0].SetTopLeft(0, 0);
		ball[1].SetTopLeft(0, 0);
		break;

	case 3:
		ball[0].SetTopLeft(1150, 125);
		ball[1].SetTopLeft(1100, 305);
		break;
	case 4:
		ball[0].SetTopLeft(0, 0);
		ball[1].SetTopLeft(0, 0);
		break;
	}
}

void Object::Ball::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		break;

	case 2:
		break;

	case 3:
		ball[0].ShowBitmap();
		ball[1].ShowBitmap();
		break;
	case 4:
		break;
	}
}

// Fan
void Object::Fan::generateObject() {
	for (int i = 0; i < 2; i++) {
		fan[i].LoadBitmapByString({ "Resources/fan.bmp" }, RGB(255, 255, 255));
	}
}

void Object::Fan::setObject(int map_stage) {
	switch (map_stage) {
	case 1:
		fan[0].SetTopLeft(0, 0);
		fan[1].SetTopLeft(0, 0);
		break;

	case 2:
		fan[0].SetTopLeft(0, 0);
		fan[1].SetTopLeft(0, 0);
		break;

	case 3:
		fan[0].SetTopLeft(0, 0);
		fan[1].SetTopLeft(0, 0);
		break;

	case 4:
		fan[0].SetTopLeft(35, 600);
		fan[1].SetTopLeft(0, 0);
		break;

	case 5:
		fan[0].SetTopLeft(30, 330);
		fan[1].SetTopLeft(1280, 330);
		break;
	}
}

void Object::Fan::showObject(int map_stage) {
	switch (map_stage) {
	case 1:
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		fan[0].ShowBitmap();
		break;

	case 5:
		fan[0].ShowBitmap();
		fan[1].ShowBitmap();
		break;
	}
}

