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
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g) : CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	/*
	if (clock() - button_retry_time == 21000) {
		button_retry.SetFrameIndexOfBitmap(0);
		button_play.ShowBitmap();
	}
	else if (clock() - button_retry_time <= 25500) {
		GotoGameState(GAME_STATE_RUN);
	}
	*/
	//GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	background.LoadBitmapByString({ "resources/game_over.bmp" }, RGB(255, 255, 255));
	background.SetTopLeft(170, 150);
	button_menu.LoadBitmapByString({ "resources/button_menu.bmp","resources/button_menu1.bmp" });
	button_retry.LoadBitmapByString({ "resources/button_retry.bmp","resources/button_retry1.bmp" });
	button_menu.SetTopLeft(405, 536);
	button_retry.SetTopLeft(722, 536);


}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66, "Initialize...");	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100, "OK!");

	Sleep(1000);


}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (WM_LBUTTONDOWN) {
		int idx1 = point.x;
		int idy1 = point.y;

		if (idx1 >= 722 && idy1 > 536 && idx1 <= 915 && idy1 <= 600) {
			button_retry.SetTopLeft(718, 530);
			button_retry.SetFrameIndexOfBitmap(1);
			button_retry.ShowBitmap();
			button_retry_time = clock();

		}
		else if(idx1 >= 405 && idy1 > 536 && idx1 <= 611 && idy1 <= 600){
			button_menu.SetTopLeft(400, 530);
			button_menu.SetFrameIndexOfBitmap(1);
			button_menu.ShowBitmap();
			button_menu_time = clock();
		}

	}


}

void CGameStateOver::OnShow()
{
	background.ShowBitmap();
	button_menu.ShowBitmap();
	button_retry.ShowBitmap();
}
