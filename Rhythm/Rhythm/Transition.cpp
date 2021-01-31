#include "Transition.h"
#include"DxLib.h"

BoxTransitionHeight::BoxTransitionHeight()
{
	font = CreateFontToHandle("和田研細丸ゴシック2004絵文字P", 150, 3, DX_FONTTYPE_ANTIALIASING);
	fontSpace = -20;//文字間
	adjustTextPosX = 0;//文字ずらす
	boxHeight = 0;//四角形の高さ
	flame = 0;
	maxFlame = 20;
	speedX = flame / maxFlame;//イージングの一般式
	pal = 80;
}

void BoxTransitionHeight::Update()
{
	//更新処理
	if (flame <= maxFlame)//フレームが最終地点まで到達していない間
	{
		boxHeight = 460 * (1 - (1 - speedX) * (1 - speedX));//四角形の高さ
		fontSpace = 40 * (1 - (1 - speedX) * (1 - speedX));//文字間の幅
		SetFontSpaceToHandle(fontSpace, font);//フォントの文字間の幅を反映
		adjustTextPosX = 240 * (1 - (1 - speedX) * (1 - speedX));//文字描画位置のずれの修正
	}

	//フレームを更新
	flame++;
	speedX = flame / maxFlame;

	//画面推移
	if (flame > 100)//ポーズ時間(100-20)
	{
		//BoxTransitionHeight::Initial();//初期化

		//リザルト画面へ
	}
}

void BoxTransitionHeight::Draw()
{
	//四角形の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DrawBox(0, __WIN_HEIGHT / 2 - boxHeight/2, __WIN_WIDTH, __WIN_HEIGHT / 2 + boxHeight/2, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//文字"GameClear"の描画
	DrawStringToHandle(610 - adjustTextPosX, 490, "Game Clear", GetColor(255, 255, 255), font);

}

void BoxTransitionHeight::Initial()
{
	//初期化
	fontSpace = -20;
	SetFontSpaceToHandle(fontSpace,font);
	adjustTextPosX = 0;
	boxHeight = 0;
	flame = 0;
}
