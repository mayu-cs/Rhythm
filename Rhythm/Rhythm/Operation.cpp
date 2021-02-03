#include "Operation.h"
#include "DxLib.h"


Operation::Operation()
{
	Back = LoadGraph("Resources\\Background\\operation.png");
	trans = 0;
	flag = false;
}

void Operation::Draw()
{
	while (ScreenFlip() == false && ProcessMessage() == false && ClearDrawScreen() == false)
	{
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			flag = true;
		}

		if (flag == true) {
			trans -= 5;
		}
		else if(trans <= 255) {
			trans += 5;
		}

		if (flag == true && trans == 0) {
			break;
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
		DrawGraph(0, 0, Back, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
