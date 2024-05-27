#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <fstream>
#include "sstream"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()	// 移動遊戲元素
{
	if (phase > 5) {
		return;
	}

	gravety();
	characterMove();
	//ballMove();
	BallMove(ball.ball[0], fireBoy);
	BallMove(ball.ball[1], fireBoy);
	BallMove(ball.ball[0], waterGirl);
	BallMove(ball.ball[1], waterGirl);
	
	/////////////////////////////////////////////////////////////////////////////
	////	 機關
	/////////////////////////////////////////////////////////////////////////////
	
	//機關 按鈕觸發
	
	if (phase == 1 || phase == 2 || phase == 4) {

		//角色 1  2 和箱子 碰到 button1 會按下
		if (CMovingBitmap::IsOverlap(waterGirl.foot, button.button1) == true ||
			CMovingBitmap::IsOverlap(fireBoy.foot, button.button1) == true || 
			CMovingBitmap::IsOverlap(box.box, button.button1) == true) {
			button.button1.SetTopLeft(button.button1.GetLeft(), min(button.button1_y+15,button.button1.GetTop() + 1));
		}
		else if (button.button1.GetTop() > button.button1_y) {
			button.button1.SetTopLeft(button.button1.GetLeft(), button.button1.GetTop() - 2);
		}

		//角色 1  2 和 碰到 button2 會按下

		if (CMovingBitmap::IsOverlap(waterGirl.foot, button.button2) == true || 
			CMovingBitmap::IsOverlap(fireBoy.foot, button.button2) == true) {
			button.button2.SetTopLeft(button.button2.GetLeft(), min(button.button1_y + 15,button.button2.GetTop() + 1));
		}
		else if (button.button2.GetTop() > button.button2_y) {
			button.button2.SetTopLeft(button.button2.GetLeft(), button.button2.GetTop() - 2);
		}


	}
	
	if (phase == 2 || phase == 3) {
		// 角色 1  2 和球 碰到 purple button 會按下
		for (int i = 0; i < 2; i++) {
			if (CMovingBitmap::IsOverlap(fireBoy.foot, button.purple_button[i]) == true ||
				CMovingBitmap::IsOverlap(waterGirl.foot, button.purple_button[i]) == true || 
				CMovingBitmap::IsOverlap(ball.ball[0], button.purple_button[i]) == true) {
				button.purple_button[i].SetTopLeft(button.purple_button[i].GetLeft(), min(button.purple_button_y[i]+15,button.purple_button[i].GetTop() + 1));
			}
			else if (button.purple_button[i].GetTop() > button.purple_button_y[i]) {
				button.purple_button[i].SetTopLeft(button.purple_button[i].GetLeft(), max(button.purple_button_y[i],button.purple_button[i].GetTop() - 2));
			}
		}

		// 球 碰到 white button 會按下
		if (CMovingBitmap::IsOverlap(ball.ball[1], button.white_button) == true) {
			button.white_button.SetTopLeft(button.white_button.GetLeft(), min(button.white_button_y+15,button.white_button.GetTop() + 1));
		}
		else if (button.white_button.GetTop() > button.white_button_y) {
			button.white_button.SetTopLeft(button.white_button.GetLeft(), button.white_button.GetTop() - 2);
		}
	}


	//機關 ramp 移動
	if (phase == 1 || phase == 4) {
		// button1 && button2 操控 ramp2 上下移動
		if (button.button1.GetTop() > button.button1_y || button.button2.GetTop() > button.button2_y) {
			ramp.ramp2.SetTopLeft(ramp.ramp2.GetLeft(), min(ramp.ramp2_y2, ramp.ramp2.GetTop() + 5));
		}
		else {
			ramp.ramp2.SetTopLeft(ramp.ramp2.GetLeft(), max(ramp.ramp2_y1, ramp.ramp2.GetTop() - 5));
		}
	}
	else if (phase == 2) {
		// button1 && button2 操控 white ramp 上下移動
		if (button.button1.GetTop() > button.button1_y || button.button2.GetTop() > button.button2_y) {
			ramp.white_ramp.SetTopLeft(ramp.white_ramp.GetLeft(), max(ramp.white_ramp_y2, ramp.white_ramp.GetTop() - 5));
		}
		else {
			ramp.white_ramp.SetTopLeft(ramp.white_ramp.GetLeft(), min(ramp.white_ramp_y1, ramp.white_ramp.GetTop() + 5));
		}
		// purple button 操控 purple ramp 左右移動
		if (button.purple_button[0].GetTop() > button.purple_button_y[0] || button.purple_button[1].GetTop() > button.purple_button_y[1]) {
			ramp.purple_ramp.SetTopLeft(max(ramp.purple_ramp_x2, ramp.purple_ramp.GetLeft() - 5), ramp.purple_ramp.GetTop());
		}
		else {
			ramp.purple_ramp.SetTopLeft(min(ramp.purple_ramp_x1, ramp.purple_ramp.GetLeft() + 5), ramp.purple_ramp.GetTop());
		}
	}
	else if (phase == 3) {
		// purple button[0] 操控 purple ramp3 左右移動
		if (button.purple_button[0].GetTop() > button.purple_button_y[0]) {
			ramp.purple_ramp3.SetTopLeft(min(ramp.purple_ramp3_x2, ramp.purple_ramp3.GetLeft() + 5), ramp.purple_ramp3.GetTop());
		}
		else {
			ramp.purple_ramp3.SetTopLeft(max(ramp.purple_ramp3_x1, ramp.purple_ramp3.GetLeft() - 5), ramp.purple_ramp3.GetTop());
		}
		// white button 操控 white ramp 上下移動
		if (button.white_button.GetTop() > button.white_button_y) {
			ramp.white_ramp.SetTopLeft(ramp.white_ramp.GetLeft(), min(ramp.white_ramp_y2, ramp.white_ramp.GetTop() + 5));
		}
		else {
			ramp.white_ramp.SetTopLeft(ramp.white_ramp.GetLeft(), max(ramp.white_ramp_y1, ramp.white_ramp.GetTop() - 5));
		}
	}

	//角色碰到機關 ramp 上下 移動時會跟著 上下 移動
	// ramp1
	if (CMovingBitmap::IsOverlap(fireBoy.foot, ramp.ramp) == true &&
		ramp.ramp.GetTop() > ramp.ramp_y1 && ramp.ramp.GetTop() != ramp.ramp_y2) {
		fireBoy.SetTopLeft(fireBoy.GetLeft(), fireBoy.GetTop() - 5);
	}
	if (CMovingBitmap::IsOverlap(waterGirl.foot, ramp.ramp) == true && 
		ramp.ramp.GetTop() > ramp.ramp_y1 && ramp.ramp.GetTop() != ramp.ramp_y2) {
		waterGirl.SetTopLeft(waterGirl.GetLeft(), waterGirl.GetTop() - 5);
	}

	// ramp2
	if (CMovingBitmap::IsOverlap(fireBoy.foot, ramp.ramp2) == true && 
		ramp.ramp2.GetTop() > ramp.ramp2_y1 && ramp.ramp2.GetTop() != ramp.ramp2_y2) {
		fireBoy.SetTopLeft(fireBoy.GetLeft(), fireBoy.GetTop() - 5);
	}
	if (CMovingBitmap::IsOverlap(waterGirl.foot, ramp.ramp2) == true && 
		ramp.ramp2.GetTop() > ramp.ramp2_y1 && ramp.ramp2.GetTop() != ramp.ramp2_y2) {
		waterGirl.SetTopLeft(waterGirl.GetLeft(), waterGirl.GetTop() - 5);
	}
	

	// joystick 控制 ramp1
	if (joystick.joystick.GetFrameIndexOfBitmap() == 2) {
		ramp.ramp.SetTopLeft(ramp.ramp.GetLeft(), min(ramp.ramp_y2, ramp.ramp.GetTop() + 5));
	}
	else {
		ramp.ramp.SetTopLeft(ramp.ramp.GetLeft(), max(ramp.ramp_y1, ramp.ramp.GetTop() - 5));
	}

	// red joystick 控制 red ramp
	if (joystick.red_joystick.GetFrameIndexOfBitmap() == 1) {
		ramp.red_ramp.SetTopLeft(ramp.red_ramp.GetLeft(), max(ramp.red_ramp_y2, ramp.red_ramp.GetTop() - 5));
	}
	else {
		ramp.red_ramp.SetTopLeft(ramp.red_ramp.GetLeft(), min(ramp.red_ramp_y1, ramp.red_ramp.GetTop() + 5));
	}

	// green joystick 控制 green ramp
	if (joystick.green_joystick.GetFrameIndexOfBitmap() == 1) {
		ramp.green_ramp.SetTopLeft(ramp.green_ramp.GetLeft(), max(ramp.green_ramp_y2, ramp.green_ramp.GetTop() - 5));
	}
	else {
		ramp.green_ramp.SetTopLeft(ramp.green_ramp.GetLeft(), min(ramp.green_ramp_y1, ramp.green_ramp.GetTop() + 5));
	}

	// 碰到 fan 飛起
	if (phase == 4) {
		if (fireBoy.foot.GetLeft() > 35 && fireBoy.foot.GetLeft() < 125 && fireBoy.head.GetTop() < 600 && fireBoy.head.GetTop() > 250) {
			fireBoy.SetTopLeft(fireBoy.GetLeft(), max(fireBoy.GetTop() - 8, 250));
		}
		if (waterGirl.foot.GetLeft() > 35 && waterGirl.foot.GetLeft() < 125 && waterGirl.head.GetTop() < 601 && waterGirl.head.GetTop() > 250) {
			waterGirl.SetTopLeft(waterGirl.GetLeft(), max(waterGirl.GetTop() - 8, 250));
		}
	}

	if (phase == 5) {
		if (fireBoy.foot.GetLeft() + fireBoy.foot.GetWidth() > 1280 && fireBoy.foot.GetLeft() < 1370 && fireBoy.foot.GetTop() < 330 && fireBoy.foot.GetTop() > 30) {
			fireBoy.SetTopLeft(fireBoy.GetLeft(), max(fireBoy.GetTop() - 8, 30));
		}
		if (waterGirl.foot.GetLeft() > 30 && waterGirl.foot.GetLeft() < 120 && waterGirl.foot.GetTop() < 330 && waterGirl.foot.GetTop() > 30) {
			waterGirl.SetTopLeft(waterGirl.GetLeft(), max(waterGirl.GetTop() - 8, 30));
		}
	}

	CheckDeadOnPool(waterGirl);
	CheckDeadOnPool(fireBoy);

	if (clock() - button_continue_time == 21000) {
		button_continue.SetFrameIndexOfBitmap(0);
		button_continue.ShowBitmap();
	}
	else if (clock() - button_continue_time <= 25500) {
		continue_what = 0;
	}
}


void CGameStateRun::CheckDeadOnPool(Character &character) {
	// 2 red pond
	// 3 blue pond
	// 4 green pond

	int foot1_y = (character.foot.GetTop()) / 30;
	for (int j = foot1_y; j < min(foot1_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] == 2) {
				if (character.name == CHARACTER_WATERGIRL && CMovingBitmap::IsOverlap(character.foot, map.map1[phase - 1][j][i]) == true && test_no_dead == false) {
					isdead = true;
					return;
				}
			}
			if (map.int_map[phase - 1][j][i] == 3) {
				if (character.name == CHARACTER_FIREBOY && CMovingBitmap::IsOverlap(character.foot, map.map1[phase - 1][j][i]) == true && test_no_dead == false) {
					isdead = true;
					return;
				}
			}
			if (map.int_map[phase - 1][j][i] == 4) {
				if (CMovingBitmap::IsOverlap(character.foot, map.map1[phase - 1][j][i]) == true && test_no_dead == false) {
					isdead = true;
					return;
				}
			}
		}
	}
}



void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	fireBoy.OnInit();
	waterGirl.OnInit();

	//背景
	bg.LoadBitmapByString({ "Resources/bg.bmp" });
	bg.SetTopLeft(0, 0);
	
	map.generateMap();
	scene.loadScene();
	door.generateObject();
	button.generateObject();
	ramp.generateObject();
	box.generateObject();
	diamond.generateObject();
	joystick.generateObject();
	ball.generateObject();
	fan.generateObject();

	pause.LoadBitmapByString({ "Resources/pause_img.bmp" }, RGB(255, 255, 255));;

	//continue 介面
	continueUI.LoadBitmapByString({ "Resources/continue.bmp", "Resources/continue_all.bmp" }, RGB(255, 255, 255));
	continueUI.SetTopLeft(170, 150);

	//死亡介面
	gameover.LoadBitmapByString({ "Resources/game_over.bmp" }, RGB(255, 255, 255));
	gameover.SetTopLeft(0, 0);

	//死亡介面按鈕
	button_menu.LoadBitmapByString({ "resources/button_menu.bmp","resources/button_menu1.bmp" });
	button_retry.LoadBitmapByString({ "resources/button_retry.bmp","resources/button_retry1.bmp" });
	button_menu.SetTopLeft(455, 536);
	button_retry.SetTopLeft(772, 536);
	button_continue.LoadBitmapByString({ "resources/button_continue1.bmp","resources/continue_button.bmp" });
	button_continue.SetTopLeft(230, 560);

	show_image_by_phase();
}




void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	////////角色2左右移動
	if (nChar == VK_LEFT) {
		keepLeft = true;
		waterGirl.OnPressLeft();
	}

	if (nChar == VK_RIGHT) {
		keepRight = true;
		waterGirl.OnPressRight();
	}

	if (nChar == VK_A) {
		fireBoy.OnPressLeft();
	}

	if (nChar == VK_D) {
		fireBoy.OnPressRight();
	}

	////////角色2 跳
	
	if (nChar == VK_UP && jumpable2 == true) {
		jump2 = true;
		jump2_time = clock();
	}
	
	bool flag2 = false;

	int foot_y = (waterGirl.foot.GetTop()) / 30;
	for (int j = foot_y; j < min(foot_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] != 0) {
				if (nChar == VK_UP && CMovingBitmap::IsOverlap(waterGirl.foot, map.map1[phase - 1][j][i]) == true) {
					flag2 = true;
					break;
				}
			}
		}
	}
	
	if (flag2 == true) {
		jump2 = true;
		jump2_time = clock();
		flag2 = false;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	////////角色2 放開左右移動
	if (nChar == VK_LEFT) {
		keepLeft = false;
		waterGirl.OnPressUp();
	}

	if (nChar == VK_RIGHT) {
		keepRight = false;
		waterGirl.OnPressUp();
	}

	if (nChar == VK_A || nChar == VK_D) {
		fireBoy.OnPressUp();
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	// 死亡畫面 retry
	if (isdead == true && (WM_LBUTTONDOWN)) {
		int idx1 = point.x;
		int idy1 = point.y;

		if (idx1 >= 752 && idy1 > 536 && idx1 <= 955 && idy1 <= 600) {
			button_retry.SetTopLeft(768, 530);
			button_retry.SetFrameIndexOfBitmap(1);
			button_retry.ShowBitmap();
			show_image_by_phase();
			isdead = false;
		}
		else if (idx1 >= 455 && idy1 > 536 && idx1 <= 661 && idy1 <= 600) {
			button_menu.SetTopLeft(450, 530);
			button_menu.SetFrameIndexOfBitmap(1);
			button_menu.ShowBitmap();
			ismenu = true;
			isdead = false;
		}
	}
	//call pause call 

	if ((WM_LBUTTONDOWN)) {
		int idx1 = point.x;
		int idy1 = point.y;
		if (idx1 >= 1350 && idy1 > 15 && idx1 <= 1383 && idy1 <= 51 ) {
			ispause = true;
		}
	}

	//pause meau

	if (ispause == true && (WM_LBUTTONDOWN)) {
		int idx1 = point.x;
		int idy1 = point.y;
		if (idx1 >= 752 && idy1 > 536 && idx1 <= 955 && idy1 <= 600) {
			button_retry.SetTopLeft(768, 530);
			button_retry.SetFrameIndexOfBitmap(1);
			button_retry.ShowBitmap();
			show_image_by_phase();

		}
		else if (idx1 >= 455 && idy1 > 536 && idx1 <= 661 && idy1 <= 600) {
			button_menu.SetTopLeft(450, 530);
			button_menu.SetFrameIndexOfBitmap(1);
			button_menu.ShowBitmap();
			ismenu = true;
			ispause = false;
		}
		else if (idx1 >= 610 && idy1 > 434 && idx1 <= 811 && idy1 <= 504) {
			ispause = false;
		}

	}

	//選關畫面
	if (ismenu == true && (WM_LBUTTONDOWN)) {
		int idx1 = point.x;
		int idy1 = point.y;
		if ((pass_phase >=0)&&idx1 >= 666 && idy1 > 742 && idx1 <= 730 && idy1 <= 822) {
			phase = 1;
			ismenu = false;
			ispause = false;
			isdead = false;
			show_image_by_phase();
		}
		else if ((pass_phase >= 1) && idx1 >= 722 && idy1 > 660 && idx1 <= 776 && idy1 <= 730) {
			phase = 2;
			ismenu = false;
			ispause = false;
			isdead = false;
			show_image_by_phase();
		}
		else if ((pass_phase >= 2) && idx1 >= 666 && idy1 > 584 && idx1 <= 730 && idy1 <= 644) {
			phase = 3;
			ismenu = false;
			ispause = false;
			isdead = false;
			show_image_by_phase();
		}
	}



	//continue
	if ((continue_what == 1 || continue_what == 2) && (WM_LBUTTONDOWN)) {
		int idx1 = point.x;
		int idy1 = point.y;
		if (idx1 >= 570 && idy1 > 580 && idx1 <= 850 && idy1 <= 650) {
			button_continue.SetFrameIndexOfBitmap(1);
			button_continue.ShowBitmap();
			button_continue_time = clock();
			show_image_by_phase();
		}
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}


void CGameStateRun::OnShow()
{
	/////////////////////////////////圖片 顯示///////////////////////////////////   


	bg.ShowBitmap();
	map.showMap(phase);

	pause.ShowBitmap();
	door.showObject(phase);
	button.showObject(phase);
	ramp.showObject(phase);
	box.showObject(phase);
	diamond.showObject(phase);
	joystick.showObject(phase);
	ball.showObject(phase);
	fan.showObject(phase);

	//箱子碰撞器
	box.box_left.SetTopLeft(box.box.GetLeft() - 5, box.box.GetTop());
	box.box_right.SetTopLeft(box.box.GetLeft() + 43, box.box.GetTop());
	

	//碰到寶石 寶石消失
	for (int i = 0; i < 8; i++) {
		if (CMovingBitmap::IsOverlap(fireBoy.GetBody(), diamond.red_diamond[i]) == true) {
			diamond.red_diamond[i].SetFrameIndexOfBitmap(1);
			diamond.red_diamond[i].SetTopLeft(0, 0);
			diamond_num++;
		}

		if (CMovingBitmap::IsOverlap(waterGirl.GetBody(), diamond.blue_diamond[i]) == true) {
			diamond.blue_diamond[i].SetFrameIndexOfBitmap(1);
			diamond.blue_diamond[i].SetTopLeft(0, 0);
			diamond_num++;
		}
	}
	
	//判斷吃到幾顆寶石
	eat_diamond = diamondNum();
	
	fireBoy.OnShow();
	waterGirl.OnShow();

	//人物碰到門 門打開 動畫
	if (CMovingBitmap::IsOverlap(fireBoy.rightArm, door.door1) == true && door.door1.GetFrameIndexOfBitmap() == 0) {
		door.door1.ToggleAnimation();
	}
	if (CMovingBitmap::IsOverlap(fireBoy.rightArm, door.door1) == false) {
		door.door1.SetFrameIndexOfBitmap(0);
	}

	if (CMovingBitmap::IsOverlap(waterGirl.rightArm, door.door2) == true && door.door2.GetFrameIndexOfBitmap() == 0) {
		door.door2.ToggleAnimation();
	}

	if (CMovingBitmap::IsOverlap(waterGirl.rightArm, door.door2) == false) {
		door.door2.SetFrameIndexOfBitmap(0);
	}

	

	//跳關卡
	if (GetAsyncKeyState(0x31) & 0x8000) {
		phase = 1;
		show_image_by_phase();
	}
	else if (GetAsyncKeyState(0x32) & 0x8000) {
		phase = 2;
		show_image_by_phase();

	}
	else if(GetAsyncKeyState(0x33) & 0x8000) {
		phase = 3;
		show_image_by_phase();
	}
	
	else if (GetAsyncKeyState(0x34) & 0x8000) {
		phase = 4;
		show_image_by_phase();
	}
	else if (GetAsyncKeyState(0x35) & 0x8000) {
		phase = 5;
		show_image_by_phase();
	}

	//按 0 不會死
	if (GetAsyncKeyState(0x30) & 0x8000) {
		test_no_dead = true;
	}
	//按 9 死
	if (GetAsyncKeyState(0x39) & 0x8000) {
		test_no_dead = false;

	}

	// 判斷通關條件
	if ((door.door1.GetFrameIndexOfBitmap() == 5 && door.door2.GetFrameIndexOfBitmap() == 5)) {

		if (phase == 1) {
			if (eat_diamond == 7) {
				continue_what = 1;
				phase += 1;
				show_image_by_phase();
			}
			else {
				button_continue.ShowBitmap();
				continue_what = 2;
				phase += 1;
				show_image_by_phase();
			}
			pass_phase = 1;
		}
		else if (phase == 2) {
			if (eat_diamond == 16) {
				continue_what = 1;
				phase += 1;
				show_image_by_phase();
			}
			else {
				button_continue.ShowBitmap();
				continue_what = 2;
				phase += 1;
				show_image_by_phase();
			}
			pass_phase = 2;
		}
		else if (phase == 3) {
			if (eat_diamond == 9) {
				continue_what = 1;
				phase += 1;
				show_image_by_phase();
			}
			else {
				button_continue.ShowBitmap();
				continue_what = 2;
				phase += 1;
				show_image_by_phase();
			}
			pass_phase = 3;
		}
		else if (phase == 4) {
			if (eat_diamond == 15) {
				continue_what = 1;
				phase += 1;
				show_image_by_phase();
			}
			else {
				button_continue.ShowBitmap();
				continue_what = 2;
				phase += 1;
				show_image_by_phase();
			}
			pass_phase = 4;
		}
		else if (phase == 5) {
			if (eat_diamond == 16) {
				continue_what = 1;
				phase += 1;
				show_image_by_phase();
			}
			else {
				button_continue.ShowBitmap();
				continue_what = 2;
				phase += 1;
				show_image_by_phase();
			}
			pass_phase = 5;
		}

	}

	

	//搖桿
	if (CMovingBitmap::IsOverlap(fireBoy.leftArm, joystick.joystick) == true && joystick.joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.joystick.ToggleAnimation();
	}
	if (CMovingBitmap::IsOverlap(fireBoy.rightArm, joystick.joystick) == true && joystick.joystick.GetFrameIndexOfBitmap() == 2) {
		joystick.joystick.SetFrameIndexOfBitmap(0);
	}
	if (CMovingBitmap::IsOverlap(waterGirl.leftArm, joystick.joystick) == true && joystick.joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.joystick.ToggleAnimation();
	}
	if (CMovingBitmap::IsOverlap(waterGirl.rightArm, joystick.joystick) == true && joystick.joystick.GetFrameIndexOfBitmap() == 2) {
		joystick.joystick.SetFrameIndexOfBitmap(0);
	}

	// red joystick
	if (CMovingBitmap::IsOverlap(fireBoy.leftArm, joystick.red_joystick) == true && joystick.red_joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.red_joystick.SetFrameIndexOfBitmap(1);
	}
	if (CMovingBitmap::IsOverlap(fireBoy.rightArm, joystick.red_joystick) == true && joystick.red_joystick.GetFrameIndexOfBitmap() == 1) {
		joystick.red_joystick.SetFrameIndexOfBitmap(0);
	}
	if (CMovingBitmap::IsOverlap(waterGirl.leftArm, joystick.red_joystick) == true && joystick.red_joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.red_joystick.SetFrameIndexOfBitmap(1);
	}
	if (CMovingBitmap::IsOverlap(waterGirl.rightArm, joystick.red_joystick) == true && joystick.red_joystick.GetFrameIndexOfBitmap() == 1) {
		joystick.red_joystick.SetFrameIndexOfBitmap(0);
	}

	// green joystick
	if (CMovingBitmap::IsOverlap(fireBoy.rightArm, joystick.green_joystick) == true && joystick.green_joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.green_joystick.SetFrameIndexOfBitmap(1);
	}
	if (CMovingBitmap::IsOverlap(fireBoy.leftArm, joystick.green_joystick) == true && joystick.green_joystick.GetFrameIndexOfBitmap() == 1) {
		joystick.green_joystick.SetFrameIndexOfBitmap(0);
	}
	if (CMovingBitmap::IsOverlap(waterGirl.rightArm, joystick.green_joystick) == true && joystick.green_joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.green_joystick.SetFrameIndexOfBitmap(1);
	}
	if (CMovingBitmap::IsOverlap(waterGirl.leftArm, joystick.green_joystick) == true && joystick.green_joystick.GetFrameIndexOfBitmap() == 1) {
		joystick.green_joystick.SetFrameIndexOfBitmap(0);
	}


	//死掉介面 0
	//繼續_ALL寶石介面 1
	//繼續_NOT ALL寶石介面 2
	// 初始選單介面 3

	//continue 畫面
	if (continue_what == 1) {
		scene.showScene(1);
		button_continue.ShowBitmap();
	}
	else if (continue_what == 2) {
		scene.showScene(2);
		button_continue.ShowBitmap();
	}

	//死亡畫面
	if (isdead == true) {
		scene.showScene(0);
		button_menu.ShowBitmap();
		button_retry.ShowBitmap();
		
		

	}


	//pause

	if (ispause == true) {
		scene.showScene(9);
		button_menu.ShowBitmap();
		button_retry.ShowBitmap();

	}


	//mune

	if (ismenu == true) {

		scene.showScene(pass_phase+3);
		
	}
	

	show_text_by_phase();
	
}


void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(256, 0, 256), 800);

	if (test_no_dead == true) {
		CTextDraw::Print(pDC, 237, 128, "現在不會死");
	}
	
	

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::gravety() {
	// 當角色1	沒有碰到 地板 以及 移動板，會往下掉
	bool gravity_flag1 = false;

	if (CheckMapComponentOverlap(fireBoy.foot)) {
		gravity_flag1 = true;
		jumpable1 = true;
	}

	int foot1_y = (fireBoy.foot.GetTop()) / 30;
	for (int j = foot1_y; j < min(foot1_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] != 0) {
				if (CMovingBitmap::IsOverlap(fireBoy.foot, map.map1[phase - 1][j][i]) == true) {
					jumpable1 = true;
					gravity_flag1 = true;
					break;
				}

			}
		}
	}

	if (gravity_flag1 == false) {
		fireBoy.SetTopLeft(fireBoy.GetLeft(), fireBoy.GetTop() + 5);
	}

	


	// 當角色2	沒有碰到 地板 以及 移動板，會往下掉
	bool gravity_flag2 = false;


	if (CheckMapComponentOverlap(waterGirl.foot)) {
		gravity_flag2 = true;
		jumpable2 = true;
	}

	int foot_y = (waterGirl.foot.GetTop()) / 30;
	for (int j = foot_y; j < min(foot_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] != 0) {
				if (CMovingBitmap::IsOverlap(waterGirl.foot, map.map1[phase - 1][j][i]) == true) {
					gravity_flag2 = true;
					jumpable2 = true;
					break;
				}
			}
		}
	}

	if (gravity_flag2 == false) {
		waterGirl.SetTopLeft(waterGirl.GetLeft(), waterGirl.GetTop() + 5);
	}



	// 箱子重力
	if (phase == 1 || phase == 4) {
		bool gravity_flag_box = false;

		if (CMovingBitmap::IsOverlap(box.box, ramp.ramp) == true && CMovingBitmap::IsOverlap(box.box, ramp.ramp2) == true) {
			gravity_flag_box = true;
		}


		int box_y = (box.box.GetTop()) / 30;
		for (int j = box_y; j < min(box_y + 3, 29); j++) {
			for (int i = 0; i < 40; i++) {
				if (map.int_map[phase - 1][j][i] != 0) {
					if (CMovingBitmap::IsOverlap(box.box, map.map1[phase - 1][j][i]) == true) {
						gravity_flag_box = true;
						break;
					}
				}
			}
		}

		if (gravity_flag_box == false) {
			box.box.SetTopLeft(box.box.GetLeft(), box.box.GetTop() + 5);
		}
	}

	// 球重力
	if (phase == 3) {
		bool gravity_flag_ball = false;
		bool gravity_flag_ball1 = false;

		if (CMovingBitmap::IsOverlap(ball.ball[0], ramp.purple_ramp) == true) {
			gravity_flag_ball = true;
		}
		if (CMovingBitmap::IsOverlap(ball.ball[1], ramp.white_ramp) == true) {
			gravity_flag_ball1 = true;
		}


		int ball_y = (ball.ball[0].GetTop()) / 30;
		for (int j = ball_y; j < min(ball_y + 3, 29); j++) {
			for (int i = 0; i < 40; i++) {
				if (map.int_map[phase - 1][j][i] != 0) {
					if (CMovingBitmap::IsOverlap(ball.ball[0], map.map1[phase - 1][j][i]) == true || CMovingBitmap::IsOverlap(ball.ball[0], ramp.purple_ramp3) == true) {
						gravity_flag_ball = true;
						break;
					}
				}
			}
		}

		int ball_y1 = (ball.ball[1].GetTop()) / 30;
		for (int j = ball_y1; j < min(ball_y1 + 3, 29); j++) {
			for (int i = 0; i < 40; i++) {
				if (map.int_map[phase - 1][j][i] != 0) {
					if (CMovingBitmap::IsOverlap(ball.ball[1], map.map1[phase - 1][j][i]) == true || CMovingBitmap::IsOverlap(ball.ball[1], ramp.purple_ramp3) == true) {
						gravity_flag_ball1 = true;
						break;
					}
				}
			}
		}

		if (gravity_flag_ball == false) {
			ball.ball[0].SetTopLeft(ball.ball[0].GetLeft(), ball.ball[0].GetTop() + 5);
		}
		if (gravity_flag_ball1 == false) {
			ball.ball[1].SetTopLeft(ball.ball[1].GetLeft(), ball.ball[1].GetTop() + 5);
		}

	}

}


void CGameStateRun::characterMove() {
	/////////////////////////////////////////////////////////////////////////////
	////	 角色 跳躍
	/////////////////////////////////////////////////////////////////////////////

	////	 角色 1 跳躍
	
	if (GetAsyncKeyState(0x57) & 0x8000 && jumpable1 == true) {
		jump1 = true;
		jump1_time = clock();
	}

	if (jump1 == true) {
		jumpable1 = false;
	}
	

	if (jump1 == true && (clock() - jump1_time) < 500) {
		fireBoy.SetTopLeft(fireBoy.GetLeft(), fireBoy.GetTop() - 10);
	}
	else if (jump1 == true && (clock() - jump1_time) < 560) {
		fireBoy.SetTopLeft(fireBoy.GetLeft(), fireBoy.GetTop() - 5);
	}
	else if (jump1 == true) {
		jump1 = false;
	}

	bool flag1 = false;

	int foot1_x = (fireBoy.foot.GetTop()) / 30;
	for (int j = foot1_x; j < min(foot1_x + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] != 0) {
				if (GetAsyncKeyState(0x57) & 0x8000 && CMovingBitmap::IsOverlap(fireBoy.foot, map.map1[phase - 1][j][i]) == true) {
					flag1 = true;
					break;
				}
			}
		}
	}

	if (flag1 == true) {
		jump1 = true;
		jump1_time = clock();
		flag1 = false;
	}


	////	 角色 2 跳躍
	if (jump2 == true) {
		jumpable2 = false;
	}

	if (jump2 == true && (clock() - jump2_time) < 500) {
		waterGirl.SetTopLeft(waterGirl.GetLeft(), waterGirl.GetTop() - 10);
	}
	else if (jump2 == true && (clock() - jump2_time) < 560) {
		waterGirl.SetTopLeft(waterGirl.GetLeft(), waterGirl.GetTop() - 5);
	}
	else if (jump2 == true) {
		jump2 = false;
	}

	/////////////////////////////////////////////////////////////////////////////
	////	 角色 頂頭
	/////////////////////////////////////////////////////////////////////////////

	////	 角色 1 頂頭 	////	 角色 1 碰到牆壁停止       //// 箱子碰到牆壁停止

	bool wall_left1 = false;
	bool wall_right1 = false;
	bool wall_box_right1 = false;
	bool wall_box_left1 = false;
	
	int head1_y = (fireBoy.head.GetTop()) / 30;

	// 判斷 character1 頭上的物件是否有重疊
	for (int j = head1_y; j >= max(head1_y - 4, 0); j--) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] != 0) {
				if (
					CMovingBitmap::IsOverlap(fireBoy.head, map.map1[phase-1][j][i]) || 
					CheckMapComponentOverlap(fireBoy.head)
				) {
					jump1 = false;
					break;
				}
			}
		}
	}

	
	for (int j = max(head1_y - 3, 0); j < min(head1_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] != 0) {
				if (CMovingBitmap::IsOverlap(fireBoy.leftArm, map.map1[phase - 1][j][i]) == true) {
					wall_left1 = true;
					break;
				}
				if (CMovingBitmap::IsOverlap(fireBoy.rightArm, map.map1[phase - 1][j][i]) == true) {
					wall_right1 = true;
					break;
				}
				if (CMovingBitmap::IsOverlap(box.box_left, map.map1[phase - 1][j][i]) == true ) {
					wall_box_left1 = true;
					break;
				}
				if (CMovingBitmap::IsOverlap(box.box_right, map.map1[phase - 1][j][i]) == true ) {
					wall_box_right1 = true;
					break;
				}
			}
		}
	}
	
	


	/////////////////////////////////////////////////////////////////////////////
	////	 角色 1 移動 箱子移動
	/////////////////////////////////////////////////////////////////////////////

	if (GetAsyncKeyState(VK_A) & 0x8000 && wall_left1 == false ) {  // 當角色1按 A 向左
		if (CMovingBitmap::IsOverlap(fireBoy.leftArm, box.box_right) == false) {
			fireBoy.SetTopLeft(fireBoy.GetLeft() - 8, fireBoy.GetTop());
		}
	}
	if (GetAsyncKeyState(VK_D) & 0x8000 && wall_right1 == false ) {  //當角色1按 D 向右
		if (CMovingBitmap::IsOverlap(fireBoy.rightArm, box.box_left) == false) {
			fireBoy.SetTopLeft(fireBoy.GetLeft() + 8, fireBoy.GetTop());
		}
	}

	
	//向左推
	if (CMovingBitmap::IsOverlap(fireBoy.leftArm, box.box) == true) {
		if (GetAsyncKeyState(0x41) & 0x8000 && wall_left1 == false && wall_box_left1 == false) {
			box.box.SetTopLeft(box.box.GetLeft() - 8, box.box.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(fireBoy.rightArm, box.box) == true) {
		if (GetAsyncKeyState(0x44) & 0x8000 && wall_right1 == false && wall_box_right1 == false ) {
			box.box.SetTopLeft(box.box.GetLeft() + 8, box.box.GetTop());
		}
	}

	////	 角色 2 頂頭 // 碰到地板左右停止
	bool wall_left2 = false;
	bool wall_right2 = false;
	bool wall_box_right2 = false;
	bool wall_box_left2 = false;


	int head2_y = (waterGirl.head.GetTop()) / 30;

	// 判斷 character2 頭上的物件是否有重疊
	for (int j = head2_y; j >= max(head2_y - 4, 0); j--) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] != 0) {
				if (
					CMovingBitmap::IsOverlap(waterGirl.head, map.map1[phase - 1][j][i]) ||
					CheckMapComponentOverlap(waterGirl.head)
					) {
					jump2 = false;
					break;
				}
			}
		}
	}

	for (int j = max(head2_y - 3, 0); j < min(head2_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] != 0) {
				if (CMovingBitmap::IsOverlap(waterGirl.leftArm, map.map1[phase - 1][j][i]) == true) {
					wall_left2 = true;
					break;
				}
				if (CMovingBitmap::IsOverlap(waterGirl.rightArm, map.map1[phase - 1][j][i]) == true) {
					wall_right2 = true;
					break;
				}
				if (CMovingBitmap::IsOverlap(box.box_right, map.map1[phase - 1][j][i]) == true) {
					wall_box_right2 = true;
					break;
				}
				if (CMovingBitmap::IsOverlap(box.box_left, map.map1[phase - 1][j][i]) == true) {
					wall_box_left2 = true;
				}
			}	
		}
	}

	////	 角色 2 移動 且 碰到牆壁停止

	if (keepLeft == true && wall_left2 == false) {
		if (CMovingBitmap::IsOverlap(waterGirl.leftArm, box.box_right) == false) {
			waterGirl.SetTopLeft(waterGirl.GetLeft() - 8, waterGirl.GetTop());
		}
	}
	if (keepRight == true && wall_right2 == false) {
		if (CMovingBitmap::IsOverlap(waterGirl.rightArm, box.box_left) == false) {
			waterGirl.SetTopLeft(waterGirl.GetLeft() + 8, waterGirl.GetTop());
		}
	}

	//人物二推箱子移動
	//向左推
	if (CMovingBitmap::IsOverlap(waterGirl.leftArm, box.box_right) == true) {
		if (keepLeft == true && wall_left2 == false && wall_box_left2 == false ) {
			box.box.SetTopLeft(box.box.GetLeft() - 8, box.box.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(waterGirl.rightArm, box.box_left) == true) {
		if (keepRight == true && wall_right2 == false && wall_box_right2 == false) {
			box.box.SetTopLeft(box.box.GetLeft() + 8, box.box.GetTop());
		}
	}

	// 角色碰到ramp 、green 、red 、ramp2 左右 停止 不會穿過 
	if (CheckMapComponentOverlap(fireBoy.leftArm)) {
		fireBoy.SetTopLeft(fireBoy.GetLeft() + 8, fireBoy.GetTop());
	}
	if (CheckMapComponentOverlap(fireBoy.rightArm)) {
		fireBoy.SetTopLeft(fireBoy.GetLeft() - 8, fireBoy.GetTop());
	}
	if (CheckMapComponentOverlap(waterGirl.leftArm)) {
		waterGirl.SetTopLeft(waterGirl.GetLeft() + 8, waterGirl.GetTop());
	}
	if (CheckMapComponentOverlap(waterGirl.rightArm)) {
		waterGirl.SetTopLeft(waterGirl.GetLeft() - 8, waterGirl.GetTop());
	}
}

void CGameStateRun::BallMove(CMovingBitmap &ball, Character &character) {
	if (CMovingBitmap::IsOverlap(character.leftArm, ball) == true) {
		if (character.IsLeftWalking()) {
			ball.SetTopLeft(ball.GetLeft() - 8, ball.GetTop());
		}
	}
	if (CMovingBitmap::IsOverlap(character.rightArm, ball) == true && 
		!map.IsBlock(phase-1, ball.GetLeft() + ball.GetWidth() + 8, ball.GetTop())) {
		if (character.IsRightWalking()) {
			ball.SetTopLeft(ball.GetLeft() + 8, ball.GetTop());
		}
	}
	if (CMovingBitmap::IsOverlap(character.foot, ball) == true) {
		character.SetTopLeft(character.GetLeft(), character.GetTop() - 5);
	}
}
void CGameStateRun::show_image_by_phase() {

	/////////////////////////////////////////////////////////
	//////////// 物件在不同關卡的初始位置 //////////////////////
	////////////////////////////////////////////////////////

	if (phase <= 6) {
		door.setObject(phase);
		button.setObject(phase);
		ramp.setObject(phase);
		box.setObject(phase);
		diamond.setObject(phase);
		joystick.setObject(phase);
		ball.setObject(phase);
		fan.setObject(phase);

		if (phase == 1 && sub_phase == 1) {
			// 角色與箱子
			fireBoy.SetTopLeft(25, 640);  //25, 640
			waterGirl.SetTopLeft(25, 760);

		}
		if (phase == 2 && sub_phase == 1) {
			fireBoy.SetTopLeft(25, 640);
			waterGirl.SetTopLeft(25, 760);
		}

		if (phase == 3 && sub_phase == 1) {
			fireBoy.SetTopLeft(50, 50);
			waterGirl.SetTopLeft(100, 50);
		}
		if (phase == 4 && sub_phase == 1) {
			fireBoy.SetTopLeft(50, 700);
			waterGirl.SetTopLeft(100, 700);

		}
		if (phase == 5 && sub_phase == 1) {
			fireBoy.SetTopLeft(30, 750);
			waterGirl.SetTopLeft(1300, 750);
		}

		pause.SetTopLeft(1350, 15);
		for (int i = 0; i < 8; i++) {
			diamond.red_diamond[i].SetFrameIndexOfBitmap(0);
			diamond.blue_diamond[i].SetFrameIndexOfBitmap(0);
		}

		diamond_num = 0;
		isdead = false;
		ispause = false;

		door.door1.SetFrameIndexOfBitmap(0);
		door.door2.SetFrameIndexOfBitmap(0);

		if (phase == 6 && sub_phase == 1) {
			scene.showScene(10);
			GotoGameState(GAME_STATE_OVER);
		}
	}
}


//寶石記數
int CGameStateRun::diamondNum() {
	for (int i = 0; i < 8; i++) {
		if (CMovingBitmap::IsOverlap(fireBoy.GetBody(), diamond.red_diamond[i]) == true) {
			diamond_num++;
		}
		if (CMovingBitmap::IsOverlap(waterGirl.GetBody(), diamond.blue_diamond[i]) == true) {
			diamond_num++;
		}
	}
	return diamond_num;
}

bool CGameStateRun::CheckMapComponentOverlap(CMovingBitmap charactor_part) {
	return (
		CMovingBitmap::IsOverlap(charactor_part, ramp.ramp) == true ||
		CMovingBitmap::IsOverlap(charactor_part, ramp.ramp2) == true ||
		CMovingBitmap::IsOverlap(charactor_part, ramp.purple_ramp) == true ||
		CMovingBitmap::IsOverlap(charactor_part, box.box) == true||
		CMovingBitmap::IsOverlap(charactor_part, ramp.green_ramp) == true ||
		CMovingBitmap::IsOverlap(charactor_part, ramp.red_ramp) == true ||
		CMovingBitmap::IsOverlap(charactor_part, ramp.white_ramp) == true
	);
}

