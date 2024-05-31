#pragma once

#ifndef MYOBJECT_H

#define MYOBJECT_H
#include "../Library/gameutil.h"
#include "../Game/myMap.h"

using namespace game_framework;

namespace Object {

	class Object {
	public:
		virtual void generateObject() = 0;
		virtual void setObject(int map_stage) = 0;
		virtual void showObject(int map_stage) = 0;
	};

	class Door : public Object {
	public:
		CMovingBitmap door1;
		CMovingBitmap door2;

		void generateObject();
		void setObject(int map_stage);
		void showObject(int map_stage);
	};

	class Button : public Object {
	public:
		CMovingBitmap button1;
		CMovingBitmap button2;
		CMovingBitmap purple_button[2];
		CMovingBitmap white_button;

		int button1_y;
		int button2_y;
		int purple_button_y[2];
		int white_button_y;

		void generateObject();
		void setObject(int map_stage);
		void showObject(int map_stage);
	};

	class Ramp : public Object {
	public:
		CMovingBitmap ramp;
		CMovingBitmap ramp2;
		CMovingBitmap purple_ramp;
		CMovingBitmap white_ramp;
		CMovingBitmap green_ramp;
		CMovingBitmap red_ramp;
		CMovingBitmap short_white_ramp;
		CMovingBitmap purple_ramp3;

		int ramp_y1;
		int ramp_y2;
		int ramp2_y1;
		int ramp2_y2;
		int purple_ramp_x1;
		int purple_ramp_x2;
		int white_ramp_y1;
		int white_ramp_y2;
		int green_ramp_y1;
		int green_ramp_y2;
		int red_ramp_y1;
		int red_ramp_y2;
		int short_white_ramp_y1;
		int short_white_ramp_y2;
		int purple_ramp3_x1;
		int purple_ramp3_x2;

		void generateObject();
		void setObject(int map_stage);
		void showObject(int map_stage);
	};

	class Box : public Object {
	public:
		CMovingBitmap box;
		CMovingBitmap box_left;
		CMovingBitmap box_right;

		void generateObject();
		void setObject(int map_stage);
		void showObject(int map_stage);

	};


	class Diamond : public Object {
	public:
		CMovingBitmap red_diamond[8];
		CMovingBitmap blue_diamond[8];

		void generateObject();
		void setObject(int map_stage);
		void showObject(int map_stage);
	};

	class Joystick : public Object {
	public:
		CMovingBitmap joystick;
		CMovingBitmap green_joystick;
		CMovingBitmap red_joystick;

		void generateObject();
		void setObject(int map_stage);
		void showObject(int map_stage);
	};

	class Ball : public Object {
	public:
		CMovingBitmap ball[2];

		void generateObject();
		void setObject(int map_stage);
		void showObject(int map_stage);
	};

	class Fan : public Object {
	public:
		CMovingBitmap fan[2];

		void generateObject();
		void setObject(int map_stage);
		void showObject(int map_stage);
	};
}

#endif // !MYOBJECT_H