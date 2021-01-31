#include "DxLib.h"

#include "MusicSelect.h"
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

	MusicSelect select;
	select.LoadMusicSelect();
	std::string music = select.getnum();
	std::string level = select.getlevel();

	Scene scene(music.c_str(),level.c_str());
	//Scene scene("Lyrith -–À‹{ƒŠƒŠƒX-");
	scene.GameStart();
}
