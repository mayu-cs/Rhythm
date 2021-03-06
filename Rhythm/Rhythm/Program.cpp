#include "DxLib.h"
#include "Start.h"
#include "Initialize.h"
#include <iostream>
#include <ctime>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// DXlibÌú»
	Initialize initialize;
	if (initialize.components() == -1) {
		return -1;
	}

	srand(time(nullptr));

	AddFontResourceEx("Resources\\Font\\ac¤×ÛSVbN2004G¶P.ttf", FR_PRIVATE, NULL);
	Start GameStart;
	GameStart.start();

	DxLib_End();
	return 0;
}