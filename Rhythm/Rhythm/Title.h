#pragma once
class Title
{
private:
	unsigned int alpha;
	unsigned int Vol;
	bool flag;

	int titleGraph;
	int titleCursorGraph;
	int TitleBGM;

	int cursorX = 640;//�J�[�\���摜�p�̍��W
	int cursorY = 625;

public:
	Title();
	int start();
};

