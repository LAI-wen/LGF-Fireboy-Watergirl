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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{ 

	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
	background.LoadBitmapByString({ "resources/start.bmp" }, RGB(255, 255, 255));
	background.SetTopLeft(120, 150);
	button_play.LoadBitmapByString({ "resources/play1.bmp", "resources/play2.bmp" }, RGB(255, 255, 255));
	button_play.SetTopLeft(480, 500);

}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnMove() {

	if (clock() - button_play_time == 35000) {
		button_play.SetFrameIndexOfBitmap(0);
		button_play.ShowBitmap();
	}
	else if (clock() - button_play_time <= 55500) {
		GotoGameState(GAME_STATE_RUN);
	}

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{

	if (WM_LBUTTONDOWN) {
		int idx1 = point.x;
		int idy1 = point.y;

		if (idx1 >= 480 && idy1 > 500 && idx1 <= 863 && idy1 <= 618) {
			button_play.SetFrameIndexOfBitmap(1);
			button_play.ShowBitmap();
			button_play_time = clock();


		}

	}
	// 切換至GAME_STATE_RUN
}



void CGameStateInit::load_background() {

}




void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	button_play.ShowBitmap();

}

