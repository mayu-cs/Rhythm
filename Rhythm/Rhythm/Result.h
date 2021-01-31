#pragma once

#define SCORE_SIZE			10
#define DISPLAY_SCORE_SIZE	6
#define EVALUATION_SIZE		4

#define PERFECT			0
#define EXCELLENT		1
#define GOOD			2
#define BAD				3

#define EVALUATION_S	3
#define EVALUATION_A	2
#define EVALUATION_B	1
#define EVALUATION_C	0

class Result
{
private:
	int SongNumber;
	int Font;
	int J_Font;
	int Background;
	int BackgroundMask;
	int Jacket;
	int Title[3];
	int Evaluation_img[EVALUATION_SIZE];
	int Score_img[SCORE_SIZE];


	unsigned int	alpha;
	unsigned int	PlayScore;
	unsigned int	MaxCombo;
	unsigned int	Judge[4];
	unsigned int	Base_MaxScore;
	unsigned int	Percentage;
	unsigned short	Evaluation;

public:
	Result(const unsigned int MaxCombo, const unsigned int Judge[4], const unsigned int PlayScore, const unsigned int Notesize, const char *SongName, const int SongNumber);
	int Start();
};