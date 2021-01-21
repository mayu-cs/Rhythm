#include "MusicSelect.h"




MusicSelect::MusicSelect()
{
	input = new Input;

	MusicName.push_back("‚¤‚ñ‚¿");
	MusicName.push_back("‚¤‚ñ‚¿2");
	MusicName.push_back("‚¤‚ñ‚¿3");

	Level.push_back("easy");
	Level.push_back("normal");
	Level.push_back("hard");
}

std::string MusicSelect::getnum()
{
	return MusicName[MusicNumber];
}

std::string MusicSelect::getlevel()
{
	return Level[LevelNumber];
}



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

	if (2 <= LevelNumber)
	{
		LevelNumber = 2;
	}
	if (0 >= LevelNumber)
	{
		LevelNumber = 0;
	}


	DrawFormatString(0, 40, GetColor(255, 255, 255), "%d", LevelNumber);
}

void MusicSelect::Select()
{

	input->Initialize();

	if (input->GetKeyDown(KEY_INPUT_RIGHT))
	{
		MusicNumber++;
	}
	else if (input->GetKeyDown(KEY_INPUT_LEFT))
	{
		MusicNumber--;
	}

	if (MusicName.size() <= MusicNumber)
	{
		MusicNumber = 0;
	}


	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", MusicNumber);
}







