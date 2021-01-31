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
	//背景&難易度用グラフィック
	Back = LoadGraph("Resources\\MusicSelect\\selectBack2.png");//背景
	StarA = LoadGraph("Resources\\MusicSelect\\selectStarA.png");//難易度(★)
	StarB = LoadGraph("Resources\\MusicSelect\\selectStarB.png");//難易度(☆)
	LevelText = LoadGraph("Resources\\MusicSelect\\selectLevelText.png");
	//曲名-----
	MusicName.push_back("君色ジャンプ");
	MusicName.push_back("Lyrith -迷宮リリス-");
	MusicName.push_back("Evanescent");
	//サウンド------
	MusicSound.push_back("Resources\\MusicScore\\Data\\君色ジャンプ.preload.mp3");
	MusicSound.push_back("Resources\\MusicScore\\Data\\Lyrith -迷宮リリス-.preload.mp3");
	MusicSound.push_back("Resources\\MusicScore\\Data\\Evanescent.preload.mp3");
	//難易度-----
	Level.push_back("easy");
	Level.push_back("normal");
	Level.push_back("hard");
	//曲のサムネイル(仮置き)

	Music[0] = LoadGraph("Resources\\MusicSelect\\");
	Music[1] = LoadGraph("Resources\\MusicSelect\\Lyrith -迷宮リリス-.png");
	Music[2] = LoadGraph("Resources\\MusicSelect\\Evanescent.jpg");

	//フォント
	Font = CreateFontToHandle("和田研細丸ゴシック2004絵文字P", 90, 8, DX_FONTTYPE_ANTIALIASING);
	
	//サウンド
	Loadsound = "Lyrith -迷宮リリス-.preload.mp3";
	sound = LoadSoundMem(Loadsound.c_str());
	//ChangeVolumeSoundMem(20,sound);
}

MusicSelect::~MusicSelect()
{
	delete input;
}

void MusicSelect::LoadMusicSelect()
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
			if (input->GetKeyDown(KEY_INPUT_BACK))
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
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	StopSoundMem(sound);
}

//曲の切り替え
void MusicSelect::LoadMusic()
{
	Loadsound = MusicSound[MusicNumber].c_str();
	sound = LoadSoundMem(Loadsound.c_str());
	ChangeVolumeSoundMem(100, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_LOOP);
}

//曲のサムネや難易度の画像表示
void MusicSelect::SelectDraw()
{
	DrawGraph(0, 0, Back, TRUE);
	//文字の描画
	NameDraw();

	//スクロール----------
	Right();
	Center();
	Left();
	DrawExtendGraph(450 + ScrollX[1], 400 - ScrollY[1], 650 + (ScrollX[1] * 1.666667), 600, Music[0], TRUE);
	DrawExtendGraph(750 + ScrollX[2], 200 - ScrollY[2], 1150 + ScrollX[3], 600, Music[1], TRUE);
	DrawExtendGraph(1250 - ScrollX[0], 400 - ScrollY[0], 1450 - (ScrollX[0] * 0.6), 600, Music[2], TRUE);

	//レベル選択時に表示
	if (determine == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
		DrawBox(0, 0, 1920, 1080, GetColor(40, 40, 40), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}

	//難易度表示--------
	DrawGraph(760, 950, LevelText, TRUE);
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

//難易度＆曲名の表示
void MusicSelect::NameDraw()
{

	if (!Musicflag && !Musicflag2)
		DrawStringToHandle(680, 660, MusicName[MusicNumber].c_str(), GetColor(255, 255, 255), Font);

	//左右どちらかが押されて曲が変わったら読み込み
	if (oldMusicNumber != MusicNumber)
	{
		StopSoundMem(sound);

		LoadMusic();
	}
	oldMusicNumber = MusicNumber;

#ifdef DEBUG
	//ただの確認用↓
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

//曲情報を返す
std::string MusicSelect::getnum()
{
	return MusicName[MusicNumber];
}
std::string MusicSelect::getlevel()
{
	return Level[LevelNumber];
}

//曲名とレベルの選択
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

//スクロールの動き
void MusicSelect::Left()//右から左へのスクロール0
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
	if (Musicflag)//右
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
void MusicSelect::Right()//左から右へのスクロール
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