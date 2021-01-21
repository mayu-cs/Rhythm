#include "Play.h"
#include "DxLib.h"
#include "Particle.h"
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
Particle **particle;

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
    //IO初期化
    input = new Input();
    input->Initialize();
    MouseX = input->GetMousePointX();
    MouseY = input->GetMousePointY();

    //画像初期化
    Background = LoadGraph("Resources\\Background\\gameBack.png");
    particle_img = LoadGraph("Resources\\Particle\\particle.png");

    particle = new Particle*[32];
    for (auto i = 0; i < 32; i++) {
        particle[i] = new Particle(particle_img, (double)MouseX, (double)MouseY, 5, 18);
    }
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

    //システム変数初期化
    counter = 0;
    speed = 11.f;
    BPM = 150;

    for (auto i = 0; i < 200; i++) flag[i] = false;

    time_sync.SetBaseTime();
}

Scene::~Scene()
{
    delete input;
}

void Scene::GameStart()
{
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        //初期化
        input->Update();
        MouseX = input->GetMousePointX();
        MouseY = input->GetMousePointY();
        DrawGraph(0, 0, Background, true);

       /* MouseX = input->GetMousePointX();
        if (MouseX <= 0) {
            MouseX = 25;
        }
        else if (MouseX >= WIN_WIDTH - 25) {
            MouseX = WIN_WIDTH - 25;
        }*/

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
        if (MusicScore.size() == counter) { return; }

        if (MusicScore[counter] != 0 && flag[counter] == false) {
            flag[counter] = true;
            PosY[counter] = -100.f;

            switch (MusicScore[counter]) {
                case 1: PosX[counter] = LANE1_POSITION_X; break;
                case 2: PosX[counter] = LANE2_POSITION_X; break;
                case 3: PosX[counter] = LANE3_POSITION_X; break;
                case 4: PosX[counter] = LANE4_POSITION_X; break;
            }
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

#ifdef DEBUG
            oldClick = ClickFlag;
            if (GetMouseInput() & MOUSE_INPUT_LEFT) { ClickFlag = true; }
            else { ClickFlag = false; }

            if (input->GetMouseClick(MOUSE_INPUT_LEFT)) {
                if (collision.CircleCollision(
                    PosX[i] + 198 / 2, PosY[i] + 198 / 2, 198 / 2,
                    (double)(MouseX), (double)(MouseY), 10.0 )) {
                    flag[i] = false;
                }

                if (oldClick == false && ClickFlag == true) {
                    for (auto i = 0; i < 32; i++) {
                        delete particle[i];
                        particle[i] = new Particle(particle_img, (double)MouseX - 50, (double)MouseY - 50, 5, 18);
                    }
                    Particle_Flag = true;

                }
            }

            if (Particle_Flag) {
                for (auto i = 0; i < 32; i++) {
                    particle[i]->Draw();

                    if (particle[32 - 1]->GetFlag() == false) {
                        Particle_Flag = false;
                    }
                }
            }
#endif // DEBUG

        }
    }

#ifdef DEBUG
    DrawCircle(MouseX, MouseY, 10, GetColor(255, 255, 255), true);
#endif // DEBUG

}

void Scene::DrawObject()
{
    for (auto i = 0; i < 200; i++) {
        if (flag[i] == true) {
            DrawGraph(PosX[i], PosY[i] - 10.0, NomalNote, true);
        }
    }
}