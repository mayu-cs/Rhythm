#pragma once
#include "IO.h"
#include "Dxlib.h"
#include <vector>
#include <string>

class MusicSelect
{
private:
	unsigned int alpha;
	unsigned int Vol;
	bool flag;

	int MusicNumber;
	int oldMusicNumber;
	int LevelNumber;
	//グラフィック
	int Back;
	int StarA;
	int StarB;
	//曲のグラフィック
	int Music[3];

	//難易度グラフィック
	int LevelText;

	//スクロールさせる際のフラグ
	bool Musicflag;//右
	bool Musicflag2;//左

	//曲選択中かレベル選択中かの判定フラグ
	bool determine;

	//難易度用フラグ
	int easyflag;
	int normalflag;
	int hardflag;
	//スクロール
	int ScrollX[4];
	int ScrollY[3];
	int count[3];

	bool leftflag;
	bool rightflag;
	//フォント
	int Font;

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