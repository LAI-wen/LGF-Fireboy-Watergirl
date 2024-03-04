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
	if (CMovingBitmap::IsOverlap(character1, floor1) == false) {
		character1.SetTopLeft(character1.GetLeft(), character1.GetTop() + 2);
	}

	if (CMovingBitmap::IsOverlap(character2, floor1) == false) {
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() + 5);
	}

	if (keepLeft == true) {
		character2.SetTopLeft(character2.GetLeft() - 5 , character2.GetTop());
	}
	if (keepRight == true) {
		character2.SetTopLeft(character2.GetLeft() + 5, character2.GetTop());
	}

	if (jump == true && (clock() - jump_time) < 400) {
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() - 10);
	}
	else if (jump == true && (clock() - jump_time) < 450) {
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() - 5);
	}
	else if (jump == true && (clock() - jump_time) < 4000) {
		jump = false;

	}
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	floor1.LoadBitmapByString({ "Resources/floor1.bmp" });
	floor1.SetTopLeft(0, 850);

	character1.LoadBitmapByString({"Resources/fireboy.bmp"}, RGB(255, 255, 255));
	character1.SetTopLeft(850, 700);

	character2.LoadBitmapByString({"Resources/watergirl.bmp"}, RGB(255, 255, 255));
	character2.SetTopLeft(850, 700);


}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		keepLeft = true;
	}

	if (nChar == VK_RIGHT) {
		keepRight = true;
	}

	if (nChar == VK_UP && CMovingBitmap::IsOverlap(character2, floor1) == true) {
		jump = true;
		jump_time = clock();
		//character2.SetTopLeft(character2.GetLeft(), character2.GetTop() - 40);
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	floor1.ShowBitmap();
	character1.ShowBitmap();
	character2.ShowBitmap();

}
