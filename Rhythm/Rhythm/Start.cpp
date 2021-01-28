#include "DxLib.h"

#include "Start.h"
#include "Result.h"
#include "Play.h"
#include "Title.h"

Start::Start()
{
	NomalNote = LoadGraph("Resources\\Notes\\NomalNote.png");
	Cursor = LoadGraph("Resources\\Cursor\\Cursor.png");
}

void Start::start()
{
	Title title;
	title.start();

	Scene scene(NomalNote, Cursor);
	scene.GameStart();
}
