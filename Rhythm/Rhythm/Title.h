#pragma once
class Title
{
private:

	int titleGraph;
	int titleCursorGraph;

	int cursorX = 640;//カーソル画像用の座標
	int cursorY = 625;

public:
	Title();
	void start();
};

