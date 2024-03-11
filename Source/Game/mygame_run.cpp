#include "stdafx.h"
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
	//重力
	//當角色1沒有碰到最下層跟第二層地板，會往下掉
	if (CMovingBitmap::IsOverlap(character1, floor1) == false && CMovingBitmap::IsOverlap(character1, floor2_up) == false ) {
		character1.SetTopLeft(character1.GetLeft(), character1.GetTop() + 5);
	}

	//當角色2沒有碰到最下層跟第二層地板，會往下掉
	if (CMovingBitmap::IsOverlap(character2[0], floor1) == false && CMovingBitmap::IsOverlap(character2[0], floor2_up) == false) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() + 5);
	}

	// character1 move
	// 碰到牆壁停止

	if (CMovingBitmap::IsOverlap(character1, map_left) == false) {
		character1.SetTopLeft(character1.GetLeft() - 5, character1.GetTop());
	}
	if (CMovingBitmap::IsOverlap(character1, map_right) == false) {
		character1.SetTopLeft(character1.GetLeft() + 5, character1.GetTop());
	}


	if (GetAsyncKeyState(0x41) & 0x8000) {  //按A向左
		character1.SetTopLeft(character1.GetLeft() - 5, character1.GetTop());
	}
	if (GetAsyncKeyState(0x44) & 0x8000) {  //按D向右
		character1.SetTopLeft(character1.GetLeft() + 5, character1.GetTop());
	}
	if (GetAsyncKeyState(0x57) & 0x8000 && (CMovingBitmap::IsOverlap(character1, floor1) == true || CMovingBitmap::IsOverlap(character1, floor2_up) == true)) {
		jump1 = true;
		jump1_time = clock();
	}

	if (jump1 == true && (clock() - jump1_time) < 450) {
		character1.SetTopLeft(character1.GetLeft(), character1.GetTop() - 12);
	}
	else if (jump1 == true && (clock() - jump1_time) < 500) {
		character1.SetTopLeft(character1.GetLeft(), character1.GetTop() - 5);
	}
	else if (jump1 == true) {
		jump1 = false;
	}

	if (CMovingBitmap::IsOverlap(character1, floor2_down) == true) {
		jump1 = false;
	}

	//character2 move
	//如果碰到牆壁就停止

	if (keepLeft == true && CMovingBitmap::IsOverlap(character2[0], map_left) == false) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 5, character2[0].GetTop());
	}
	if (keepRight == true && CMovingBitmap::IsOverlap(character2[0], map_right) == false) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 5, character2[0].GetTop());
	}

	//跳躍
	if (jump2 == true && (clock() - jump2_time) < 450) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 12);
	}
	else if (jump2 == true && (clock() - jump2_time) < 500) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}
	else if (jump2 == true) {
		jump2 = false;
	}

	if (CMovingBitmap::IsOverlap(character2[0], floor2_down) == true) {
		jump2 = false;
	}

	//機關

	if (CMovingBitmap::IsOverlap(character2[0], button) == true && button.GetTop()) {
		button.SetTopLeft(button.GetLeft(), button.GetTop() + 1);
	}
	else if (button.GetTop() > 700)
	{
		button.SetTopLeft(button.GetLeft(), button.GetTop() - 2);
	}
	else if (button.GetTop() == 721) {
		button.SetTopLeft(button.GetLeft(), button.GetTop());
	}

	if (button.GetTop() > 720 && ramp.GetTop() < 560) {
		ramp.SetTopLeft(ramp.GetLeft(), ramp.GetTop() + 5);
	}

	else if (ramp.GetTop() > 300) {
		ramp.SetTopLeft(ramp.GetLeft(), ramp.GetTop() - 5);
	}

	//角色碰到機關停住
	if (CMovingBitmap::IsOverlap(character1, ramp) == true) {
		character1.SetTopLeft(character1.GetLeft(), character1.GetTop() -10);
	}

	//door 動畫
	if (CMovingBitmap::IsOverlap(character2[0], door2) == true && door2.GetFrameIndexOfBitmap() == 0) {
		door2.ToggleAnimation();
	}




}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

	//背景
	bg.LoadBitmapByString({ "Resources/bg.bmp" });
	bg.SetTopLeft(0, 0);

	//地板
	floor1.LoadBitmapByString({ "Resources/floor1.bmp" });
	floor1.SetTopLeft(0, 842);

	floor2_up.LoadBitmapByString({ "Resources/floor2_up.bmp" });
	floor2_up.SetTopLeft(0, 720);

	floor2_down.LoadBitmapByString({ "Resources/floor2_down.bmp" });
	floor2_down.SetTopLeft(0, 721);

	floor2_right.LoadBitmapByString({ "Resources/floor2_right.bmp" });
	floor2_right.SetTopLeft(980, 721);

	//角色
	character1.LoadBitmapByString({ "Resources/fireboy.bmp" }, RGB(255, 255, 255));
	character1.SetTopLeft(850, 700);

	character2[0].LoadBitmapByString({ "Resources/watergirl_sprite (0_0).bmp" }, RGB(255, 255, 255));
	character2[0].SetTopLeft(850, 700);

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


	//牆壁
	map_left.LoadBitmapByString({ "Resources/map_left.bmp" });
	map_left.SetTopLeft(0, 0);

	map_right.LoadBitmapByString({ "Resources/map_right.bmp" });
	map_right.SetTopLeft(1348, 0);

	map_top.LoadBitmapByString({ "Resources/map_top.bmp" });
	map_top.SetTopLeft(0, 0);

	//機關

	button.LoadBitmapByString({ "Resources/button(1).bmp" }, RGB(255, 255, 255));
	button.SetTopLeft(300, 700);

	ramp.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
	ramp.SetTopLeft(1000, 300);

	//門
	door2.LoadBitmapByString({ "Resources/door200.bmp",
							   "Resources/door201.bmp",
							   "Resources/door202.bmp",
							   "Resources/door203.bmp",
							   "Resources/door204.bmp",
							   "Resources/door205.bmp" });
	door2.SetTopLeft(100, 631);
	door2.SetAnimation(100, true);



}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		keepLeft = true;
		character2[2].SetAnimation(100, false);
	}

	if (nChar == VK_RIGHT) {
		keepRight = true;
		character2[1].SetAnimation(100, false);
	}

	if (nChar == VK_UP && (CMovingBitmap::IsOverlap(character2[0], floor1) == true || CMovingBitmap::IsOverlap(character2[0], floor2_up) == true)) {
		jump2 = true;
		jump2_time = clock();
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
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

void CGameStateRun::OnShow()
{
	//牆壁
	bg.ShowBitmap();
	//門
	door2.ShowBitmap();

	//機關與動畫
	button.ShowBitmap();

	ramp.ShowBitmap();

	//地板
	floor1.ShowBitmap();
	floor2_up.ShowBitmap();
	floor2_down.ShowBitmap();
	floor2_right.ShowBitmap();
	character1.ShowBitmap();

	//人物與動畫
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

	//牆壁
	map_left.ShowBitmap();
	map_right.ShowBitmap();
	map_top.ShowBitmap();


}
