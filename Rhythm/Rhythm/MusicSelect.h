#pragma once
#include "IO.h"
#include "Dxlib.h"
#include <vector>
#include <string>

class MusicSelect
{
private:
	int MusicNumber = 1;
	int oldMusicNumber = 0;
	int LevelNumber = 0;
	//グラフィック
	int Back;
	int StarA;
	int StarB;
	//曲のグラフィック
	int Music;
	int Music1;

	//スクロールさせる際のフラグ
	bool Musicflag = false;//右
	bool Musicflag2 = false;//左

	//曲選択中かレベル選択中かの判定フラグ
	bool determine = false;


	//難易度用フラグ
	int easyflag;
	int normalflag;
	int hardflag;
	//スクロール
	int ScrollX[4] = { 0 };
	int ScrollY[3] = { 0 };
	int count[3] = { 0 };

	bool leftflag = false;
	bool rightflag = false;
	//フォント
	int Font;
	int LevelFont;

	//サウンド
	std::string Loadsound;
	int sound;


	Input *input;

	std::vector<std::string> MusicName;
	std::vector<std::string> MusicSound;
	std::vector<std::string> Level;

public:
	//スクロール
	void Left();
	void Center();
	void Right();

	~MusicSelect();
	MusicSelect();

	void LoadMusic();
	void Select();
	void levelSelect();
	void SelectDraw();
	void leveldraw();
	void NameDraw();

	//本部分
	void LoadMusicSelect();

	std::string getnum();
	std::string getlevel();

};