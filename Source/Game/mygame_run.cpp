#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <fstream>

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

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	/////////////////////////////////////////////////////////////////////////////
	// 重力開始 
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// 當角色1	沒有碰到 地板 以及 移動板，會往下掉
	/////////////////////////////////////////////////////////////////////////////
	bool gravity_flag1 = false;

	if (CMovingBitmap::IsOverlap(foot1, ramp) == true || CMovingBitmap::IsOverlap(foot1, ramp2) == true) {
		gravity_flag1 = true;
	}

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					if (CMovingBitmap::IsOverlap(foot1, maps[j][i][n]) == true) {
						gravity_flag1 = true;
						break;
					}

				}

			}
		}
	}


	if (gravity_flag1 == false) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() + 5);
	}

	/////////////////////////////////////////////////////////////////////////////
	// 當角色2	沒有碰到 地板 以及 移動板，會往下掉
	/////////////////////////////////////////////////////////////////////////////
	bool gravity_flag2 = false;
	
	if (CMovingBitmap::IsOverlap(foot2, ramp) == true || CMovingBitmap::IsOverlap(foot2, ramp2) == true) {
		gravity_flag2 = true;
	}


	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					if (CMovingBitmap::IsOverlap(foot2, maps[j][i][n]) == true) {
						gravity_flag2 = true;
						break;
					}

				}

			}
		}
	}

	if (gravity_flag2 == false) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() + 5);
	}

	// 箱子重力
	bool gravity_flag_box = false;

	if (CMovingBitmap::IsOverlap(box, ramp) == true) {
		gravity_flag_box = true;
	}


	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					if (CMovingBitmap::IsOverlap(box, maps[j][i][n]) == true) {
						gravity_flag_box = true;
						break;
					}

				}

			}
		}
	}


	if (gravity_flag_box == false) {
		box.SetTopLeft(box.GetLeft(), box.GetTop() + 5);
	}

	/////////重力結束////////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////////////////
	////	 角色 跳躍
	/////////////////////////////////////////////////////////////////////////////

	////	 角色 1 跳躍
	if (GetAsyncKeyState(0x57) & 0x8000 && (CMovingBitmap::IsOverlap(foot1, ramp) == true || CMovingBitmap::IsOverlap(foot1, ramp2) == true || CMovingBitmap::IsOverlap(foot1, box) == true)) {
		jump1 = true;
		jump1_time = clock();
	}

	if (jump1 == true && (clock() - jump1_time) < 500) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 15);
	}
	else if (jump1 == true && (clock() - jump1_time) < 560) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}
	else if (jump1 == true) {
		jump1 = false;
	}

	bool flag1 = false;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					if (GetAsyncKeyState(0x57) & 0x8000 && CMovingBitmap::IsOverlap(foot1, maps[j][i][n]) == true) {
						flag1 = true;
						break;
					}

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
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 15);
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

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					if (CMovingBitmap::IsOverlap(head1, maps[j][i][n]) == true || CMovingBitmap::IsOverlap(head1, ramp) == true || CMovingBitmap::IsOverlap(ramp2, ramp) == true) {
						jump1 = false;
						break;
					}

					if (CMovingBitmap::IsOverlap(character1_left, maps[j][i][n]) == true) {
						wall_left1 = false;
						break;
					}
					if (CMovingBitmap::IsOverlap(character1_right, maps[j][i][n]) == true) {
						wall_right1 = false;
						break;
					}

					if (CMovingBitmap::IsOverlap(box_left, maps[j][i][n]) == true) {
						box_moveleft = false;
						break;
					}
					if (CMovingBitmap::IsOverlap(box_right, maps[j][i][n]) == true) {
						box_moveright = false;
						break;
					}

				}

			}
		}
	}

	if (wall_left1 == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 10, character1[0].GetTop());
	}
	if (wall_right1 == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 10, character1[0].GetTop());
	}


	if (box_moveleft == true ) {
		box.SetTopLeft(box.GetLeft() - 10, box.GetTop());
	}
	if (box_moveright == true ) {
		box.SetTopLeft(box.GetLeft() + 10, box.GetTop());
	}

	if (box_moveleft == true && CMovingBitmap::IsOverlap(box, character1[0]) == true ) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 10, character1[0].GetTop());
	}
	if (box_moveright == true && CMovingBitmap::IsOverlap(box, character1[0]) == true ) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 10, character1[0].GetTop());
	}

	if (box_moveleft == true && CMovingBitmap::IsOverlap(box, character2[0]) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 10, character2[0].GetTop());
	}
	if (box_moveright == true && CMovingBitmap::IsOverlap(box, character2[0]) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 10, character2[0].GetTop());
	}




	////	 角色 2 頂頭 // 碰到地板左右停止

	bool wall_left2 = true;
	bool wall_right2 = true;


	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					if (CMovingBitmap::IsOverlap(head2, maps[j][i][n]) == true || CMovingBitmap::IsOverlap(head2, ramp) == true || CMovingBitmap::IsOverlap(head2, ramp2) == true) {
						jump2 = false;
					}

					if (CMovingBitmap::IsOverlap(character2_left, maps[j][i][n]) == true ) {
						wall_left2 = false;
						break;
					}
					if (CMovingBitmap::IsOverlap(character2_right, maps[j][i][n]) == true ) {
						wall_right2 = false;
						break;
					}

				}

			}
		}
	}

	
	// 角色碰到ramp 停止 
	if (CMovingBitmap::IsOverlap(character1_left, ramp) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 10, character1[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character1_right, ramp) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 10, character1[0].GetTop());
	}

	if (CMovingBitmap::IsOverlap(character2_left, ramp) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 10, character2[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character2_right, ramp) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 10, character2[0].GetTop());
	}

	// 角色碰到ramp2 停止 
	if (CMovingBitmap::IsOverlap(character1_left, ramp2) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 10, character1[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character1_right, ramp2) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 10, character1[0].GetTop());
	}

	if (CMovingBitmap::IsOverlap(character2_left, ramp2) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 10, character2[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character2_right, ramp2) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 10, character2[0].GetTop());
	}



	/////////////////////////////////////////////////////////////////////////////
	////	 角色 1 移動
	/////////////////////////////////////////////////////////////////////////////


	if (GetAsyncKeyState(0x41) & 0x8000) {  // 當角色1按A向左
		character1[0].SetTopLeft(character1[0].GetLeft() - 10, character1[0].GetTop());
		character1[2].SetAnimation(100, false);
	}
	if (GetAsyncKeyState(0x44) & 0x8000) {  //當角色1按D向右
		character1[0].SetTopLeft(character1[0].GetLeft() + 10, character1[0].GetTop());
		character1[1].SetAnimation(100, false);
	}


	////	 角色 2 移動碰到牆壁停止
	if (keepLeft == true && wall_left2 == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 10, character2[0].GetTop());

	}
	if (keepRight == true && wall_right2 == true) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 10, character2[0].GetTop());
	}

	

	/////////////////////////////////////////////////////////////////////////////
	////	 機關
	/////////////////////////////////////////////////////////////////////////////
	
	//機關
	
	//button1
	if (CMovingBitmap::IsOverlap(foot2, button1) == true || CMovingBitmap::IsOverlap(foot1, button1) == true || CMovingBitmap::IsOverlap(box, button1) == true) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop() + 1);
	}
	else if (button1.GetTop() > button1_y) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop() - 2);
	}
	else if (button1.GetTop() == button1_y + 15) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop());
	}


	//button2
	
	if (CMovingBitmap::IsOverlap(foot2, button2) == true || CMovingBitmap::IsOverlap(foot1, button2) == true) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop() + 1);
	}
	else if (button2.GetTop() > button2_y) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop() - 2);
	}
	else if (button2.GetTop() == button2_y + 15) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop());
	}

	// button1 && button2 操控 ramp2
	if (button1.GetTop() > button1_y || button2.GetTop() > button2_y) {
		ramp2.SetTopLeft(ramp2.GetLeft(), min(ramp2_y2, ramp2.GetTop() + 5));
	}
	else {
		ramp2.SetTopLeft(ramp2.GetLeft(), max(ramp2_y1, ramp2.GetTop() - 5));
	}
	


	// joystick 控制 ramp1
	if (joystick.GetFrameIndexOfBitmap() == 2) {
		ramp.SetTopLeft(ramp.GetLeft(), min(ramp_y2, ramp.GetTop() + 5));
	}
	else {
		ramp.SetTopLeft(ramp.GetLeft(), max(ramp_y1, ramp.GetTop() - 5));
	}

	//角色碰到機關停住
	// ramp1
	if (CMovingBitmap::IsOverlap(foot1, ramp) == true && ramp.GetTop() > ramp_y1 && ramp.GetTop() != ramp_y2) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() -5);
	}

	if (CMovingBitmap::IsOverlap(foot2, ramp) == true && ramp.GetTop() > ramp_y1 && ramp.GetTop() != ramp_y2) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}

	// ramp2
	if (CMovingBitmap::IsOverlap(foot1, ramp2) == true && ramp2.GetTop() > ramp2_y1 && ramp2.GetTop() != ramp2_y2) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}

	if (CMovingBitmap::IsOverlap(foot2, ramp2) == true && ramp2.GetTop() > ramp2_y1 && ramp2.GetTop() != ramp2_y2) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}


	/////////////////////////////////////////////////////////////////////////////
	////	 門
	/////////////////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////////////////
	////	 箱子
	/////////////////////////////////////////////////////////////////////////////

	//人物一推箱子移動
	//向左推
	if (CMovingBitmap::IsOverlap(character1_left, box) == true) {
		if (GetAsyncKeyState(0x41) & 0x8000) {
			box.SetTopLeft(box.GetLeft() - 10, box.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(character1_right, box) == true) {
		if (GetAsyncKeyState(0x44) & 0x8000) {
			box.SetTopLeft(box.GetLeft() + 10, box.GetTop());
		}
	}

	//站在箱子上不會穿越箱子
	if (CMovingBitmap::IsOverlap(foot1, box) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}

	//人物二推箱子移動
	//向左推
	if (CMovingBitmap::IsOverlap(character2_left, box) == true) {
		if (keepLeft == true) {
			box.SetTopLeft(box.GetLeft() - 10, box.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(character2_right, box) == true) {
		if (keepRight == true) {
			box.SetTopLeft(box.GetLeft() + 10, box.GetTop());
		}
	}

	//站在箱子上不會穿越箱子
	if (CMovingBitmap::IsOverlap(foot2, box) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}

	//碰到水池死亡
	//角色一
	if (CMovingBitmap::IsOverlap(foot1, pond) == true) {
		isdead = true;
	}
	else if (CMovingBitmap::IsOverlap(foot1, blue_pond) == true) {
		isdead = true;

	}

	//角色二
	if (CMovingBitmap::IsOverlap(foot2, pond) == true) {
		isdead = true;
	}
	else if (CMovingBitmap::IsOverlap(foot2, red_pond) == true) {
		isdead = true;
	}


	///死亡介面按鈕
	if (clock() - button_retry_time == 21000) {
		button_retry.SetFrameIndexOfBitmap(0);
		button_retry.ShowBitmap();
	}
	else if (clock() - button_retry_time <= 25500) {
		isdead = 0;
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
	

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (map_test[j][i] == 1) {
				maps_test[j][i].LoadEmptyBitmap(30, 30);
			}
		}
	}

	maps_test[0][0].SetTopLeft(300, 300);
	maps_test[1][0].SetTopLeft(300, 330);
	maps_test[2][0].SetTopLeft(300, 360);
	maps_test[3][0].SetTopLeft(300, 390);
	maps_test[4][0].SetTopLeft(300, 410);





	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					maps[j][i][n].LoadBitmapByString({ "Resources/cube.bmp" });
				}

			}

		}
	}


	
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////角色////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////角色 1 圖片讀取////////////////////////////////////////
	//角色 1 碰撞感測器 圖片讀取
	foot1.LoadEmptyBitmap(5, 21);
	head1.LoadEmptyBitmap(5, 30);
	character1_left.LoadEmptyBitmap(50, 11);
	character1_right.LoadEmptyBitmap(50, 11);

	
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


	//牆壁
	map_left.LoadBitmapByString({ "Resources/map_left.bmp" });
	map_right.LoadBitmapByString({ "Resources/map_right.bmp" });
	map_top.LoadBitmapByString({ "Resources/map_top.bmp" });


	//機關
	button1.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	button2.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	ramp.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
	ramp2.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });

	//箱子
	box_left.LoadEmptyBitmap(40, 5);
	box_right.LoadEmptyBitmap(40, 5);
	box.LoadBitmapByString({ "Resources/box.bmp" }, RGB(255, 255, 255));
	


	//門
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


	//水池
	pond.LoadBitmapByString({ "Resources/pond.bmp" }, RGB(255, 255, 255));
	red_pond.LoadBitmapByString({ "Resources/red_pond.bmp" }, RGB(255, 255, 255));
	blue_pond.LoadBitmapByString({ "Resources/blue_pond.bmp" }, RGB(255, 255, 255));

	//寶石
	for (int i = 0; i < 4; i++) {
		blue_diamond[i].LoadBitmapByString({ "Resources/blue_diamond.bmp", "Resources/diamond_ignore.bmp" }, RGB(255, 255, 255));
		red_diamond[i].LoadBitmapByString({ "Resources/red_diamond.bmp", "Resources/diamond_ignore.bmp" }, RGB(255, 255, 255));
	}

	
	//搖桿
	joystick.LoadBitmapByString({ "Resources/joystick_1.bmp", "Resources/joystick_2.bmp" , "Resources/joystick_3.bmp" }, RGB(255, 255, 255));
	joystick.SetTopLeft(500, 655);
	joystick.SetAnimation(100, true);

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
	button_continue.SetTopLeft(186, 536);


	/////////////////////////////////////////////////////////////////////////////
	//////////// 物件在不同關卡的初始位置
	/////////////////////////////////////////////////////////////////////////////
	if (phase <= 6) {

////////////////////////// 第一關////////////////////////////////////////////
		if (phase == 1 && sub_phase == 1) {


			

			// 角色與箱子
			character1[0].SetTopLeft(25, 630);
			character2[0].SetTopLeft(25, 750);
			box.SetTopLeft(700, 250);

			////地板
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 10; i++) {

					maps[j][i][0].SetTopLeft(0, j*300+(30 * i));	// 第一層

				}
			}


			////機關-buttom

			button1_y = 435;
			button2_y = 317;

			button1.SetTopLeft(400, button1_y);
			button2.SetTopLeft(1000, button2_y);


			////機關-ramp
			// ramp1
			ramp_y1 = 450;
			ramp_y2 = 550;
			ramp.SetTopLeft(50, ramp_y1);
			
			// ramp2
			ramp2_y1 = 330;
			ramp2_y2 = 440;
			ramp2.SetTopLeft(1245, ramp2_y1);

			////門
			door1.SetTopLeft(1200, 95);
			door1.SetAnimation(100, true);
			door2.SetTopLeft(1100, 95);
			door2.SetAnimation(100, true);

			////機關-joystick
			joystick.SetTopLeft(300, 535);

			////死亡水池
			pond.SetTopLeft(840, 660);
			red_pond.SetTopLeft(630, 840);
			blue_pond.SetTopLeft(872, 840);

			////寶石
			red_diamond[0].SetTopLeft(700, 780);
			red_diamond[1].SetTopLeft(300, 400);
			red_diamond[2].SetTopLeft(400, 100);

			blue_diamond[0].SetTopLeft(935, 780);
			blue_diamond[1].SetTopLeft(850, 420);
			blue_diamond[2].SetTopLeft(80, 150);
			blue_diamond[3].SetTopLeft(750, 130);

			for (int i = 0; i < 4; i++) {
				red_diamond[i].SetFrameIndexOfBitmap(0);
				blue_diamond[i].SetFrameIndexOfBitmap(0);
			}
			

			diamond_num = 0;


			map_left.SetTopLeft(0, 0);
			map_right.SetTopLeft(1348, 0);
			map_top.SetTopLeft(0, 0);
		}
////////////////////////// 第二關////////////////////////////////////////////
		if (phase == 2 && sub_phase == 1) {
			// 角色與箱子
			character1[0].SetTopLeft(100, 730);
			character2[0].SetTopLeft(25, 730);
			box.SetTopLeft(1500, 250);

			////地板
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 10; i++) {

					maps[j][i][0].SetTopLeft(0, j * 300 + (30 * i));    // 第一層

				}
			}


			////機關-buttom

			button1_y = 550;
			button2_y = 130;
			//button3_y = 575;
			//button4_y = 130;

			button1.SetTopLeft(300, button1_y);
			button2.SetTopLeft(800, button2_y);


			////機關-ramp
			// ramp1
			ramp_y1 = 500;
			ramp_y2 = 650;
			ramp.SetTopLeft(700, ramp_y1);

			// ramp2
			ramp2_y1 = 330;
			ramp2_y2 = 430;
			ramp2.SetTopLeft(1245, ramp2_y1);

			////門
			door1.SetTopLeft(50, 70);
			door1.SetAnimation(100, true);
			door2.SetTopLeft(150, 70);
			door2.SetAnimation(100, true);

			////機關-joystick
			joystick.SetTopLeft(300, 535);

			////死亡水池
			pond.SetTopLeft(900, 842);

			////寶石
			//red_diamond.SetTopLeft(700, 780);
			//blue_diamond.SetTopLeft(800, 780);

			map_left.SetTopLeft(0, 0);
			map_right.SetTopLeft(1348, 0);
			map_top.SetTopLeft(0, 0);

		}
		if (phase == 3 && sub_phase == 1) {

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
	if (nChar == VK_UP && (CMovingBitmap::IsOverlap(foot2, ramp) == true || CMovingBitmap::IsOverlap(foot2, ramp2) == true || CMovingBitmap::IsOverlap(foot2, box) == true)) {
		jump2 = true;
		jump2_time = clock();
	}

	bool flag2 = false;


	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					if (nChar == VK_UP && CMovingBitmap::IsOverlap(foot2, maps[j][i][n]) == true) {
						flag2 = true;
						break;
					}

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

		}
		else if (idx1 >= 455 && idy1 > 536 && idx1 <= 661 && idy1 <= 600) {
			button_menu.SetTopLeft(450, 530);
			button_menu.SetFrameIndexOfBitmap(1);
			button_menu.ShowBitmap();
			button_menu_time = clock();
		}
	
	}
	//continue
	if ((continue_what == 1 || continue_what == 2) && (WM_LBUTTONDOWN)) {
		int idx1 = point.x;
		int idy1 = point.y;

		if (idx1 >= 752 && idy1 > 536 && idx1 <= 955 && idy1 <= 600) {
			button_continue.SetFrameIndexOfBitmap(1);
			button_continue.ShowBitmap();
			button_continue_time = clock();

		}
		else if (idx1 >= 455 && idy1 > 536 && idx1 <= 661 && idy1 <= 600) {
			button_continue.SetFrameIndexOfBitmap(1);
			button_continue.ShowBitmap();
			button_continue_time = clock();
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

	//牆壁
	bg.ShowBitmap();

	

	//牆壁

	//門
	door1.ShowBitmap();
	door2.ShowBitmap();

	//機關與動畫
	button1.ShowBitmap();
	button2.ShowBitmap();
	ramp.ShowBitmap();
	ramp2.ShowBitmap();
	
	//箱子
	box.ShowBitmap();
	box_left.SetTopLeft(box.GetLeft() - 5, box.GetTop());
	box_left.ShowBitmap();
	box_right.SetTopLeft(box.GetLeft() + 43, box.GetTop());
	box_right.ShowBitmap();


	//寶石
	for (int i = 0; i < 4; i++) {
		red_diamond[i].ShowBitmap();
		if (CMovingBitmap::IsOverlap(character1[0], red_diamond[i]) == true) {
			red_diamond[i].SetFrameIndexOfBitmap(1);
			diamond_num++;
		}

		blue_diamond[i].ShowBitmap();
		if (CMovingBitmap::IsOverlap(character2[0], blue_diamond[i]) == true) {
			blue_diamond[i].SetFrameIndexOfBitmap(1);
			diamond_num++;
		}
	}

	

	

	///////////////////地板///////////////////////////////////////	



	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 10; i++) {
			for (int n = 0; n < 40; n++) {
				if (map[j][i][n] == 1) {
					maps[j][i][n].SetTopLeft((35 * n), maps[j][i][0].GetTop());
					maps[j][i][n].ShowBitmap();
				}

			}
		}
	}

	/*
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (map_test[j][i] == 1) {
				maps_test[j][i].SetTopLeft((30* i), maps_test[j][0].GetTop());
				maps_test[j][i].ShowBitmap();
			}
		}
	}
	
	*/

	

	///////////////////////人物與動畫//////////////////////////////////////
	// character1
	//角色碰撞感測器
	foot1.SetTopLeft(character1[0].GetLeft() + 25, character1[0].GetTop() + 85);
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



	//水池
	pond.ShowBitmap();
	red_pond.ShowBitmap();
	blue_pond.ShowBitmap();

	//門動畫
	if (CMovingBitmap::IsOverlap(character1_right, door1) == true && door1.GetFrameIndexOfBitmap() == 0) {
		door1.ToggleAnimation();
	}

	if (CMovingBitmap::IsOverlap(character2_right, door2) == true && door2.GetFrameIndexOfBitmap() == 0) {
		door2.ToggleAnimation();
	}

	// 判斷通關條件
	if ((door1.GetFrameIndexOfBitmap() == 5 && door2.GetFrameIndexOfBitmap() == 5) || GetAsyncKeyState(0x32) & 0x8000) {

		if (phase == 1) {
			
			if (diamond_num == 7) {
				continue_what = 1;
			}
			else {
				button_continue.ShowBitmap();
				continue_what = 2;
			}

			
			
			ifstream ifs("map/map.map");
			///
			for (int n = 0; n < 3; n++) {
				for (int k = 0; k < 10; k++) {
					for (int i = 0; i < 40; i++) {
						ifs >> map[n][k][i];

					}
				}
			}
			ifs.close();
			OnInit();



		}


		phase += 1;
		OnInit();
	}


	

	


	//搖桿
	joystick.ShowBitmap();
	if (CMovingBitmap::IsOverlap(character1_left, joystick) == true && joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.ToggleAnimation();
	}

	if (CMovingBitmap::IsOverlap(character1_right, joystick) == true && joystick.GetFrameIndexOfBitmap() == 2) {
		joystick.SetFrameIndexOfBitmap(0);
	}

	if (CMovingBitmap::IsOverlap(character2_left, joystick) == true && joystick.GetFrameIndexOfBitmap() == 0) {
		joystick.ToggleAnimation();
	}

	if (CMovingBitmap::IsOverlap(character2_right, joystick) == true && joystick.GetFrameIndexOfBitmap() == 2) {
		joystick.SetFrameIndexOfBitmap(0);
	}


	show_image_by_phase();


	//continue 畫面
	if (continue_what == 1) {
		continueUI.SetFrameIndexOfBitmap(0);
		continueUI.ShowBitmap();
		button_continue.ShowBitmap();
	}
	else if (continue_what == 2) {
		continueUI.SetFrameIndexOfBitmap(1);
		continueUI.ShowBitmap();
		button_continue.ShowBitmap();
	}

	//死亡畫面
	if (isdead == true) {
		gameover.ShowBitmap();
		button_menu.ShowBitmap();
		button_retry.ShowBitmap();
		OnInit();
	}





	
}



void CGameStateRun::show_image_by_phase() {
	if (phase <= 6) {

		if (phase == 1 && sub_phase == 1) {

		}
		if (phase == 2 && sub_phase == 1) {

		}
		if (phase == 3 && sub_phase == 1) {

		}
		if (phase == 4 && sub_phase == 1) {
	
		}
		if (phase == 5 && sub_phase == 1) {

		}
		if (phase == 6 && sub_phase == 1) {

		}
	}
}

void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(0, 0, 0), 800);

	if (phase == 1 && sub_phase == 1) {

	}
	else if (phase == 2 && sub_phase == 1) {

	}
	else if (phase == 3 && sub_phase == 1) {

	}
	else if (phase == 4 && sub_phase == 1) {

	}
	else if (phase == 5 && sub_phase == 1) {

	}
	else if (phase == 6 && sub_phase == 1) {

	}
	else if (sub_phase == 2) {

	}

	CDDraw::ReleaseBackCDC();
}

bool CGameStateRun::validate_phase_1() {

	return 0;
}

bool CGameStateRun::validate_phase_2() {
	return 0;
}

bool CGameStateRun::validate_phase_3() {
	return 0;
}

bool CGameStateRun::validate_phase_4() {
	return 0;
}

bool CGameStateRun::validate_phase_5() {
	return 0;
}

bool CGameStateRun::validate_phase_6() {
	return 0;
}
