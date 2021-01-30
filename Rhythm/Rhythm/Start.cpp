#include "DxLib.h"

#include "Start.h"
#include "Result.h"
#include "Play.h"
#include "Title.h"

Start::Start()
{
}

void Start::start()
{
	Title title;
	title.start();

	Scene scene("Lyrith -–À‹{ƒŠƒŠƒX-");
	scene.GameStart();
}
