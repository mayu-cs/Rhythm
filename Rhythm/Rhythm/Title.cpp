#include "Title.h"
#include "DxLib.h"
#include"ParticleBox.h"
#include "IO.h"

Input *t_input;
Box box[100];
Title::Title()
{
	alpha				= 0;
	Vol					= 100;
	flag				= false;
	t_input				= new Input();
	t_input				->Initialize();
	titleGraph			= LoadGraph("Resources\\Background\\titleBack.png");
	titleCursorGraph	= LoadGraph("Resources\\Cursor\\titleCursor.png");
	TitleBGM			= LoadSoundMem("Resources\\GameSound\\TitleBGM.mp3");

	PlaySoundMem(TitleBGM, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(Vol, TitleBGM);
}

void Title::start()
{
    while (ScreenFlip() == false && ProcessMessage() == false && ClearDrawScreen() == false)
    {
		t_input->Update();
		if (flag == false && GetRand(5) == 0)//1/5の確率でパーティクルを生成する
		{
			for (int i = 0; i < 100; ++i)
			{
				if (box[i].Create()) { break; }
			}
		}

		for (int i = 0; i < 100; ++i)
		{
			box[i].Update();
		}


		//カーソル移動処理
		if (t_input->GetKeyDown(KEY_INPUT_UP))
		{
			if (cursorY == 780)//カーソルがstartの位置にあるとき
			{
				cursorY = 625;
			}
		}
		else if (t_input->GetKeyDown(KEY_INPUT_DOWN))
		{
			if (cursorY == 625)//カーソルがendの位置にあるとき
			{
				cursorY = 780;
			}
		}

		//シーン推移
		if (t_input->GetKeyDown(KEY_INPUT_SPACE))
		{
			if (cursorY == 625)//カーソルがstartの位置にあるとき
			{
				flag = true;
			}
			else//カーソルがendの位置にあるとき
			{
				DxLib_End();
			}
		}

		if (flag == true) {
			Vol -= 1;
			alpha -= 12;
			ChangeVolumeSoundMem(Vol, TitleBGM);

			if (Vol <= 0 || alpha <= 0) {
				break;
			}
		}
		else {
			if (alpha != 255) {
				alpha += 5;
			}
		}

		//描画処理
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, titleGraph, TRUE);
		DrawGraph(cursorX, cursorY, titleCursorGraph, TRUE);
		for (int i = 0; i < 100; ++i)
		{
			box[i].Draw();
		}
    }
	StopSoundMem(TitleBGM);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
