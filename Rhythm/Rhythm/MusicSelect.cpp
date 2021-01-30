#include "MusicSelect.h"

//#define TEST


MusicSelect::MusicSelect()
{
	input = new Input;

	//�w�i&��Փx�p�O���t�B�b�N
	Back = LoadGraph("selectBack2.png");//�w�i
	StarA = LoadGraph("selectStarA.png");//��Փx(��)
	StarB = LoadGraph("selectStarB.png");//��Փx(��)
	//�Ȗ�-----
	MusicName.push_back("��1");
	MusicName.push_back("���{�����X");
	MusicName.push_back("��3");
	//��Փx-----
	Level.push_back("easy");
	Level.push_back("normal");
	Level.push_back("hard");
	//�Ȃ̃T���l�C��(���u��)
	Music = LoadGraph("Music.png");
	Music1 = LoadGraph("Music1.png");
}

MusicSelect::~MusicSelect()
{
	delete input;
}

void MusicSelect::SelectDraw()
{
	DrawGraph(0, 0, Back, TRUE);

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

	//�����̕`��
	NameDraw();

	//�X�N���[��----------
	Right();
	Center();
	Left();
	DrawExtendGraph(450 + ScrollX[1], 400 - ScrollY[1], 650 + (ScrollX[1] * 1.666667), 600, Music1, TRUE);
	DrawExtendGraph(750 + ScrollX[2], 200 - ScrollY[2], 1150 + ScrollX[3], 600, Music1, TRUE);
	DrawExtendGraph(1250 - ScrollX[0], 400 - ScrollY[0], 1450 - (ScrollX[0] * 0.6), 600, Music1, TRUE);
}

//��Փx���Ȗ��̕\��
void MusicSelect::NameDraw()
{
	DrawFormatString(750, 950, GetColor(255, 255, 255), "EASY", true);
	DrawFormatString(900, 950, GetColor(255, 255, 255), "NORMAL", true);
	DrawFormatString(1050, 950, GetColor(255, 255, 255), "HARD", true);

	if (!Musicflag && !Musicflag2)
		DrawString(800, 700, MusicName[MusicNumber].c_str(), GetColor(255, 255, 255), TRUE);

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

		if (!Musicflag2) {
			Musicflag = true;
		}
	}
	else if (input->GetKeyDown(KEY_INPUT_LEFT))
	{

		if (!Musicflag) {
			Musicflag2 = true;
		}
	}
	if (2 <= MusicNumber) MusicNumber = 2;
	if (0 >= MusicNumber) MusicNumber = 0;
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









