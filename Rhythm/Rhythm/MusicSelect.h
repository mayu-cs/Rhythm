#pragma once
#include "IO.h"
#include "Dxlib.h"
#include <vector>
#include <string>

class MusicSelect
{
private:
	int MusicNumber = 0;
	int LevelNumber = 0;
	Input *input;
	std::vector<std::string> MusicName;
	std::vector<std::string> Level;

public:

	void Select();
	MusicSelect();
	void levelSelect();
	std::string getnum();
	std::string getlevel();

};

