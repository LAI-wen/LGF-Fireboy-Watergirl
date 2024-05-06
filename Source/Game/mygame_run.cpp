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
	
	gravety();

	characterMove();
	boxMove();
	ballMove();

	
	
	/////////////////////////////////////////////////////////////////////////////
	////	 機關
	/////////////////////////////////////////////////////////////////////////////
	
	//機關
	
	if (phase == 1 || phase == 2) {

		//角色 1  2 和箱子 碰到 button1 會按下
		if (CMovingBitmap::IsOverlap(foot2, button.button1) == true || CMovingBitmap::IsOverlap(foot1, button.button1) == true || CMovingBitmap::IsOverlap(box.box, button.button1) == true) {
			button.button1.SetTopLeft(button.button1.GetLeft(), button.button1.GetTop() + 1);
		}
		else if (button.button1.GetTop() > button.button1_y) {
			button.button1.SetTopLeft(button.button1.GetLeft(), button.button1.GetTop() - 2);
		}
		else if (button.button1.GetTop() == button.button1_y + 15) {
			button.button1.SetTopLeft(button.button1.GetLeft(), button.button1.GetTop());
		}

		//角色 1  2 和箱子 碰到 button2 會按下

		if (CMovingBitmap::IsOverlap(foot2, button.button2) == true || CMovingBitmap::IsOverlap(foot1, button.button2) == true) {
			button.button2.SetTopLeft(button.button2.GetLeft(), button.button2.GetTop() + 1);
		}
		else if (button.button2.GetTop() > button.button2_y) {
			button.button2.SetTopLeft(button.button2.GetLeft(), button.button2.GetTop() - 2);
		}
		else if (button.button2.GetTop() == button.button2_y + 15) {
			button.button2.SetTopLeft(button.button2.GetLeft(), button.button2.GetTop());
		}

	}
	else if (phase == 2) {

	}



	

	if (phase == 1) {
		// button1 && button2 操控 ramp2
		if (button.button1.GetTop() > button.button1_y || button.button2.GetTop() > button.button2_y) {
			ramp.ramp2.SetTopLeft(ramp.ramp2.GetLeft(), min(ramp.ramp2_y2, ramp.ramp2.GetTop() + 5));
		}
		else {
			ramp.ramp2.SetTopLeft(ramp.ramp2.GetLeft(), max(ramp.ramp2_y1, ramp.ramp2.GetTop() - 5));
		}

	}
	else if (phase == 2) {
		// button1 && button2 操控 white ramp
		if (button.button1.GetTop() > button.button1_y || button.button2.GetTop() > button.button2_y) {
			ramp.white_ramp.SetTopLeft(ramp.white_ramp.GetLeft(), max(ramp.white_ramp_y2, ramp.white_ramp.GetTop() - 5));
		}
		else {
			ramp.white_ramp.SetTopLeft(ramp.white_ramp.GetLeft(), min(ramp.white_ramp_y1, ramp.white_ramp.GetTop() + 5));
		}

		// purple button 操控 purple ramp
		if (button.purple_button[0].GetTop() > button.purple_button_y[0] || button.purple_button[1].GetTop() > button.purple_button_y[1]) {
			ramp.purple_ramp.SetTopLeft(max(ramp.purple_ramp_x2, ramp.purple_ramp.GetLeft() - 5), ramp.purple_ramp.GetTop());
		}
		else {
			ramp.purple_ramp.SetTopLeft(min(ramp.purple_ramp_x1, ramp.purple_ramp.GetLeft() + 5), ramp.purple_ramp.GetTop());
		}

	}
	else if (phase == 3) {
		
		// purple button[0] 操控 purple ramp3
		if (button.purple_button[0].GetTop() > button.purple_button_y[0]) {
			ramp.purple_ramp3.SetTopLeft(min(ramp.purple_ramp3_x2, ramp.purple_ramp3.GetLeft() + 5), ramp.purple_ramp3.GetTop());
		}
		else {
			ramp.purple_ramp3.SetTopLeft(max(ramp.purple_ramp3_x1, ramp.purple_ramp3.GetLeft() - 5), ramp.purple_ramp3.GetTop());
		}
		
		// white button 操控 short white ramp
		if (button.white_button.GetTop() > button.white_button_y) {
			ramp.short_white_ramp.SetTopLeft(ramp.short_white_ramp.GetLeft(), min(ramp.short_white_ramp_y2, ramp.short_white_ramp.GetTop() + 5));
		}
		else {
			ramp.short_white_ramp.SetTopLeft(ramp.short_white_ramp.GetLeft(), max(ramp.short_white_ramp_y1, ramp.short_white_ramp.GetTop() - 5));
		}


	}
	

	
	
	// purple button
	for (int i = 0; i < 2; i++) {
		if (CMovingBitmap::IsOverlap(foot1, button.purple_button[i]) == true || CMovingBitmap::IsOverlap(foot2, button.purple_button[i]) == true || CMovingBitmap::IsOverlap(ball.ball[0], button.purple_button[i]) == true) {
			button.purple_button[i].SetTopLeft(button.purple_button[i].GetLeft(), button.purple_button[i].GetTop() + 1);
		}
		else if (button.purple_button[i].GetTop() > button.purple_button_y[i]) {
			button.purple_button[i].SetTopLeft(button.purple_button[i].GetLeft(), button.purple_button[i].GetTop() - 2);
		}
		else if (button.purple_button[i].GetTop() == button.purple_button_y[i] + 15) {
			button.purple_button[i].SetTopLeft(button.purple_button[i].GetLeft(), button.purple_button[i].GetTop());
		}
	}

	// white button
	if (CMovingBitmap::IsOverlap(ball.ball[1], button.white_button) == true) {
		button.white_button.SetTopLeft(button.white_button.GetLeft(), button.white_button.GetTop() + 1);
	}
	else if (button.white_button.GetTop() > button.white_button_y) {
		button.white_button.SetTopLeft(button.white_button.GetLeft(), button.white_button.GetTop() - 2);
	}
	else if (button.white_button.GetTop() == button.white_button_y + 15) {
		button.white_button.SetTopLeft(button.white_button.GetLeft(), button.white_button.GetTop());
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




	//碰到水池死亡
	//角色一
	if (CMovingBitmap::IsOverlap(foot1, pond.pond) == true) {
		isdead = true;
	}
	else if (CMovingBitmap::IsOverlap(foot1, pond.blue_pond[0]) == true) {
		isdead = true;

	}

	for (int i = 0; i < 2; i++) {
		if (CMovingBitmap::IsOverlap(foot1, pond.long_pond[i]) == true)
			isdead = true;
		else if (CMovingBitmap::IsOverlap(foot1, pond.long_blue_pond[i]) == true)
			isdead = true;
	}
	
	//角色二
	if (CMovingBitmap::IsOverlap(foot2, pond.pond) == true) {
		isdead = true;
	}
	else if (CMovingBitmap::IsOverlap(foot2, pond.red_pond) == true) {
		isdead = true;
	}

	for (int i = 0; i < 2; i++) {
		if (CMovingBitmap::IsOverlap(foot2, pond.long_pond[i]) == true)
			isdead = true;
		else if (CMovingBitmap::IsOverlap(foot2, pond.long_red_pond[i]) == true)
			isdead = true;
	}

	

	//死亡介面按鈕


	if (isdead == true && clock() - button_retry_time == 21000) {
		button_retry.SetFrameIndexOfBitmap(0);
		button_retry.ShowBitmap();
	}



	if (clock() - button_continue_time == 21000) {
		button_continue.SetFrameIndexOfBitmap(0);
		button_continue.ShowBitmap();
	}
	else if (clock() - button_continue_time <= 25500) {
		continue_what = 0;
	}
	
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//背景
	bg.LoadBitmapByString({ "Resources/bg.bmp" });
	bg.SetTopLeft(0, 0);

	/////////////////////////////////////////////////////////////////////////////
	//////////////////////////////地板 依關卡改所需方格數////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	
	map.generateMap();
	scene.loadScene();
	door.generateObject();
	button.generateObject();
	ramp.generateObject();
	box.generateObject();
	pond.generateObject();
	diamond.generateObject();
	joystick.generateObject();
	ball.generateObject();

	pause.LoadBitmapByString({ "Resources/pause_img.bmp" }, RGB(255, 255, 255));;
	

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////角色////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////角色 1 圖片讀取////////////////////////////////////////
	//角色 1 碰撞感測器 圖片讀取
	foot1.LoadBitmapByString({ "Resources/foot.bmp" }, RGB(255, 255, 255));
	head1.LoadBitmapByString({ "Resources/head.bmp" }, RGB(255, 255, 255));
	character1_left.LoadBitmapByString({ "Resources/left.bmp" }, RGB(255, 255, 255));
	character1_right.LoadBitmapByString({ "Resources/left.bmp" }, RGB(255, 255, 255));

	
	character1[0].LoadBitmapByString({ "Resources/fireboy.bmp", "Resources/character_ignore.bmp" }, RGB(255, 255, 255));


	character1[2].LoadBitmapByString({ "Resources/fireboy(1_0).bmp",
										"Resources/fireboy(1_1).bmp",
										"Resources/fireboy(1_2).bmp",
										"Resources/fireboy(1_3).bmp",
										"Resources/fireboy(1_4).bmp",
										"Resources/fireboy(1_5).bmp",
										"Resources/fireboy(1_6).bmp",
										"Resources/fireboy(1_7).bmp" }, RGB(255, 255, 255));

	character1[1].LoadBitmapByString({ "Resources/fireboy(2_0).bmp",
									   "Resources/fireboy(2_1).bmp",
									   "Resources/fireboy(2_2).bmp",
									   "Resources/fireboy(2_3).bmp",
									   "Resources/fireboy(2_4).bmp",
									   "Resources/fireboy(2_5).bmp",
									   "Resources/fireboy(2_6).bmp",
									   "Resources/fireboy(2_7).bmp" }, RGB(255, 255, 255));

	

	/////////////////////////////////角色 2 圖片讀取////////////////////////////////////////

	character2[0].LoadBitmapByString({ "Resources/watergirl_sprite (0_0).bmp", "Resources/character_ignore.bmp" }, RGB(255, 255, 255));


	character2[1].LoadBitmapByString({ "Resources/watergirl_sprite (1_0).bmp",
										"Resources/watergirl_sprite (1_1).bmp",
										"Resources/watergirl_sprite (1_2).bmp",
										"Resources/watergirl_sprite (1_3).bmp",
										"Resources/watergirl_sprite (1_4).bmp",
										"Resources/watergirl_sprite (1_5).bmp",
										"Resources/watergirl_sprite (1_6).bmp",
										"Resources/watergirl_sprite (1_7).bmp"
		}, RGB(255, 255, 255));

	character2[2].LoadBitmapByString({ "Resources/watergirl_sprite (2_0).bmp",
									"Resources/watergirl_sprite (2_1).bmp",
									"Resources/watergirl_sprite (2_2).bmp",
									"Resources/watergirl_sprite (2_3).bmp",
									"Resources/watergirl_sprite (2_4).bmp",
									"Resources/watergirl_sprite (2_5).bmp",
									"Resources/watergirl_sprite (2_6).bmp",
									"Resources/watergirl_sprite (2_7).bmp"
		}, RGB(255, 255, 255));


	//角色2碰撞感測器 圖片讀取
	foot2.LoadBitmapByString({ "Resources/foot.bmp" }, RGB(255, 255, 255));
	head2.LoadBitmapByString({ "Resources/head.bmp" }, RGB(255, 255, 255));
	character2_left.LoadBitmapByString({ "Resources/left.bmp" }, RGB(255, 255, 255));
	character2_right.LoadBitmapByString({ "Resources/left.bmp" }, RGB(255, 255, 255));
	
	


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

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////角色 2 移動按鈕 ////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	////////角色2左右移動
	if (nChar == VK_LEFT) {
		keepLeft = true;
		character2[2].SetAnimation(100, false);
	}

	if (nChar == VK_RIGHT) {
		keepRight = true;
		character2[1].SetAnimation(100, false);
	}


	////////角色2 跳
	
	if (nChar == VK_UP && (CMovingBitmap::IsOverlap(foot2, ramp.ramp) == true || CMovingBitmap::IsOverlap(foot2, ramp.ramp2) == true || CMovingBitmap::IsOverlap(foot2, box.box) == true)) {
		jump2 = true;
		jump2_time = clock();
	}
	
	bool flag2 = false;

	int foot2_y = (foot2.GetTop()) / 30;
	for (int j = foot2_y; j < min(foot2_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] == 1) {
				if (nChar == VK_UP && CMovingBitmap::IsOverlap(foot2, map.map1[phase - 1][j][i]) == true) {
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
	}

	if (nChar == VK_RIGHT) {
		keepRight = false;
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
			button_retry_time = clock();
			show_image_by_phase();

		}
		else if (idx1 >= 455 && idy1 > 536 && idx1 <= 661 && idy1 <= 600) {
			button_menu.SetTopLeft(450, 530);
			button_menu.SetFrameIndexOfBitmap(1);
			button_menu.ShowBitmap();
			button_menu_time = clock();
			ismenu = true;
			isdead == false;
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
			button_retry_time = clock();
			show_image_by_phase();

		}
		else if (idx1 >= 455 && idy1 > 536 && idx1 <= 661 && idy1 <= 600) {
			button_menu.SetTopLeft(450, 530);
			button_menu.SetFrameIndexOfBitmap(1);
			button_menu.ShowBitmap();
			button_menu_time = clock();
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
			show_image_by_phase();
			ismenu = false;
			ispause = false;
			isdead = false;

		}
		else if ((pass_phase >= 1) && idx1 >= 722 && idy1 > 660 && idx1 <= 776 && idy1 <= 730) {
			phase = 2;
			show_image_by_phase();
			ismenu = false;
			ispause = false;
			isdead = false;
		}
		else if ((pass_phase >= 2) && idx1 >= 666 && idy1 > 584 && idx1 <= 730 && idy1 <= 644) {
			phase = 3;
			show_image_by_phase();
			ismenu = false;
			ispause = false;
			isdead = false;
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


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////圖片 顯示///////////////////////////////////   
/////////////////////////////////////////////////////////////////////////////

void CGameStateRun::OnShow()
{

	//暫停

	

	//地圖
	bg.ShowBitmap();
	

	
	map.showMap(phase);
	pause.ShowBitmap();


	door.showObject(phase);
	button.showObject(phase);
	ramp.showObject(phase);
	box.showObject(phase);
	pond.showObject(phase);
	diamond.showObject(phase);
	joystick.showObject(phase);
	ball.showObject(phase);


	
	box.box_left.SetTopLeft(box.box.GetLeft() - 5, box.box.GetTop());
	box.box_right.SetTopLeft(box.box.GetLeft() + 43, box.box.GetTop());
	
	

	
	//吃寶石
	for (int i = 0; i < 8; i++) {
		if (CMovingBitmap::IsOverlap(character1[0], diamond.red_diamond[i]) == true) {
			diamond.red_diamond[i].SetFrameIndexOfBitmap(1);
			diamond.red_diamond[i].SetTopLeft(0, 0);
			diamond_num++;
		}

		if (CMovingBitmap::IsOverlap(character2[0], diamond.blue_diamond[i]) == true) {
			diamond.blue_diamond[i].SetFrameIndexOfBitmap(1);
			diamond.blue_diamond[i].SetTopLeft(0, 0);
			diamond_num++;
		}
	}
	
	
	//判斷吃幾顆寶石
	eat_diamond = diamondNum();
	

	
	

	

	///////////////////////人物與動畫//////////////////////////////////////
	// character1
	//角色碰撞感測器
	foot1.SetTopLeft(character1[0].GetLeft() + 25, character1[0].GetTop() + 82);
	foot1.ShowBitmap();

	head1.SetTopLeft(character1[0].GetLeft() + 25, character1[0].GetTop() + 10);
	head1.ShowBitmap();

	character1_left.SetTopLeft(character1[0].GetLeft() + 5, character1[0].GetTop() + 25);
	character1_left.ShowBitmap();
	character1_right.SetTopLeft(character1[0].GetLeft() + 50, character1[0].GetTop() + 30);
	character1_right.ShowBitmap();
	
	//角色跑步動畫
	if (GetAsyncKeyState(0x41) & 0x8000) {
		character1[1].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop());
		character1[1].ShowBitmap();
	}
	else if (GetAsyncKeyState(0x44) & 0x8000)
	{
		character1[2].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop());
		character1[2].ShowBitmap();
	}
	else {
		character1[0].ShowBitmap();
	}




	// character2
	//角色碰撞感測器
	foot2.SetTopLeft(character2[0].GetLeft() + 39, character2[0].GetTop() + 95);
	foot2.ShowBitmap();

	head2.SetTopLeft(character2[0].GetLeft() + 39, character2[0].GetTop() + 20);
	head2.ShowBitmap();

	character2_left.SetTopLeft(character2[0].GetLeft() + 22, character2[0].GetTop() + 35);
	character2_left.ShowBitmap();
	character2_right.SetTopLeft(character2[0].GetLeft() + 66, character2[0].GetTop() + 35);
	character2_right.ShowBitmap();

	//角色跑步動畫
	if (keepRight) {

		character2[1].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
		character2[1].ShowBitmap();
	}
	else if (keepLeft)
	{
		character2[2].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
		character2[2].ShowBitmap();
	}
	else {
		character2[0].ShowBitmap();

	}


	

	//門動畫
	if (CMovingBitmap::IsOverlap(character1_right, door.door1) == true && door.door1.GetFrameIndexOfBitmap() == 0) {
		door.door1.ToggleAnimation();
	}

	if (CMovingBitmap::IsOverlap(character2_right, door.door2) == true && door.door2.GetFrameIndexOfBitmap() == 0) {
		door.door2.ToggleAnimation();
	}

	//跳關卡
	if (GetAsyncKeyState(0x32) & 0x8000) {
		phase = 2;
		show_image_by_phase();

	}
	else if(GetAsyncKeyState(0x33) & 0x8000) {
		phase = 3;
		show_image_by_phase();
	}
	else if (GetAsyncKeyState(0x31) & 0x8000) {
		phase = 1;
		show_image_by_phase();
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
		}else if (phase == 2) {
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
		
		
		


	}

	


	
	//搖桿
	if (CMovingBitmap::IsOverlap(character1_left, joystick.joystick) == true && joystick.joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.joystick.ToggleAnimation();
	}
	if (CMovingBitmap::IsOverlap(character1_right, joystick.joystick) == true && joystick.joystick.GetFrameIndexOfBitmap() == 2) {
		joystick.joystick.SetFrameIndexOfBitmap(0);
	}
	if (CMovingBitmap::IsOverlap(character2_left, joystick.joystick) == true && joystick.joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.joystick.ToggleAnimation();
	}
	if (CMovingBitmap::IsOverlap(character2_right, joystick.joystick) == true && joystick.joystick.GetFrameIndexOfBitmap() == 2) {
		joystick.joystick.SetFrameIndexOfBitmap(0);
	}

	// red joystick
	if (CMovingBitmap::IsOverlap(character1_left, joystick.red_joystick) == true && joystick.red_joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.red_joystick.SetFrameIndexOfBitmap(1);
	}
	if (CMovingBitmap::IsOverlap(character1_right, joystick.red_joystick) == true && joystick.red_joystick.GetFrameIndexOfBitmap() == 1) {
		joystick.red_joystick.SetFrameIndexOfBitmap(0);
	}
	if (CMovingBitmap::IsOverlap(character2_left, joystick.red_joystick) == true && joystick.red_joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.red_joystick.SetFrameIndexOfBitmap(1);
	}
	if (CMovingBitmap::IsOverlap(character2_right, joystick.red_joystick) == true && joystick.red_joystick.GetFrameIndexOfBitmap() == 1) {
		joystick.red_joystick.SetFrameIndexOfBitmap(0);
	}

	// green joystick
	if (CMovingBitmap::IsOverlap(character1_right, joystick.green_joystick) == true && joystick.green_joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.green_joystick.SetFrameIndexOfBitmap(1);
	}
	if (CMovingBitmap::IsOverlap(character1_left, joystick.green_joystick) == true && joystick.green_joystick.GetFrameIndexOfBitmap() == 1) {
		joystick.green_joystick.SetFrameIndexOfBitmap(0);
	}
	if (CMovingBitmap::IsOverlap(character2_right, joystick.green_joystick) == true && joystick.green_joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.green_joystick.SetFrameIndexOfBitmap(1);
	}
	if (CMovingBitmap::IsOverlap(character2_left, joystick.green_joystick) == true && joystick.green_joystick.GetFrameIndexOfBitmap() == 1) {
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
	







	
}

void CGameStateRun::gravety() {
	
	// 當角色1	沒有碰到 地板 以及 移動板，會往下掉
	bool gravity_flag1 = false;

	if (CMovingBitmap::IsOverlap(foot1, ramp.ramp) == true || CMovingBitmap::IsOverlap(foot1, ramp.ramp2) == true || CMovingBitmap::IsOverlap(foot1, ramp.purple_ramp) == true) {
		gravity_flag1 = true;
	}

	int foot1_y = (foot1.GetTop()) / 30;
	for (int j = foot1_y; j < min(foot1_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] == 1) {
				if (CMovingBitmap::IsOverlap(foot1, map.map1[phase - 1][j][i]) == true) {
					gravity_flag1 = true;
					break;
				}

			}
		}
	}

	if (gravity_flag1 == false) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() + 5);
	}

	//角色碰到機關移動時會跟著移動
	// ramp1
	if (CMovingBitmap::IsOverlap(foot1, ramp.ramp) == true && ramp.ramp.GetTop() > ramp.ramp_y1 && ramp.ramp.GetTop() != ramp.ramp_y2) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}

	if (CMovingBitmap::IsOverlap(foot2, ramp.ramp) == true && ramp.ramp.GetTop() > ramp.ramp_y1 && ramp.ramp.GetTop() != ramp.ramp_y2) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}

	// ramp2
	if (CMovingBitmap::IsOverlap(foot1, ramp.ramp2) == true && ramp.ramp2.GetTop() > ramp.ramp2_y1 && ramp.ramp2.GetTop() != ramp.ramp2_y2) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}

	if (CMovingBitmap::IsOverlap(foot2, ramp.ramp2) == true && ramp.ramp2.GetTop() > ramp.ramp2_y1 && ramp.ramp2.GetTop() != ramp.ramp2_y2) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}


	// 當角色2	沒有碰到 地板 以及 移動板，會往下掉
	bool gravity_flag2 = false;

	if (CMovingBitmap::IsOverlap(foot2, ramp.ramp) == true || CMovingBitmap::IsOverlap(foot2, ramp.ramp2) == true || CMovingBitmap::IsOverlap(foot2, ramp.purple_ramp) == true) {
		gravity_flag2 = true;
	}

	int foot2_y = (foot2.GetTop()) / 30;
	for (int j = foot2_y; j < min(foot2_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] == 1) {
				if (CMovingBitmap::IsOverlap(foot2, map.map1[phase - 1][j][i]) == true) {
					gravity_flag2 = true;
					break;
				}
			}
		}
	}

	if (gravity_flag2 == false) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() + 5);
	}

	// 箱子重力
	if (phase == 1) {
		bool gravity_flag_box = false;

		if (CMovingBitmap::IsOverlap(box.box, ramp.ramp) == true) {
			gravity_flag_box = true;
		}


		int box_y = (box.box.GetTop()) / 30;
		for (int j = box_y; j < min(box_y + 3, 29); j++) {
			for (int i = 0; i < 40; i++) {
				if (map.int_map[phase - 1][j][i] == 1) {
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
				if (map.int_map[phase - 1][j][i] == 1) {
					if (CMovingBitmap::IsOverlap(ball.ball[0], map.map1[phase - 1][j][i]) == true) {
						gravity_flag_ball = true;
						break;
					}
				}
			}
		}

		int ball_y1 = (ball.ball[1].GetTop()) / 30;
		for (int j = ball_y1; j < min(ball_y1 + 3, 29); j++) {
			for (int i = 0; i < 40; i++) {
				if (map.int_map[phase - 1][j][i] == 1) {
					if (CMovingBitmap::IsOverlap(ball.ball[1], map.map1[phase - 1][j][i]) == true) {
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

	if (GetAsyncKeyState(0x57) & 0x8000 && (CMovingBitmap::IsOverlap(foot1, ramp.ramp) == true || CMovingBitmap::IsOverlap(foot1, ramp.ramp2) == true || CMovingBitmap::IsOverlap(foot1, ramp.purple_ramp) == true || CMovingBitmap::IsOverlap(foot1, box.box) == true)) {
		jump1 = true;
		jump1_time = clock();
	}

	if (jump1 == true && (clock() - jump1_time) < 500) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 10);
	}
	else if (jump1 == true && (clock() - jump1_time) < 560) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}
	else if (jump1 == true) {
		jump1 = false;
	}

	bool flag1 = false;

	int foot1_x = (foot1.GetTop()) / 30;
	for (int j = foot1_x; j < min(foot1_x + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] == 1) {
				if (GetAsyncKeyState(0x57) & 0x8000 && CMovingBitmap::IsOverlap(foot1, map.map1[phase - 1][j][i]) == true) {
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
	if (jump2 == true && (clock() - jump2_time) < 500) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 10);
	}
	else if (jump2 == true && (clock() - jump2_time) < 560) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}
	else if (jump2 == true) {
		jump2 = false;
	}

	/////////////////////////////////////////////////////////////////////////////
	////	 角色 頂頭
	/////////////////////////////////////////////////////////////////////////////

	////	 角色 1 頂頭 	////	 角色 1 碰到牆壁停止       //// 箱子碰到牆壁停止

	bool wall_left1 = true;
	bool wall_right1 = true;
	bool box_moveleft = true;
	bool box_moveright = true;

	int head1_y = (head1.GetTop()) / 30;

	// 判斷 character1 頭上的物件是否有重疊
	for (int j = head1_y; j >= head1_y - 4; j--) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] == 1) {
				if (
					CMovingBitmap::IsOverlap(head1, map.map1[phase-1][j][i]) || 
					CMovingBitmap::IsOverlap(head1, ramp.ramp) || 
					CMovingBitmap::IsOverlap(foot1, ramp.ramp2) || 
					CMovingBitmap::IsOverlap(foot1, ramp.purple_ramp)
				) {
					jump1 = false;
					break;
				}
			}
		}
	}
	for (int j = head1_y - 3; j < min(head1_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] == 1) {
				if (CMovingBitmap::IsOverlap(character1_left, map.map1[phase - 1][j][i]) == true) {
					wall_left1 = false;
					break;
				}
				if (CMovingBitmap::IsOverlap(character1_right, map.map1[phase - 1][j][i]) == true) {
					wall_right1 = false;
					break;
				}
				if (CMovingBitmap::IsOverlap(box.box_left, map.map1[phase - 1][j][i]) == true) {
					box_moveleft = false;
					break;
				}
				if (CMovingBitmap::IsOverlap(box.box_right, map.map1[phase - 1][j][i]) == true) {
					box_moveright = false;
					break;
				}
			}
		}
	}

	if (wall_left1 == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 8, character1[0].GetTop());
	}
	if (wall_right1 == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 8, character1[0].GetTop());
	}


	if (box_moveleft == true) {
		box.box.SetTopLeft(box.box.GetLeft() - 8, box.box.GetTop());
	}
	if (box_moveright == true) {
		box.box.SetTopLeft(box.box.GetLeft() + 8, box.box.GetTop());
	}

	if (box_moveleft == true && CMovingBitmap::IsOverlap(box.box, character1[0]) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 8, character1[0].GetTop());
	}
	if (box_moveright == true && CMovingBitmap::IsOverlap(box.box, character1[0]) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 8, character1[0].GetTop());
	}

	if (box_moveleft == true && CMovingBitmap::IsOverlap(box.box, character2[0]) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 8, character2[0].GetTop());
	}
	if (box_moveright == true && CMovingBitmap::IsOverlap(box.box, character2[0]) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 8, character2[0].GetTop());
	}




	////	 角色 2 頂頭 // 碰到地板左右停止
	bool wall_left2 = true;
	bool wall_right2 = true;

	int head2_y = (head2.GetTop()) / 30;
	for (int j = head2_y; j < min(head2_y + 3, 29); j++) {
		for (int i = 0; i < 40; i++) {
			if (map.int_map[phase - 1][j][i] == 1) {
				if (CMovingBitmap::IsOverlap(head2, map.map1[phase - 1][j][i]) == true || CMovingBitmap::IsOverlap(head2, ramp.ramp) == true || CMovingBitmap::IsOverlap(head2, ramp.ramp2) == true || CMovingBitmap::IsOverlap(head2, ramp.purple_ramp) == true) {
					jump2 = false;
				}

				if (CMovingBitmap::IsOverlap(character2_left, map.map1[phase - 1][j][i]) == true) {
					wall_left2 = false;
					break;
				}
				if (CMovingBitmap::IsOverlap(character2_right, map.map1[phase - 1][j][i]) == true) {
					wall_right2 = false;
					break;
				}
			}
		}
	}


	// 角色碰到ramp 停止 
	if (CMovingBitmap::IsOverlap(character1_left, ramp.ramp) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 8, character1[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character1_right, ramp.ramp) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 8, character1[0].GetTop());
	}

	if (CMovingBitmap::IsOverlap(character2_left, ramp.ramp) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 8, character2[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character2_right, ramp.ramp) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 8, character2[0].GetTop());
	}

	// 角色碰到ramp2 停止 
	if (CMovingBitmap::IsOverlap(character1_left, ramp.ramp2) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 8, character1[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character1_right, ramp.ramp2) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 8, character1[0].GetTop());
	}

	if (CMovingBitmap::IsOverlap(character2_left, ramp.ramp2) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 8, character2[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character2_right, ramp.ramp2) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 8, character2[0].GetTop());
	}



	// 角色碰到 white ramp 停住

	if (CMovingBitmap::IsOverlap(character1_left, ramp.white_ramp) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 8, character1[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character2_left, ramp.white_ramp) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 8, character2[0].GetTop());
	}

	if (CMovingBitmap::IsOverlap(character1_right, ramp.white_ramp) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 8, character1[0].GetTop());
	}

	if (CMovingBitmap::IsOverlap(character2_right, ramp.white_ramp) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 8, character2[0].GetTop());
	}




	/////////////////////////////////////////////////////////////////////////////
	////	 角色 1 移動
	/////////////////////////////////////////////////////////////////////////////

	if (GetAsyncKeyState(0x41) & 0x8000) {  // 當角色1按A向左
		character1[0].SetTopLeft(character1[0].GetLeft() - 8, character1[0].GetTop());
		character1[2].SetAnimation(100, false);
	}
	if (GetAsyncKeyState(0x44) & 0x8000) {  //當角色1按D向右
		character1[0].SetTopLeft(character1[0].GetLeft() + 8, character1[0].GetTop());
		character1[1].SetAnimation(100, false);
	}


	////	 角色 2 移動碰到牆壁停止
	if (keepLeft == true && wall_left2 == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 8, character2[0].GetTop());

	}
	if (keepRight == true && wall_right2 == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 8, character2[0].GetTop());
	}
}

void CGameStateRun::boxMove() {
	//人物一推箱子移動
	//向左推
	if (CMovingBitmap::IsOverlap(character1_left, box.box) == true) {
		if (GetAsyncKeyState(0x41) & 0x8000) {
			box.box.SetTopLeft(box.box.GetLeft() - 8, box.box.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(character1_right, box.box) == true) {
		if (GetAsyncKeyState(0x44) & 0x8000) {
			box.box.SetTopLeft(box.box.GetLeft() + 8, box.box.GetTop());
		}
	}

	//站在箱子上不會穿越箱子
	if (CMovingBitmap::IsOverlap(foot1, box.box) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}

	//人物二推箱子移動
	//向左推
	if (CMovingBitmap::IsOverlap(character2_left, box.box) == true) {
		if (keepLeft == true) {
			box.box.SetTopLeft(box.box.GetLeft() - 8, box.box.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(character2_right, box.box) == true) {
		if (keepRight == true) {
			box.box.SetTopLeft(box.box.GetLeft() + 8, box.box.GetTop());
		}
	}

	//站在箱子上不會穿越箱子
	if (CMovingBitmap::IsOverlap(foot2, box.box) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}
}

void CGameStateRun::ballMove() {
	//人物一推球移動
	//向左推
	for (int i = 0; i < 2; i++) {
		if (CMovingBitmap::IsOverlap(character1_left, ball.ball[i]) == true) {
			if (GetAsyncKeyState(0x41) & 0x8000) {
				ball.ball[i].SetTopLeft(ball.ball[i].GetLeft() - 8, ball.ball[i].GetTop());
			}
		}

		//向右推
		if (CMovingBitmap::IsOverlap(character1_right, ball.ball[i]) == true) {
			if (GetAsyncKeyState(0x44) & 0x8000) {
				ball.ball[i].SetTopLeft(ball.ball[i].GetLeft() + 8, ball.ball[i].GetTop());
			}
		}

		//站在箱子上不會穿越箱子
		if (CMovingBitmap::IsOverlap(foot1, ball.ball[i]) == true) {
			character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
		}

		//人物二推箱子移動
		//向左推
		if (CMovingBitmap::IsOverlap(character2_left, ball.ball[i]) == true) {
			if (keepLeft == true) {
				ball.ball[i].SetTopLeft(ball.ball[i].GetLeft() - 8, ball.ball[i].GetTop());
			}
		}

		//向右推
		if (CMovingBitmap::IsOverlap(character2_right, ball.ball[i]) == true) {
			if (keepRight == true) {
				ball.ball[i].SetTopLeft(ball.ball[i].GetLeft() + 8, ball.ball[i].GetTop());
			}
		}

		//站在箱子上不會穿越箱子
		if (CMovingBitmap::IsOverlap(foot2, ball.ball[i]) == true) {
			character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
		}
	}
}



void CGameStateRun::show_image_by_phase() {
	/////////////////////////////////////////////////////////////////////////////
	//////////// 物件在不同關卡的初始位置
	/////////////////////////////////////////////////////////////////////////////
	if (phase <= 6) {
		door.setObject(phase);
		button.setObject(phase);
		ramp.setObject(phase);
		box.setObject(phase);
		pond.setObject(phase);
		diamond.setObject(phase);
		joystick.setObject(phase);
		ball.setObject(phase);

		if (phase == 1 && sub_phase == 1) {
			// 角色與箱子
			character1[0].SetTopLeft(25, 640);
			character2[0].SetTopLeft(25, 760);

			for (int i = 0; i < 8; i++) {
				diamond.red_diamond[i].SetFrameIndexOfBitmap(0);
				diamond.blue_diamond[i].SetFrameIndexOfBitmap(0);
			}

			pause.SetTopLeft(1350,15);

			diamond_num = 0;
			isdead = false;
			ispause = false;

			door.door1.SetFrameIndexOfBitmap(0);
			door.door2.SetFrameIndexOfBitmap(0);
		}

		if (phase == 2 && sub_phase == 1) {
			character1[0].SetTopLeft(25, 640);
			character2[0].SetTopLeft(25, 760);

			for (int i = 0; i < 8; i++) {
				diamond.red_diamond[i].SetFrameIndexOfBitmap(0);
				diamond.blue_diamond[i].SetFrameIndexOfBitmap(0);
			}

			diamond_num = 0;
			isdead = false;
			ispause = false;
			
			door.door1.SetFrameIndexOfBitmap(0);
			door.door2.SetFrameIndexOfBitmap(0);
		}

		if (phase == 3 && sub_phase == 1) {
			character1[0].SetTopLeft(50, 50);
			character2[0].SetTopLeft(100, 50);

			for (int i = 0; i < 8; i++) {
				diamond.red_diamond[i].SetFrameIndexOfBitmap(0);
				diamond.blue_diamond[i].SetFrameIndexOfBitmap(0);
			}

			diamond_num = 0;
			isdead = false;
			ispause = false;

			door.door1.SetFrameIndexOfBitmap(0);
			door.door2.SetFrameIndexOfBitmap(0);



		}
		if (phase == 4 && sub_phase == 1) {

		}
		if (phase == 5 && sub_phase == 1) {

		}
		if (phase == 6 && sub_phase == 1) {

		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
}


//寶石記數
int CGameStateRun::diamondNum() {
	for (int i = 0; i < 8; i++) {
		if (CMovingBitmap::IsOverlap(character1[0], diamond.red_diamond[i]) == true) {
			diamond_num++;
		}

		if (CMovingBitmap::IsOverlap(character2[0], diamond.blue_diamond[i]) == true) {
			diamond_num++;
		}
	}
	
	return diamond_num;
}
