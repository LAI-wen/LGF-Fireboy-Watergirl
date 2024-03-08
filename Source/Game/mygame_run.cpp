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
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

void CGameStateRun::OnMove()							// ���ʹC������
{
	if (CMovingBitmap::IsOverlap(character1, floor1) == false) {
		character1.SetTopLeft(character1.GetLeft(), character1.GetTop() + 2);
	}


	if (CMovingBitmap::IsOverlap(character2, floor1) == false && CMovingBitmap::IsOverlap(character2, floor2) == false) {
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() + 5);
	}

	if (keepLeft == true) {
		character2.SetTopLeft(character2.GetLeft() - 5, character2.GetTop());
	}
	if (keepRight == true) {
		character2.SetAnimation(100, false);
		character2.SetTopLeft(character2.GetLeft() + 5, character2.GetTop());

	}

	if (jump == true && (clock() - jump_time) < 450) {
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() - 12);
	}
	else if (jump == true && (clock() - jump_time) < 500) {
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() - 5);
	}
	else if (jump == true) {
		jump = false;
	}

	if (CMovingBitmap::IsOverlap(character2, floor2) == true) {
		jump = false;
	}






}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	bg.LoadBitmapByString({ "Resources/bg.bmp" });
	bg.SetTopLeft(0, 0);

	floor1.LoadBitmapByString({ "Resources/floor1.bmp" });
	floor1.SetTopLeft(0, 842);

	floor2.LoadBitmapByString({ "Resources/floor2.bmp" });
	floor2.SetTopLeft(0, 720);

	character1.LoadBitmapByString({ "Resources/fireboy.bmp" }, RGB(255, 255, 255));
	character1.SetTopLeft(850, 700);

	character2.LoadBitmapByString({ "Resources/watergirl_sprite (0_0).bmp", 
									"Resources/watergirl_sprite (1_0).bmp",
									"Resources/watergirl_sprite (1_1).bmp",
									"Resources/watergirl_sprite (1_2).bmp",
									"Resources/watergirl_sprite (1_3).bmp",
									"Resources/watergirl_sprite (1_4).bmp",
									"Resources/watergirl_sprite (1_5).bmp",
									"Resources/watergirl_sprite (1_6).bmp",
									"Resources/watergirl_sprite (1_7).bmp",
										}, RGB(255, 255, 255));
	character2.SetTopLeft(850, 700);

	map_left.LoadBitmapByString({ "Resources/map_left.bmp" });
	map_left.SetTopLeft(0, 0);

	map_right.LoadBitmapByString({ "Resources/map_right.bmp" });
	map_right.SetTopLeft(1348, 0);

	map_top.LoadBitmapByString({ "Resources/map_top.bmp" });
	map_top.SetTopLeft(0, 0);
	


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
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		keepLeft = false;
	}

	if (nChar == VK_RIGHT) {
		keepRight = false;
		character2.SetAnimation(100, true);
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
	bg.ShowBitmap();
	floor1.ShowBitmap();
	floor2.ShowBitmap();
	character1.ShowBitmap();
	character2.ShowBitmap();
	map_left.ShowBitmap();
	map_right.ShowBitmap();
	map_top.ShowBitmap();

}
