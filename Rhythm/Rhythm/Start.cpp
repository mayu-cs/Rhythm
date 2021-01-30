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

	Scene scene(music.c_str());
	//Scene scene("Lyrith -���{�����X-");
	scene.GameStart();
}
