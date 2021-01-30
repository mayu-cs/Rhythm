#include "Result.h"
#include "DxLib.h"
#include <iostream>
#include <string>

Result::Result(const unsigned int MaxCombo, const unsigned int Judge[4], const unsigned int PlayScore, const unsigned int Notesize) : 
	MaxCombo(MaxCombo),
	PlayScore(PlayScore)
{
	for (auto i = 0; i < 4; i++) {
		this->Judge[i] = Judge[i];
	}
	
	//背景/フォント素材ロード
	LoadDivGraph("Resources\\Font\\number.png", SCORE_SIZE, SCORE_SIZE, 1, 30, 44, Score_img);
	LoadDivGraph("Resources\\Font\\rank.png", EVALUATION_SIZE, EVALUATION_SIZE, 1, 171, 226, Evaluation_img);

	Background		= LoadGraph("Resources\\Background\\resultBack.png");
	BackgroundMask	= LoadGraph("Resources\\Background\\resultBox.png");
	Jacket			= LoadGraph("Resources\\MusicScore\\Data\\Lyrith -迷宮リリス-.png");

	//得点割合計算
	if (PlayScore != 0 && Notesize != 0) {
		Base_MaxScore = Notesize * 220;
		Percentage = (Base_MaxScore / PlayScore) * 100;
	}
	else {
		Base_MaxScore = 0;
		Percentage = 0;
	}

	if		(Percentage > 90) { Evaluation = EVALUATION_S; }
	else if (Percentage > 80) { Evaluation = EVALUATION_A; }
	else if (Percentage > 60) { Evaluation = EVALUATION_B; }
	else					  { Evaluation = EVALUATION_C; }

	Font = CreateFontToHandle("和田研細丸ゴシック2004絵文字P", 60, 0, DX_FONTTYPE_ANTIALIASING);
	J_Font = CreateFontToHandle("和田研細丸ゴシック2004絵文字P", 40, 0, DX_FONTTYPE_ANTIALIASING);
}

void Result::Start()
{
	while (ScreenFlip() == false && ProcessMessage() == false && ClearDrawScreen() == false) {
		//背景
		DrawGraph(0, 0, Background, false);

		//ジャケット
		DrawExtendGraph(1150, 250, 1825, 925 , Jacket, true);

		//リザルトボックス
		DrawGraph(120, 250, BackgroundMask, true);

		//スコア
		DrawGraph(220, 280, Evaluation_img[Evaluation], true);
		DrawStringToHandle(650, 835, std::to_string(PlayScore).c_str(), GetColor(255, 255, 255), Font);

		for (auto i = 0; i < 4; i++) {
			DrawStringToHandle(550, 560 + (i * 57), std::to_string(Judge[i]).c_str(), GetColor(255, 255, 255), J_Font);
		}
	}
}
