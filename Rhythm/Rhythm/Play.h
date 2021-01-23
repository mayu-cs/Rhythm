#pragma once
#pragma once
#include "IO.h"
#include "TimeSync.h"
#include "Collision.h"

//extern const int WIN_WIDTH;
const int WIN_WIDTH = 810;
extern const int WIN_HEIGHT;

#define LANE_NUM 4 //ÉåÅ[ÉìÇÃêî
#define BAR_NUM 20 //(âÊñ Ç…)ìØéûÇ…ë∂ç›Ç≈Ç´ÇÈ1ÉåÅ[ÉìÇ†ÇΩÇËÇÃbarÇÃç≈ëÂêî

#define LANE1_POSITION_X 572 + (WIN_WIDTH / 4) / 2 - (105 / 2) - 20
#define LANE2_POSITION_X 572 + (WIN_WIDTH / 4 * 3) / 2 - (105 / 2) - 20
#define LANE3_POSITION_X 572 + WIN_WIDTH - ((WIN_WIDTH / 4) * 3) / 2 - (105 / 2) - 20
#define LANE4_POSITION_X 572 + WIN_WIDTH - (WIN_WIDTH / 4) / 2 - (105 / 2) - 20

#define DEBUG

class Scene
{
public:
	Scene(int NomalNoteGraphHandle, int CursorGraphHandle);
	~Scene();
	void GameStart();

private:
	Input *input;
	TimeSync time_sync;
	Collision collision;

	void MakeObject();
	void UpdateObject();
	void DrawObject();

private:
	//System
	int counter;
	int MouseX;
	int MouseY;
	int C_MouseX = 0;
	unsigned int count;
	bool ClickFlag = false;
	bool oldClick = false;
	bool Particle_Flag = false;

	//Sounds
	double BPM;
	double speed;
	bool SoundFlag;

	//images
	bool flag[200];
	double PosX[200];
	double PosY[200];
	double bar_PosY[BAR_NUM];

	int Cursor;
	int NomalNote;
	int Background;
	int MusicHandle;
	int particle_img;
};