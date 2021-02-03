#include "MusicSelect.h"

MusicSelect::MusicSelect()
{
	input = new Input;

	alpha = 0;
	Vol = 100;
	flag = false;

	MusicNumber = 1;
	oldMusicNumber = 0;
	LevelNumber = 0;
	for (int i = 0; i < 4; i++)
	{
		ScrollX[i] = { 0 };
	}
	for (int i = 0; i < 3; i++)
	{
		ScrollY[i] = { 0 };
		count[i] = { 0 };
	}
	Musicflag = false;
	Musicflag2 = false;
	
	determine = false;

	leftflag = false;
	rightflag = false;
	//�w�i&��Փx�p�O���t�B�b�N
	Back = LoadGraph("Resources\\Background\\selectBack.png");//�w�i
	StarA = LoadGraph("Resources\\Background\\selectStarA.png");//��Փx(��)
	StarB = LoadGraph("Resources\\Background\\selectStarB.png");//��Փx(��)
	LevelText = LoadGraph("Resources\\Background\\selectLevelText.png");
	//�Ȗ�-----
	MusicName.push_back("�N�F�W�����v");
	MusicName.push_back("Lyrith -���{�����X-");
	MusicName.push_back("Doppelganger");
	LoadDivGraph("Resources\\Background\\songTitle.png", 3, 1, 3, 800, 130, MusicTitle);
	//�T�E���h------
	MusicSound.push_back("Resources\\MusicScore\\Data\\�N�F�W�����v.preload.mp3");
	MusicSound.push_back("Resources\\MusicScore\\Data\\Lyrith -���{�����X-.preload.mp3");
	MusicSound.push_back("Resources\\MusicScore\\Data\\Doppelganger.preload.mp3");
	//��Փx-----
	Level.push_back("easy");
	Level.push_back("normal");
	Level.push_back("hard");
	//�Ȃ̃T���l�C��(���u��)
	Music[0] = LoadGraph("Resources\\MusicScore\\Data\\�N�F�W�����v.png");
	Music[1] = LoadGraph("Resources\\MusicScore\\Data\\Lyrith -���{�����X-.png");
	Music[2] = LoadGraph("Resources\\MusicScore\\Data\\Doppelganger.png");
	//�T�E���h
	Loadsound = "Lyrith -���{�����X-.preload.mp3";
	sound = LoadSoundMem(Loadsound.c_str());
}

MusicSelect::~MusicSelect()
{
	delete input;
}

int MusicSelect::LoadMusicSelect()
{
	while (ScreenFlip() == false && ProcessMessage() == false && ClearDrawScreen() == false)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
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
				flag = true;
			}
			if (input->GetKeyDown(KEY_INPUT_Z))
			{
				determine = false;
			}
		}

		if (flag == true)
		{
			Vol -= 1;
			alpha -= 12;
			ChangeVolumeSoundMem(Vol, sound);

			if (Vol <= 0 || alpha <= 0) {
				break;
			}
		}
		else 
		{
			if (alpha != 255)
			{
				alpha += 5;
			}
		}
		if (input->GetKey(KEY_INPUT_ESCAPE))
		{
			return -1;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	StopSoundMem(sound);
	return 0;
}

//�Ȃ̐؂�ւ�
void MusicSelect::LoadMusic()
{
	Loadsound = MusicSound[MusicNumber].c_str();
	sound = LoadSoundMem(Loadsound.c_str());
	ChangeVolumeSoundMem(100, sound);
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
	DrawExtendGraph(450 + ScrollX[1], 400 - ScrollY[1], 650 + (ScrollX[1] * 1.666667), 600, Music[0], TRUE);
	DrawExtendGraph(750 + ScrollX[2], 200 - ScrollY[2], 1150 + ScrollX[3], 600, Music[1], TRUE);
	DrawExtendGraph(1250 - ScrollX[0], 400 - ScrollY[0], 1450 - (ScrollX[0] * 0.6), 600, Music[2], TRUE);

	//���x���I�����ɕ\��
	if (determine == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
		DrawBox(0, 0, 1920, 1080, GetColor(40, 40, 40), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}

	//��Փx�\��--------
	DrawGraph(760, 950, LevelText, TRUE);
	DrawGraph(750, 850, easyflag, TRUE);
	DrawGraph(900, 850, normalflag, TRUE);
	DrawGraph(1050, 850, hardflag, TRUE);
	if (LevelNumber == 0)easyflag = StarA ;
	else easyflag = StarB;
	if (LevelNumber == 1)normalflag = StarA;
	else normalflag = StarB;
	if (LevelNumber == 2)hardflag = StarA;
	else hardflag = StarB;


}

//��Փx���Ȗ��̕\��
void MusicSelect::NameDraw()
{

	if (!Musicflag && !Musicflag2)
	{
		if (MusicNumber == 0)DrawGraph(530, 640, MusicTitle[0], TRUE);
		if (MusicNumber == 1)DrawGraph(530, 640, MusicTitle[1], TRUE);
		if (MusicNumber == 2)DrawGraph(530, 640, MusicTitle[2], TRUE);
	}
	//���E�ǂ��炩��������ċȂ��ς������ǂݍ���
	if (oldMusicNumber != MusicNumber)
	{
		StopSoundMem(sound);

		LoadMusic();
	}
	oldMusicNumber = MusicNumber;

#ifdef DEBUG
	//�����̊m�F�p��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%s", Loadsound.c_str());
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", MusicNumber);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "%d", oldMusicNumber);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", aa);
#endif // DEBUG
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