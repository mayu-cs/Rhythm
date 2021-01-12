#include "Play.h"
#include "DxLib.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using nlohmann::json;
json ScoreData;
std::vector<int> MusicScore;

std::vector<std::string> S_Split(std::string str, char key)
{
    int first = 0;
    int last = str.find_first_of(key);

    std::vector<std::string> result;

    while (first < str.size())
    {
        std::string cache(str, first, last - first);
        result.push_back(cache);

        first = last + 1;
        last = str.find_first_of(key, first);

        if (last == std::string::npos)
        {
            last = str.size();
        }
    }

    return result;
}

Scene::Scene(int NomalNoteGraphHandle, int CursorGraphHandle) :
    NomalNote(NomalNoteGraphHandle),
    Cursor(CursorGraphHandle)
{
#pragma region Initialize_IO
    //IO初期化
    input.Initialize();
    MouseX = input.GetMousePointX();
#pragma endregion

#pragma region Initialize_Image
    //画像初期化
    Background = LoadGraph("Resources\\Background\\gameBack.png");
#pragma endregion

#pragma region Initialize_Score
    //譜面読み込み/整形
    std::ifstream stream("Resources\\MusicScore\\Data\\Musics.json");
    ScoreData = json::parse(stream);
    std::string score = ScoreData["map"];

    //削除文字
    char chars[] = "\"";

    for (auto i = 0; i < strlen(chars); i++) {
        score.erase(remove(score.begin(), score.end(), chars[i]), score.end());
    }

    for (auto cache_str : S_Split(score, ',')) {
        std::istringstream stream = std::istringstream(cache_str);
        int cache;
        stream >> cache;
        MusicScore.push_back(cache);
    }
#pragma endregion


    //システム変数初期化
    counter = 0;
    speed = 5.f;
    BPM = 150;

    for (auto i = 0; i < 200; i++) flag[i] = false;

    time_sync.SetBaseTime();
}

void Scene::GameStart()
{
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        //初期化
        input.Update();
        DrawGraph(0, 0, Background, true);

        MouseX = input.GetMousePointX();
        if (MouseX <= 0) {
            MouseX = 25;
        }
        else if (MouseX >= WIN_WIDTH - 25) {
            MouseX = WIN_WIDTH - 25;
        }

        MakeObject();
        UpdateObject();
        DrawObject();

        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { break; }
    }
}

void Scene::MakeObject()
{
    //bar生成
    if (time_sync.GetTime1MSSync() >= 60000 / BPM * counter) {
        if (MusicScore[counter] != 0 && flag[counter] == false) {
            flag[counter] = true;
            PosY[counter] = -100.f;
        }
        counter++;
    }
}

void Scene::UpdateObject()
{
    for (auto i = 0; i < 200; i++) {
        if (flag[i] == true) {
            PosY[i] += speed;
            if (PosY[i] > WIN_HEIGHT + 10) {
                flag[i] = false;
            }
        }
    }
}

void Scene::DrawObject()
{
    //Clump_Point();

    for (auto i = 0; i < 200; i++) {
        if (flag[i] == true) {
            switch (MusicScore[i]) {
                case 1:
                    DrawGraph(572 + (WIN_WIDTH / 4) / 2 - (105 / 2), PosY[i] - 10.0, NomalNote, true);
                    break;
                case 2:
                    DrawGraph(572 + (WIN_WIDTH / 4 * 3) / 2 - (105 / 2), PosY[i] - 10.0, NomalNote, true);
                    break;
                case 3:
                    DrawGraph(572 + WIN_WIDTH - ((WIN_WIDTH / 4) * 3) / 2 - (105 / 2), PosY[i] - 10.0, NomalNote, true);
                    break;
                case 4:
                    DrawGraph(572 + WIN_WIDTH - (WIN_WIDTH / 4) / 2 - (105 / 2), PosY[i] - 10.0, NomalNote, true);
                    break;
            }
            /*DrawGraph(572 + (WIN_WIDTH / 4) / 2 - (105 / 2), PosY[i] - 10.0, NomalNote, true);*/
        }
    }
}

void Scene::Clump_Point()
{
    //null
}