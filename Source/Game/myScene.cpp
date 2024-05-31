#include "stdafx.h"
#include "myScene.h"



void Scene::loadScene() {

	//�������� 0
	//�~��_ALL�_�ۤ��� 1
	//�~��_NOT ALL�_�ۤ��� 2
	// ��l��椶�� 3

	//window(setting paused die pass)
	window[0].LoadBitmapByString({ "Resources/w_game_over.bmp" });				//��������
	window[1].LoadBitmapByString({ "Resources/w_continue_all.bmp" });			//�~��_ALL�_�ۤ���
	window[2].LoadBitmapByString({ "Resources/w_continue.bmp" });				//�~��_NOT ALL�_�ۤ���
	window[3].LoadBitmapByString({ "Resources/w_choose0.bmp" });				// ��l��椶��

	window[4].LoadBitmapByString({ "Resources/w_choose1.bmp" });				// �q�L�Ĥ@��
	window[5].LoadBitmapByString({ "Resources/w_choose2.bmp" });				// �q�L�ĤG��
	window[6].LoadBitmapByString({ "Resources/w_choose3.bmp" });				// �q�L�ĤT��
	window[7].LoadBitmapByString({ "Resources/w_choose4.bmp" });				// �q�L�ĥ|��
	window[8].LoadBitmapByString({ "Resources/w_choose5.bmp" });				// �q�L�Ĥ���
	window[9].LoadBitmapByString({ "Resources/w_pause.bmp" });				// pause
	window[10].LoadBitmapByString({ "Resources/w_END.bmp" });				// END


	for (int i = 0; i < 11; i++) {
		window[i].SetTopLeft(0, 0);
	}

}

void Scene::showScene(int page_phase) {

	window[page_phase].ShowBitmap();		//window




}