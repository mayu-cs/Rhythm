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
	//�O���t�B�b�N
	int Back;
	int StarA;
	int StarB;
	//�Ȃ̃O���t�B�b�N
	int Music;
	int Music1;

	bool Musicflag = false;
	bool Musicflag2 = false;
	//��Փx�p�t���O
	int easyflag;
	int normalflag;
	int hardflag;
	//�X�N���[��
	int ScrollX[4] = { 0 };
	int ScrollY[3] = { 0 };
	int count[3] = { 0 };

	bool leftflag = false;
	bool rightflag = false;

	Input *input;

	std::vector<std::string> MusicName;
	std::vector<std::string> Level;

public:
	//�X�N���[��
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

