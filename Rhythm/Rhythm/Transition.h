#pragma once

const int __WIN_WIDTH = 1920; //ウィンドウ横幅
const int __WIN_HEIGHT = 1080;//ウィンドウ縦幅

class BoxTransitionHeight
{
private:
	int font;
	int fontSpace;//文字間
	int adjustTextPosX;//文字ずらす
	float boxHeight;//四角形の高さの1/2
	float flame;
	float maxFlame;
	float speedX;//イージングの一般式
	int pal;
public:
	BoxTransitionHeight();
	void Update();
	void Draw();
private:
	void Initial();
};