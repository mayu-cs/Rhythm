#pragma once
#pragma once
#include "IO.h"
#include "TimeSync.h"
#include "Collision.h"

//extern const int WIN_WIDTH;
const int WIN_WIDTH = 810;
extern const int WIN_HEIGHT;

#define LANE_NUM 4 //ƒŒ[ƒ“‚Ì”
#define BAR_NUM 20 //(‰æ–Ê‚É)“¯‚É‘¶İ‚Å‚«‚é1ƒŒ[ƒ“‚ ‚½‚è‚Ìbar‚ÌÅ‘å”

class Scene
{
public:
	Scene(int NomalNoteGraphHandle, int CursorGraphHandle);
	void GameStart();

private:
	Input input;
	TimeSync time_sync;
	Collision collision;

	void MakeObject();
	void UpdateObject();
	void DrawObject();
	void Clump_Point();

private:
	//System
	int counter;
	int MouseX;
	int C_MouseX = 0;

	//Sounds
	double BPM;
	double speed;

	//images
	bool bar_flag[LANE_NUM][BAR_NUM];
	double bar_PosY[BAR_NUM];

	int Cursor;
	int NomalNote;
	int Background;
};