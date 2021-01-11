#include "DxLib.h"
#include "Start.h"
#include "Initialize.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// DXlib‚Ì‰Šú‰»
	Initialize initialize;
	if (initialize.components() == -1) {
		return -1;
	}

	Start GameStart;
	GameStart.start();

	DxLib_End();
	return 0;
}