#pragma once

extern const int WIN_WIDTH; //ウィンドウ横幅
extern const int WIN_HEIGHT;//ウィンドウ縦幅
class Box
{
	int x;
	int y;
	int width;
	int height;
	int pal;//透明度
	int speed;
	int flag;//0の時描画されない

public:
	Box();
	bool Create();
	void Update();
	void Draw();
};

