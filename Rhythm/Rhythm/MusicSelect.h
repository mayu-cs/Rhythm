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
	//�O���t�B�b�N
	int Back;
	int StarA;
	int StarB;
	//�Ȃ̃O���t�B�b�N
	int Music[3];

	//��Փx�O���t�B�b�N
	int LevelText;

	//�X�N���[��������ۂ̃t���O
	bool Musicflag;//�E
	bool Musicflag2;//��

	//�ȑI�𒆂����x���I�𒆂��̔���t���O
	bool determine;

	//��Փx�p�t���O
	int easyflag;
	int normalflag;
	int hardflag;
	//�X�N���[��
	int ScrollX[4];
	int ScrollY[3];
	int count[3];

	bool leftflag;
	bool rightflag;
	//�t�H���g
	int Font;

	//�T�E���h
	std::string Loadsound;
	int sound;

	Input *input;

	std::vector<std::string> MusicName;
	std::vector<std::string> MusicSound;
	std::vector<std::string> Level;

public:
	//�X�N���[��
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

	//�{����
	void LoadMusicSelect();

	std::string getnum();
	std::string getlevel();

};