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

	int cursorX = 640;//カーソル画像用の座標
	int cursorY = 625;

public:
	Title();
	int start();
};

