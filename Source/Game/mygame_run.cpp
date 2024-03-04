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
	character1.SetTopLeft(character1.GetLeft(), character1.GetTop() + 10);
	character2.SetTopLeft(character2.GetLeft(), character2.GetTop() + 10);


	if (GetAsyncKeyState(0x41)) {  //A鍵向左
		character1.SetTopLeft(character1.GetLeft() - 10, character1.GetTop());
	}
	if (GetAsyncKeyState(0x44)) {  //D鍵向右
		character1.SetTopLeft(character1.GetLeft() + 10, character1.GetTop());
	}

	if (keepLeft == true) {
		character2.SetTopLeft(character2.GetLeft() - 10, character2.GetTop());
	}
	if (keepRight == true) {
		character2.SetTopLeft(character2.GetLeft() + 10, character2.GetTop());
	}
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{


	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		keepLeft = true;
	}

	if (nChar == VK_RIGHT) {
		keepRight = true;
	}

	if (nChar == VK_UP) {
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() - 10);
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
}
