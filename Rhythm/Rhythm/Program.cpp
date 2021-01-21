#include "DxLib.h"
#include "Start.h"
#include "Initialize.h"
#include <iostream>
#include <ctime>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// DXlibÇÃèâä˙âª
	Initialize initialize;
	if (initialize.components() == -1) {
		return -1;
	}

	srand(time(nullptr));

	Start GameStart;
	GameStart.start();

	DxLib_End();
	return 0;
}