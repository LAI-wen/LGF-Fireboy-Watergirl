/*
 * mygame.h: ���ɮ��x�C��������class��interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/


#include "myMap.h"
#include "myObject.h"
#include "myScene.h"
#include "Character.h"

#define VK_W 0x57
#define VK_A 0x41
#define VK_D 0x44
#define CHARACTER_WATERGIRL "watergirl"
#define CHARACTER_FIREBOY   "fireboy"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnMove();
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo
	private:
		void load_background();
		void draw_text();
		CMovingBitmap background;
		CMovingBitmap button_play;
		int button_play_time;
	};
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int phase = 1;									//���d
		int sub_phase = 1;								
		Character fireBoy = Character(CHARACTER_FIREBOY);
		Character waterGirl = Character(CHARACTER_WATERGIRL);
		CMovingBitmap background;						//�I��
		CMovingBitmap bg;					
		
		CMovingBitmap continueUI;
		CMovingBitmap gameover;

		CMovingBitmap pause;

		void gravety();
		void characterMove();
		void BallMove(CMovingBitmap &ball, Character &character); // New version 
		void CheckDeadOnPool(Character &character);
		void show_text_by_phase();

		int diamondNum();
		int eat_diamond;

		void show_image_by_phase();
		bool isdead = false;
		bool ispause = false;
		bool ismenu = false;
		bool test_no_dead = false;

		int pass_phase = 0;

		int continue_what;
		int diamond_num = 0;
	

		CMovingBitmap maps[29][40];

		int button_continue_time;


		bool keepLeft = false;
		bool keepRight = false;
		bool jump1 = false;
		int jump1_time = 0;
		bool jump2 = false;
		int jump2_time = 0;


		CMovingBitmap button_continue;
		CMovingBitmap button_retry;
		CMovingBitmap button_menu;
		
		Scene scene;

		Map map;
		Object::Door door;
		Object::Button button;
		Object::Ramp ramp;
		Object::Box box;
		Object::Pond pond;
		Object::Diamond diamond;
		Object::Joystick joystick;
		Object::Ball ball;
		Object::Fan fan;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////


	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		int button_retry_time;
		int button_menu_time;
		CMovingBitmap background;
		CMovingBitmap button_retry;
		CMovingBitmap button_menu;
	};

}
