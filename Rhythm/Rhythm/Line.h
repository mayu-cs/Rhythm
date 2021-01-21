#pragma once

extern const int WIN_HEIGHT;

class Line
{
private:
	int x;
	int height = 792;

public:
	Line(int x);
	void draw();
};



