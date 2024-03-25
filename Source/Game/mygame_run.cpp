﻿#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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

	if (CMovingBitmap::IsOverlap(foot1, ramp) == true) {
		gravity_flag1 = true;
	}

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 38; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			else if (j == 2 && i > 26) {
				break;
			}
			if (CMovingBitmap::IsOverlap(foot1, cube[j][i]) == true) {
				gravity_flag1 = true;
				break;
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
	
	if (CMovingBitmap::IsOverlap(foot2, ramp) == true) {
		gravity_flag2 = true;
	}

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 38; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			else if (j == 2 && i > 26) {
				break;
			}
			if (CMovingBitmap::IsOverlap(foot2, cube[j][i]) == true) {
				character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
				gravity_flag2 = true;
				break;
			}
		}
	}

	if (gravity_flag2 == false) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() + 5);
	}

	/////////重力結束////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	////	 角色 碰到牆壁停止
	/////////////////////////////////////////////////////////////////////////////

	////	 角色 1 碰到牆壁停止
	if (CMovingBitmap::IsOverlap(character1_left, map_left) == false) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 5, character1[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character1_right, map_right) == false) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 5, character1[0].GetTop());
	}

	////	 角色 2 碰到牆壁停止
	if (keepLeft == true && CMovingBitmap::IsOverlap(character2_left, map_left) == false) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 5, character2[0].GetTop());
	}
	if (keepRight == true && CMovingBitmap::IsOverlap(character2_right, map_right) == false) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 5, character2[0].GetTop());
	}



	/////////////////////////////////////////////////////////////////////////////
	////	 角色 1 移動
	/////////////////////////////////////////////////////////////////////////////


	if (GetAsyncKeyState(0x41) & 0x8000) {  // 當角色1按A向左
		character1[0].SetTopLeft(character1[0].GetLeft() - 5, character1[0].GetTop());
		character1[2].SetAnimation(100, false);
	}
	if (GetAsyncKeyState(0x44) & 0x8000) {  //當角色1按D向右
		character1[0].SetTopLeft(character1[0].GetLeft() + 5, character1[0].GetTop());
		character1[1].SetAnimation(100, false);
	}

	/////////////////////////////////////////////////////////////////////////////
	////	 角色 跳躍
	/////////////////////////////////////////////////////////////////////////////

	////	 角色 1 跳躍
	if (GetAsyncKeyState(0x57) & 0x8000 && CMovingBitmap::IsOverlap(foot1, ramp) == true) {
		jump1 = true;
		jump1_time = clock();
	}

	if (jump1 == true && (clock() - jump1_time) < 500) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 12);
	}
	else if (jump1 == true && (clock() - jump1_time) < 560) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}
	else if (jump1 == true) {
		jump1 = false;
	}

	////	 角色 2 跳躍
	if (jump2 == true && (clock() - jump2_time) < 500) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 12);
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

	////	 角色 1 頂頭
	for (int j = 1; j < 3; j++) {
		for (int i = 0; i < 38; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			else if (j == 2 && i > 26) {
				break;
			}
			if (CMovingBitmap::IsOverlap(head1, cube[1][i]) == true) {
				jump1 = false;
			}
		}
	}

	////	 角色 2 頂頭
	for (int j = 1; j < 3; j++) {
		for (int i = 0; i < 30; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			else if (j == 2 && i > 26) {
				break;
			}
			if (CMovingBitmap::IsOverlap(head2, cube[1][i]) == true) {
				jump2 = false;
			}
		}
	}

	bool flag1 = false;

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 38; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			else if (j == 2 && i > 26) {
				break;
			}

			if (GetAsyncKeyState(0x57) & 0x8000 && CMovingBitmap::IsOverlap(foot1, cube[j][i]) == true) {
				character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop());
				flag1 = true;
				break;
			}
		}
	}

	if (flag1 == true) {
		jump1 = true;
		jump1_time = clock();
		flag1 = false;
	}

	/////////////////////////////////////////////////////////////////////////////
	////	 機關
	/////////////////////////////////////////////////////////////////////////////
	
	//機關
	//button1
	if (CMovingBitmap::IsOverlap(foot2, button1) == true || CMovingBitmap::IsOverlap(foot1, button1) == true || CMovingBitmap::IsOverlap(box, button1) == true) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop() + 1);
	}
	else if (button1.GetTop() > 705) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop() - 2);
	}
	else if (button1.GetTop() == 721) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop());
	}


	//button2
	
	if (CMovingBitmap::IsOverlap(foot2, button2) == true || CMovingBitmap::IsOverlap(foot1, button2) == true) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop() + 1);
	}
	else if (button2.GetTop() > 205) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop() - 2);
	}
	else if (button2.GetTop() == 221) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop());
	}

	// button1 && button2 操控 ramp
	if (button1.GetTop() > 705 || button2.GetTop() > 205) {
		ramp.SetTopLeft(ramp.GetLeft(), min(600, ramp.GetTop() + 5));
	}
	else {
		ramp.SetTopLeft(ramp.GetLeft(), max(300, ramp.GetTop() - 5));
	}
	

	//角色碰到機關停住
	if (CMovingBitmap::IsOverlap(foot1, ramp) == true && ramp.GetTop() > 300 && ramp.GetTop() != 600) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() -5);
	}

	if (CMovingBitmap::IsOverlap(foot2, ramp) == true && ramp.GetTop() > 300 && ramp.GetTop() != 600) {
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
			box.SetTopLeft(box.GetLeft() - 5, box.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(character1_right, box) == true) {
		if (GetAsyncKeyState(0x44) & 0x8000) {
			box.SetTopLeft(box.GetLeft() + 5, box.GetTop());
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
			box.SetTopLeft(box.GetLeft() - 5, box.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(character2_right, box) == true) {
		if (keepRight == true) {
			box.SetTopLeft(box.GetLeft() + 5, box.GetTop());
		}
	}

	//站在箱子上不會穿越箱子
	if (CMovingBitmap::IsOverlap(foot2, box) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}

	// 箱子碰到牆壁停止
	if (CMovingBitmap::IsOverlap(box, map_left) == true) {
		box.SetTopLeft(box.GetLeft() + 5, box.GetTop());

		//箱子碰到牆壁時人物不會穿越箱子
		if (CMovingBitmap::IsOverlap(character1_left, box) == true) {
			character1[0].SetTopLeft(character1[0].GetLeft() + 5, character1[0].GetTop());
		}
		
		if (CMovingBitmap::IsOverlap(character2_left, box) == true) {
			character2[0].SetTopLeft(character2[0].GetLeft() + 5, character2[0].GetTop());
		}
	}


}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//背景
	bg.LoadBitmapByString({ "Resources/bg.bmp" });
	bg.SetTopLeft(0, 0);

	//////////////////////////////地板///////////////////////////
	
	//第一層
	for (int i = 0; i < 38; i++) {
		cube[0][i].LoadBitmapByString({ "Resources/cube.bmp" });
	}
	cube[0][0].SetTopLeft(0, 841);

	//第二層
	for (int i = 0; i < 30; i++) {
		cube[1][i].LoadBitmapByString({ "Resources/cube.bmp" });
	}
	cube[1][0].SetTopLeft(0, 720);

	//第三層
	for (int i = 0; i < 27; i++) {
		cube[2][i].LoadBitmapByString({ "Resources/cube.bmp" });
	}
	cube[2][0].SetTopLeft(0, 220);



	
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////角色////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////角色 1 圖片讀取////////////////////////////////////////
	character1[0].LoadBitmapByString({ "Resources/fireboy.bmp", "Resources/character_ignore.bmp" }, RGB(255, 255, 255));
	character1[0].SetTopLeft(850, 750);

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

	//角色 1 碰撞感測器
	foot1.LoadEmptyBitmap(5, 21);
	head1.LoadEmptyBitmap(5, 21);
	character1_left.LoadEmptyBitmap(60, 11);
	character1_right.LoadEmptyBitmap(60, 11);

	/////////////////////////////////角色 2 圖片讀取////////////////////////////////////////

	character2[0].LoadBitmapByString({ "Resources/watergirl_sprite (0_0).bmp", "Resources/character_ignore.bmp" }, RGB(255, 255, 255));
	character2[0].SetTopLeft(850, 750);

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


	//角色2碰撞感測器

	foot2.LoadEmptyBitmap(5, 21);
	head2.LoadEmptyBitmap(5, 21);
	character2_left.LoadEmptyBitmap(60, 11);
	character2_right.LoadEmptyBitmap(60, 11);

	/////////////////////////////////////////////////////////////////////////////////////////////////


	//牆壁
	map_left.LoadBitmapByString({ "Resources/map_left.bmp" });
	map_left.SetTopLeft(0, 0);

	map_right.LoadBitmapByString({ "Resources/map_right.bmp" });
	map_right.SetTopLeft(1348, 0);

	map_top.LoadBitmapByString({ "Resources/map_top.bmp" });
	map_top.SetTopLeft(0, 0);

	//機關
	button1.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	button1.SetTopLeft(300, 710);

	button2.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	button2.SetTopLeft(600, 210);

	ramp.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
	ramp.SetTopLeft(1000, 300);

	//箱子
	box.LoadBitmapByString({ "Resources/box.bmp" }, RGB(255, 255, 255));
	box.SetTopLeft(200, 676);


	//門
	door1.LoadBitmapByString({ "Resources/door100.bmp",
							   "Resources/door101.bmp",
							   "Resources/door102.bmp",
							   "Resources/door103.bmp",
							   "Resources/door104.bmp",
							   "Resources/door105.bmp" });
	door1.SetTopLeft(200, 131);
	door1.SetAnimation(100, true);

	door2.LoadBitmapByString({ "Resources/door200.bmp",
							   "Resources/door201.bmp",
							   "Resources/door202.bmp",
							   "Resources/door203.bmp",
							   "Resources/door204.bmp",
							   "Resources/door205.bmp" });
	door2.SetTopLeft(100, 131);
	door2.SetAnimation(100, true);

	//水池
	pond.LoadBitmapByString({ "Resources/pond.bmp" }, RGB(255, 255, 255));
	pond.SetTopLeft(1200, 842);

}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////角色 2 按鈕 ////////////////////////////////
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
	if (nChar == VK_UP && CMovingBitmap::IsOverlap(foot2, ramp) == true) {
		jump2 = true;
		jump2_time = clock();
	}

	bool flag2 = false;

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 38; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			else if (j == 2 && i > 26) {
				break;
			}

			if (nChar == VK_UP && CMovingBitmap::IsOverlap(foot2, cube[j][i]) == true) {
				character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
				flag2 = true;
				break;
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

	////////角色2左右移動
	if (nChar == VK_LEFT) {
		keepLeft = false;
	}

	if (nChar == VK_RIGHT) {
		keepRight = false;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
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

	//門
	door1.ShowBitmap();
	door2.ShowBitmap();

	//機關與動畫
	button1.ShowBitmap();
	button2.ShowBitmap();
	ramp.ShowBitmap();
	
	//箱子
	box.ShowBitmap();
	

	///////////////////地板///////////////////////////////////////	
	for (int i = 0; i < 38; i++) {
		cube[0][i].SetTopLeft(cube[0][0].GetLeft() + (36 * i), cube[0][0].GetTop());
		cube[0][i].ShowBitmap();
	}

	for (int i = 0; i < 30; i++) {
		cube[1][i].SetTopLeft(cube[1][0].GetLeft() + (36 * i), cube[1][0].GetTop());
		cube[1][i].ShowBitmap();
	}

	for (int i = 0; i < 27; i++) {
		cube[2][i].SetTopLeft(cube[2][0].GetLeft() + (36 * i), cube[2][0].GetTop());
		cube[2][i].ShowBitmap();
	}

	///////////////////////人物與動畫//////////////////////////////////////
	// character1
	//角色碰撞感測器
	foot1.SetTopLeft(character1[0].GetLeft() + 25, character1[0].GetTop() + 85);
	foot1.ShowBitmap();

	head1.SetTopLeft(character1[0].GetLeft() + 25, character1[0].GetTop() + 4);
	head1.ShowBitmap();

	character1_left.SetTopLeft(character1[0].GetLeft() + 0, character1[0].GetTop() + 15);
	character1_left.ShowBitmap();
	character1_right.SetTopLeft(character1[0].GetLeft() + 55, character1[0].GetTop() + 15);
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
	else if (CMovingBitmap::IsOverlap(foot1, pond) == true) {  //死亡條件
		character1[0].SetFrameIndexOfBitmap(1);
		GotoGameState(GAME_STATE_OVER);
	}
	else {
		character1[0].ShowBitmap();
	}




	// character2
	//角色碰撞感測器
	foot2.SetTopLeft(character2[0].GetLeft() + 39, character2[0].GetTop() + 95);
	foot2.ShowBitmap();

	head2.SetTopLeft(character2[0].GetLeft() + 39, character2[0].GetTop() + 15);
	head2.ShowBitmap();

	character2_left.SetTopLeft(character2[0].GetLeft() + 22, character2[0].GetTop() + 25);
	character2_left.ShowBitmap();
	character2_right.SetTopLeft(character2[0].GetLeft() + 66, character2[0].GetTop() + 25);
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
	else if (CMovingBitmap::IsOverlap(character2[0], pond) == true) {  //死亡條件
		character2[0].SetFrameIndexOfBitmap(1);
		GotoGameState(GAME_STATE_OVER);
	}
	else {
		character2[0].ShowBitmap();

	}

	

	//牆壁
	map_left.ShowBitmap();
	map_right.ShowBitmap();
	map_top.ShowBitmap();

	//水池
	pond.ShowBitmap();

	//door 動畫
	if (CMovingBitmap::IsOverlap(character1[0], door1) == true && door1.GetFrameIndexOfBitmap() == 0) {
		door1.ToggleAnimation();
	}

	if (CMovingBitmap::IsOverlap(character2[0], door2) == true && door2.GetFrameIndexOfBitmap() == 0) {
		door2.ToggleAnimation();
	}

}



void CGameStateRun::show_image_by_phase() {
	if (phase <= 6) {

		if (phase == 1 && sub_phase == 1) {
			
			////地板
			cube[0][0].SetTopLeft(0, 841);	// 第一層
			cube[1][0].SetTopLeft(0, 720);	// 第二層
			cube[2][0].SetTopLeft(0, 220);	// 第三層

			//
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
		CTextDraw::Print(pDC, 237, 128, "修改你的主角！");
		CTextDraw::Print(pDC, 55, 163, "將灰色方格換成 resources 內的 giraffe.bmp 圖樣！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 2 && sub_phase == 1) {
		CTextDraw::Print(pDC, 26, 128, "下一個階段，讓長頸鹿能夠透過上下左右移動到這個位置！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 3 && sub_phase == 1) {
		CTextDraw::Print(pDC, 205, 128, "幫你準備了一個寶箱");
		CTextDraw::Print(pDC, 68, 162, "設計程式讓長頸鹿摸到寶箱後，將寶箱消失！");
		CTextDraw::Print(pDC, 68, 196, "記得寶箱要去背，使用 RGB(255, 255, 255)");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 4 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了一個蜜蜂好朋友");
		CTextDraw::Print(pDC, 89, 162, "已經幫它做了兩幀的動畫，讓它可以上下移動");
		CTextDraw::Print(pDC, 110, 196, "寫個程式來讓你的蜜蜂好朋友擁有動畫！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 5 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了三扇門");
		CTextDraw::Print(pDC, 89, 162, "設計程式讓長頸鹿摸到門之後，門會打開");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 6 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了一顆會倒數的球");
		CTextDraw::Print(pDC, 89, 162, "設計程式讓球倒數，然後顯示 OK 後停止動畫");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (sub_phase == 2) {
		CTextDraw::Print(pDC, 268, 128, "完成！");
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
