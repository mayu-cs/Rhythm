#include "DxLib.h"

#include "Start.h"
#include "IO.h"
#include "Result.h"
#include "Play.h"
#include "TimeSync.h"

Start::Start()
{
	NomalNote = LoadGraph("Resources\\Notes\\NomalNote.png");
	Cursor = LoadGraph("Resources\\Cursor\\Cursor.png");
}

void Start::start()
{
	Scene scene(NomalNote, Cursor);
	scene.GameStart();
}
