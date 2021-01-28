#pragma once
#include "IO.h"
#include "Dxlib.h"
#include <vector>
#include <string>

class MusicSelect
{
private:
	int MusicNumber = 1;
	int LevelNumber = 0;
	//グラフィック
	int Back;
	int StarA;
	int StarB;
	//曲のグラフィック
	int Music;
	int Music1;

	bool Musicflag = false;
	bool Musicflag2 = false;
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

	Input *input;

	std::vector<std::string> MusicName;
	std::vector<std::string> Level;

public:
	//スクロール
	void Left();
	void Center();
	void Right();

	~MusicSelect();
	MusicSelect();

	void LoadSelect();
	void Select();
	void levelSelect();
	void SelectDraw();
	void leveldraw();
	void NameDraw();

	std::string getnum();
	std::string getlevel();

};

