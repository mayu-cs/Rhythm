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
		if (GetRand(5) == 0)//1/5�̊m���Ńp�[�e�B�N���𐶐�����
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


		//�J�[�\���ړ�����
		if (t_input->GetKeyDown(KEY_INPUT_UP))
		{
			if (cursorY == 780)//�J�[�\����start�̈ʒu�ɂ���Ƃ�
			{
				cursorY = 625;
			}
		}
		else if (t_input->GetKeyDown(KEY_INPUT_DOWN))
		{
			if (cursorY == 625)//�J�[�\����end�̈ʒu�ɂ���Ƃ�
			{
				cursorY = 780;
			}
		}

		//�V�[������
		if (t_input->GetKeyDown(KEY_INPUT_Z))
		{
			if (cursorY == 625)//�J�[�\����start�̈ʒu�ɂ���Ƃ�
			{
				break;
			}
			else//�J�[�\����end�̈ʒu�ɂ���Ƃ�
			{
				DxLib_End();
			}
		}

		//�`�揈��
		DrawGraph(0, 0, titleGraph, TRUE);
		DrawGraph(cursorX, cursorY, titleCursorGraph, TRUE);
		for (int i = 0; i < 100; ++i)
		{
			box[i].Draw();
		}
    }
}
