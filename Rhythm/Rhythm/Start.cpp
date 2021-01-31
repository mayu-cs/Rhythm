#include "DxLib.h"

#include "MusicSelect.h"
#include "Start.h"
#include "Result.h"
#include "Play.h"
#include "Title.h"

Start::Start() { }

void Start::start()
{
	Title title;
	if (title.start() == -1) { return; }

	while (true)
	{
		MusicSelect select;
		if (select.LoadMusicSelect() == -1) { break; }

		std::string music = select.getnum();
		std::string level = select.getlevel();
		Scene scene(music.c_str(), level.c_str());
		if (scene.GameStart() == -1) { break; }
		if (ProcessMessage() == true) { break; }
	}
}
