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
		virtual void showObject(int map_stage) = 0;

	};

	class Door : public Object {
	public:
		CMovingBitmap door1;
		CMovingBitmap door2;
		void generateObject();
		void showObject(int map_stage);
	};

	class Button : public Object {
	public:
		CMovingBitmap button1;
		CMovingBitmap button2;
		int button1_y;
		int button2_y;

		void generateObject();
		void showObject(int map_stage);

	};

	class Ramp : public Object {
	public:
		CMovingBitmap ramp;
		CMovingBitmap ramp2;
		int ramp_y1;
		int ramp_y2;
		int ramp2_y1;
		int ramp2_y2;

		void generateObject();
		void showObject(int map_stage);
	};

	class Box : public Object {
	public:
		CMovingBitmap box;
		CMovingBitmap box_left;
		CMovingBitmap box_right;

		void generateObject();
		void showObject(int map_stage);

	};

	class Pond : public Object {
	public:
		CMovingBitmap pond;
		CMovingBitmap red_pond;
		CMovingBitmap blue_pond;
		void generateObject();
		void showObject(int map_stage);
	};

	class Diamond : public Object {
	public:
		CMovingBitmap red_diamond[4];
		CMovingBitmap blue_diamond[4];
		void generateObject();
		void showObject(int map_stage);
	};

	class Joystick : public Object {
	public:
		CMovingBitmap joystick;
		void generateObject();
		void showObject(int map_stage);
	};
}

#endif // !MYOBJECT_H