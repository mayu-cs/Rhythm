#pragma once

extern const int WIN_HEIGHT;

class Line
{
private:
	int x;
	int height;
	int image;

public:
	Line(int x);
	void draw();
};



