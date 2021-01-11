#pragma once
#include "DxLib.h"

extern const int WIN_WIDTH = 1920;
extern const int WIN_HEIGHT = 1080;

class Initialize
{
public:
	int components()
	{
		SetMainWindowText("Untitled");
		ChangeWindowMode(FALSE);
		SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
		SetWindowSizeChangeEnableFlag(FALSE, FALSE);
		SetWindowSizeExtendRate(1.0);
		SetBackgroundColor(30, 30, 30);
		SetWaitVSyncFlag(TRUE);

		if (DxLib_Init() == -1) {
			return -1;
		}
		SetDrawScreen(DX_SCREEN_BACK);

		return 0;
	}
};