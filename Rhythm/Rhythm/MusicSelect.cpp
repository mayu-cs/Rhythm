#include "MusicSelect.h"

//#define TEST

MusicSelect::MusicSelect()
{
	input = new Input;

	//�w�i&��Փx�p�O���t�B�b�N
	Back = LoadGraph("Resources\\MusicSelect\\selectBack2.png");//�w�i
	StarA = LoadGraph("Resources\\MusicSelect\\selectStarA.png");//��Փx(��)
	StarB = LoadGraph("Resources\\MusicSelect\\selectStarB.png");//��Փx(��)
	//�Ȗ�-----
	MusicName.push_back("��1");
	MusicName.push_back("Lyrith -���{�����X-");
	MusicName.push_back("��3");
	//�T�E���h------
	MusicSound.push_back("abc.mp3");
	MusicSound.push_back("Lyrith -���{�����X-.preload.mp3");
	MusicSound.push_back("��3");
	//��Փx-----
	Level.push_back("easy");
	Level.push_back("normal");
	Level.push_back("hard");
	//�Ȃ̃T���l�C��(���u��)
	
	Music1 = LoadGraph("Resources\\MusicSelect\\Music1.png");

	//�t�H���g
	Font = CreateFontToHandle("�a�c���׊ۃS�V�b�N2004�G����P", 90, 8, DX_FONTTYPE_ANTIALIASING_EDGE);
	LevelFont = CreateFontToHandle("�a�c���׊ۃS�V�b�N2004�G����P", 25, 8, DX_FONTTYPE_ANTIALIASING_EDGE);
	//�T�E���h
	Loadsound = "Lyrith -���{�����X-.preload.mp3";
	sound = LoadSoundMem(Loadsound.c_str());
	//ChangeVolumeSoundMem(20,sound);



}

MusicSelect::~MusicSelect()
{
	delete input;
	StopSoundMem(sound);
}

void MusicSelect::LoadMusicSelect()
{

	while (ScreenFlip() == false && ProcessMessage() == false && ClearDrawScreen() == false)
	{
		SelectDraw();

		if (determine == false)
		{
			Select();

			if (input->GetKeyDown(KEY_INPUT_SPACE))
			{
				determine = true;
			}
		}
		else if (determine == true)
		{
			levelSelect();

			if (input->GetKeyDown(KEY_INPUT_SPACE))
			{
				break;
			}
			if (input->GetKeyDown(KEY_INPUT_BACK))
			{
				determine = false;
			}
		}

	}

}

//�Ȃ̐؂�ւ�
void MusicSelect::LoadMusic()
{

	Loadsound = MusicSound[MusicNumber].c_str();
	sound = LoadSoundMem(Loadsound.c_str());
	ChangeVolumeSoundMem(20, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_LOOP);


}


//�Ȃ̃T���l���Փx�̉摜�\��
void MusicSelect::SelectDraw()
{
	DrawGraph(0, 0, Back, TRUE);
	//�����̕`��
	NameDraw();

	//�X�N���[��----------
	Right();
	Center();
	Left();
	DrawExtendGraph(450 + ScrollX[1], 400 - ScrollY[1], 650 + (ScrollX[1] * 1.666667), 600, Music1, TRUE);
	DrawExtendGraph(750 + ScrollX[2], 200 - ScrollY[2], 1150 + ScrollX[3], 600, Music1, TRUE);
	DrawExtendGraph(1250 - ScrollX[0], 400 - ScrollY[0], 1450 - (ScrollX[0] * 0.6), 600, Music1, TRUE);

	//���x���I�����ɕ\��
	if (determine == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
		DrawBox(0, 0, 1920, 1080, GetColor(40, 40, 40), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	//��Փx�\��--------
	DrawGraph(750, 850, easyflag, TRUE);
	DrawGraph(900, 850, normalflag, TRUE);
	DrawGraph(1050, 850, hardflag, TRUE);
	if (LevelNumber == 0)easyflag = StarA;
	else easyflag = StarB;
	if (LevelNumber == 1)normalflag = StarA;
	else normalflag = StarB;
	if (LevelNumber == 2)hardflag = StarA;
	else hardflag = StarB;


}

//��Փx���Ȗ��̕\��
void MusicSelect::NameDraw()
{
	DrawStringToHandle(750, 950, "EASY", GetColor(255, 255, 255), LevelFont);
	DrawStringToHandle(880, 950, "NORMAL", GetColor(255, 255, 255), LevelFont);
	DrawStringToHandle(1050, 950, "HARD", GetColor(255, 255, 255), LevelFont);
	//DrawFormatString(750, 950, GetColor(255, 255, 255), "EASY",true);
	//DrawFormatString(900, 950, GetColor(255, 255, 255), "NORMAL",true);
	//DrawFormatString(1050, 950, GetColor(255, 255, 255), "HARD",true);

	if (!Musicflag && !Musicflag2)
		DrawStringToHandle(680, 660, MusicName[MusicNumber].c_str(), GetColor(255, 255, 255), Font);

	//���E�ǂ��炩��������ċȂ��ς������ǂݍ���
	if (oldMusicNumber != MusicNumber)
	{
		StopSoundMem(sound);

		LoadMusic();
		aa = true;
	}
	oldMusicNumber = MusicNumber;

	//�����̊m�F�p��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%s", Loadsound.c_str());
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", MusicNumber);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "%d", oldMusicNumber);


}


#ifdef TEST

void MusicSelect::leveldraw()
{
	DrawExtendGraph(450, 350, 650, 550, easyflag, TRUE);
	DrawExtendGraph(850, 350, 1050, 550, normalflag, TRUE);
	DrawExtendGraph(1250, 350, 1450, 550, hardflag, TRUE);

	if (LevelNumber == 0)easyflag = StarA;
	else easyflag = StarB;

	if (LevelNumber == 1)normalflag = StarA;
	else normalflag = StarB;

	if (LevelNumber == 2)hardflag = StarA;
	else hardflag = StarB;
}

#endif

//�ȏ���Ԃ�
std::string MusicSelect::getnum()
{
	return MusicName[MusicNumber];
}
std::string MusicSelect::getlevel()
{
	return Level[LevelNumber];
}

//�Ȗ��ƃ��x���̑I��
void MusicSelect::levelSelect()
{
	input->Initialize();

	if (input->GetKeyDown(KEY_INPUT_RIGHT))
	{
		LevelNumber++;
	}
	else if (input->GetKeyDown(KEY_INPUT_LEFT))
	{
		LevelNumber--;
	}
	if (2 <= LevelNumber) LevelNumber = 2;
	if (0 >= LevelNumber) LevelNumber = 0;
}
void MusicSelect::Select()
{
	input->Initialize();

	if (input->GetKeyDown(KEY_INPUT_RIGHT))
	{
		if (2 > MusicNumber)
		{
			if (!Musicflag2) {
				Musicflag = true;
			}
		}
	}
	else if (input->GetKeyDown(KEY_INPUT_LEFT))
	{
		if (0 < MusicNumber)
		{
			if (!Musicflag) {
				Musicflag2 = true;
			}
		}
	}
	/*if (2 <= MusicNumber) MusicNumber = 2;
	if (0 >= MusicNumber) MusicNumber = 0;*/
}

//�X�N���[���̓���
void MusicSelect::Left()//�E���獶�ւ̃X�N���[��0
{
	if (Musicflag) {
		if (count[0] < 25)
		{
			if (ScrollX[0] < 500)
			{
				ScrollX[0] += 20;
				ScrollY[0] += 8;
			}
			count[0]++;
		}
		else
		{
			MusicNumber++;
			count[0] = 0;
			Musicflag = false;
		}
	}
	if (Musicflag2) {
		if (count[0] < 25)
		{
			if (ScrollX[0] > -500)
			{
				ScrollX[0] -= 20;
				ScrollY[0] -= 8;
			}
			count[0]++;
		}
		else
		{
			MusicNumber--;
			count[0] = 0;
			Musicflag2 = false;
		}
	}
}
void MusicSelect::Center()
{
	if (Musicflag)//�E
	{
		if (!leftflag)
		{
			if (count[2] < 25)
			{
				if (ScrollX[0] < 500)
				{
					ScrollX[2] -= 12;
					ScrollX[3] = ScrollX[2] * 1.6;
					ScrollY[2] -= 8;
				}
				count[2]++;
			}
			else
			{
				count[2] = 0;
				rightflag = true;
			}
		}
		if (leftflag)
		{
			if (count[2] < 25)
			{
				ScrollX[2] -= 20;
				ScrollX[3] = ScrollX[2] * 0.6;
				ScrollY[2] += 8;
				count[2]++;
			}
			else
			{
				count[2] = 0;
				leftflag = false;
			}
		}
	}
	if (Musicflag2)
	{
		if (!rightflag)
		{
			if (count[2] < 25)
			{
				if (ScrollX[2] < 500)
				{
					ScrollX[2] += 20;
					ScrollX[3] = ScrollX[2] * 0.6;
					ScrollY[2] -= 8;
				}
				count[2]++;
			}
			else
			{
				leftflag = true;
				count[2] = 0;
			}
		}
		if (rightflag)
		{
			if (count[2] < 25)
			{
				ScrollX[2] += 12;
				ScrollX[3] = ScrollX[2] * 1.6;
				ScrollY[2] += 8;
				count[2]++;
			}
			else
			{
				count[2] = 0;
				rightflag = false;
			}
		}
	}
}
void MusicSelect::Right()//������E�ւ̃X�N���[��
{
	if (Musicflag2) {
		if (count[1] < 25)
		{
			if (ScrollX[1] < 300)
			{
				ScrollX[1] += 12;
				ScrollY[1] += 8;
			}
			count[1]++;
		}
		else
		{
			count[1] = 0;
		}
	}
	if (Musicflag) {
		if (count[1] < 25)
		{
			if (ScrollX[1] > -300)
			{
				ScrollX[1] -= 12;
				ScrollY[1] -= 8;
			}
			count[1]++;
		}
		else
		{
			count[1] = 0;
		}
	}
}









