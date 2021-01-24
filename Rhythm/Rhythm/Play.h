#pragma once
#include "IO.h"
#include "TimeSync.h"
#include "Collision.h"

//extern const int WIN_WIDTH;
const int WIN_WIDTH = 810;
extern const int WIN_HEIGHT;

#define PARTICLE_QUANTITY 32
#define LANE_NUM 4 //���[���̐�
#define BAR_NUM 20 //(��ʂ�)�����ɑ��݂ł���1���[���������bar�̍ő吔

/// <summary>
/// LANE(n)_POSITION_X = n���[���̃X�N���[���`����Ws
/// </summary>
constexpr double LANE1_POSITION_X = 572.0 + (WIN_WIDTH / 4.0) / 2.0 - (105.0 / 2.0) - 20.0;
constexpr double LANE2_POSITION_X = 572.0 + (WIN_WIDTH / 4.0 * 3.0) / 2.0 - (105.0 / 2.0) - 20.0;
constexpr double LANE3_POSITION_X = 572.0 + WIN_WIDTH - ((WIN_WIDTH / 4.0) * 3.0) / 2.0 - (105.0 / 2.0) - 20.0;
constexpr double LANE4_POSITION_X = 572.0 + WIN_WIDTH - (WIN_WIDTH / 4.0) / 2.0 - (105.0 / 2.0) - 20.0;

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

	void Update();
	void Pause();
	void Draw();
	void ClumpCursor();
	void Timing_Judge(const unsigned int lane, const double Distance);

private:
	//Position
	int counter;
	int MouseX;
	int MouseY;
	int CursorPosX;
	double Distance;
	double JudgePosX[4];
	double JudgePosY[4];
	const int CursorPosY = 790;

	//Counter
	unsigned int count;
	unsigned int Trans[4];

	//Flag
	bool ClickFlag = false;
	bool oldClick = false;
	bool Particle_Flag = false;
	bool PauseFlag = false;

	//Sounds
	double BPM;
	double speed;
	bool SoundFlag;

	//images
	double *PosX;
	double *PosY;
	bool *flag;

	int Cursor;
	int NomalNote;
	int Background;
	int MusicHandle;
	int particle_img;
	int PauseBack;
	int Font;
};