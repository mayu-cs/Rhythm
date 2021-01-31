#pragma once
#include "IO.h"
#include "TimeSync.h"
#include "Collision.h"
#include "Particle.h"
#include <nlohmann/json.hpp>
#include <iostream>

//extern const int WIN_WIDTH;
const int WIN_WIDTH = 810;
extern const int WIN_HEIGHT;

#define PERFECT				0
#define EXCELLENT			1
#define GOOD				2
#define BAD					3

#define END_FLAG			11	//譜面終了フラグ
#define PARTICLE_QUANTITY	32	//パーティクル数
#define LANE_NUM			4	//レーンの数
#define BAR_NUM				20	//(画面に)同時に存在できる1レーンあたりのbarの最大数

//LANE(n)_POSITION_X = nレーンのスクリーン描画座標s
constexpr double LANE1_POSITION_X = 572.0 + (WIN_WIDTH / 4.0) / 2.0 - (105.0 / 2.0) - 20.0;
constexpr double LANE2_POSITION_X = 572.0 + (WIN_WIDTH / 4.0 * 3.0) / 2.0 - (105.0 / 2.0) - 20.0;
constexpr double LANE3_POSITION_X = 572.0 + WIN_WIDTH - ((WIN_WIDTH / 4.0) * 3.0) / 2.0 - (105.0 / 2.0) - 20.0;
constexpr double LANE4_POSITION_X = 572.0 + WIN_WIDTH - (WIN_WIDTH / 4.0) / 2.0 - (105.0 / 2.0) - 20.0;

class Scene
{
public:
	Scene(const char *MusicFile);
	~Scene();
	void GameStart();

private:
	std::vector<int>	MusicScore;
	std::string			Judge[4];
	std::string			SongName;
	nlohmann::json		ScoreData;

	Particle			**particle;
	Input				*input;
	TimeSync			time_sync;
	Collision			collision;

	void loadJson(const char *ScoreFlie);
	void Update();
	void Pause();
	void Draw();
	void ClumpCursor();
	void Timing_Judge(const unsigned int lane, const double Distance);

private:
	//system
	unsigned int alpha;

	//Position
	int			MouseX;
	int			MouseY;
	int			CursorPosX;
	double		Distance;
	double		JudgePosX[4];
	double		JudgePosY[4];
	const int	CursorPosY = 790;

	//Counter
	unsigned int ActiveNotes_Counter;
	unsigned int counter;
	unsigned int EndCounter;
	unsigned int count;
	unsigned int Trans[4];

	//Flag
	bool ClickFlag = false;
	bool oldClick = false;
	bool Particle_Flag = false;
	bool PauseFlag = false;
	bool EndFlag;

	//Sounds
	double	BPM;
	double	speed;
	bool	SoundFlag;

	//images
	double	*PosX;
	double	*PosY;
	bool	*flag;

	int Cursor;
	int NomalNote;
	int Background;
	int MusicHandle;
	int particle_img;
	int PauseBack;
	int Font;
	int line_img;

	//judge
	unsigned int PlayCombo;
	unsigned int PlayMaxCombo;
	unsigned int PlayScore;
	unsigned int PlayJudge[4];
};