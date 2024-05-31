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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{ 

	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	Sleep(1000);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
	// ������GAME_STATE_RUN
}



void CGameStateInit::load_background() {

}




void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	button_play.ShowBitmap();

}

