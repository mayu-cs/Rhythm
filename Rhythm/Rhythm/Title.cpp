#include "Title.h"
#include "DxLib.h"
#include"ParticleBox.h"
#include "IO.h"

Input *t_input;
Box box[100];
Title::Title()
{
	t_input = new Input();
	t_input->Initialize();
	titleGraph = LoadGraph("Resources\\Background\\titleBack.png");
	titleCursorGraph = LoadGraph("Resources\\Cursor\\titleCursor.png");
}

void Title::start()
{
    while (ScreenFlip() == false && ProcessMessage() == false && ClearDrawScreen() == false)
    {
		t_input->Update();
		if (GetRand(5) == 0)//1/5の確率でパーティクルを生成する
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
		if (t_input->GetKeyDown(KEY_INPUT_Z))
		{
			if (cursorY == 625)//カーソルがstartの位置にあるとき
			{
				break;
			}
			else//カーソルがendの位置にあるとき
			{
				DxLib_End();
			}
		}

		//描画処理
		DrawGraph(0, 0, titleGraph, TRUE);
		DrawGraph(cursorX, cursorY, titleCursorGraph, TRUE);
		for (int i = 0; i < 100; ++i)
		{
			box[i].Draw();
		}
    }
}
