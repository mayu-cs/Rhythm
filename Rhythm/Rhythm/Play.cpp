#include "Play.h"
#include "DxLib.h"
#include <nlohmann/json.hpp>

Scene::Scene(int NomalNoteGraphHandle, int CursorGraphHandle) :
    NomalNote(NomalNoteGraphHandle),
    Cursor(CursorGraphHandle)
{
    Background = LoadGraph("Resources\\Background\\gameBack.png");

    input.Initialize();
    MouseX = input.GetMousePointX();

    //flag_y座標_初期化
    for (auto i = 0; i < BAR_NUM; i++) {
        for (auto j = 0; j < LANE_NUM; j++) {
            bar_flag[j][i] = false;
        }
        bar_PosY[i] = 0;
    }

    //システム変数初期化
    counter = 0;
    BPM = 160.0;
    speed = 5.f;

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
        for (int i = 0; i < LANE_NUM; i++) {
            bar_flag[i][counter % BAR_NUM] = true;
            bar_PosY[counter % BAR_NUM] = -100.f;
        }
        counter++;
    }
}

void Scene::UpdateObject()
{
    //bar座標更新
    for (int i = 0; i < LANE_NUM; i++) {
        for (int j = 0; j < BAR_NUM; j++) {
            bar_PosY[j] += speed;
            if (bar_flag[i][j]) {
                if (bar_PosY[j] > WIN_HEIGHT + 10) {
                    bar_flag[i][j] = false; //画面外に出たらfalse
                }
            }
        }
    }

    if (input.GetKeyDown(KEY_INPUT_SPACE)) {
        for (int i = 0; i < LANE_NUM; i++) {
            for (int j = 0; j < BAR_NUM; j++) {
                if (bar_flag[i][j]) {
                    switch (i) {
                    case 0:
                        if (collision.CircleCollision(C_MouseX, 770, 193 / 2, ((WIN_WIDTH + 572) / 4) / 2 - (105 / 2), bar_PosY[j] - 10.f, 105 / 2)) {
                            bar_flag[i][j] = false; //あたったらfalse
                        }
                        break;
                    case 1:
                        if (collision.CircleCollision(C_MouseX, 770, 193 / 2, ((WIN_WIDTH + 572) / 4 * 3) / 2 - (105 / 2), bar_PosY[j] - 10.f, 105 / 2)) {
                            bar_flag[i][j] = false; //あたったらfalse
                        }
                        break;
                    case 2:
                        if (collision.CircleCollision(C_MouseX, 770, (193 / 2), (WIN_WIDTH + 572) - (((WIN_WIDTH + 572) / 4) * 3) / 2 - (105 / 2), bar_PosY[j] - 10.f, 105 / 2)) {
                            bar_flag[i][j] = false; //あたったらfalse
                        }
                        break;
                    case 3:
                        if (collision.CircleCollision(C_MouseX, 770, (193 / 2), (WIN_WIDTH + 572) - ((WIN_WIDTH + 572) / 4) / 2 - (105 / 2), bar_PosY[j] - 10.f, 105 / 2)) {
                            bar_flag[i][j] = false; //あたったらfalse
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Scene::DrawObject()
{
    Clump_Point();

    //bar描画
    for (auto i = 0; i < LANE_NUM; i++) {
        for (auto j = 0; j < BAR_NUM; j++) {
            if (bar_flag[i][j]) {
                /*DrawCircle(100.f + i * 150.f, bar_PosY[j] - 10.f, 25, GetColor(255, 255, 255), TRUE);*/
                switch (i) {
                case 0:
                    DrawGraph(572 + (WIN_WIDTH / 4) / 2 - (105 / 2), bar_PosY[j] - 10.f, NomalNote, true);
                    break;
                case 1:
                    DrawGraph(572 + (WIN_WIDTH / 4 * 3) / 2 - (105 / 2), bar_PosY[j] - 10.f, NomalNote, true);
                    break;
                case 2:
                    DrawGraph(572 + WIN_WIDTH - ((WIN_WIDTH / 4) * 3) / 2 - (105 / 2), bar_PosY[j] - 10.f, NomalNote, true);
                    break;
                case 3:
                    DrawGraph(572 + WIN_WIDTH - (WIN_WIDTH / 4) / 2 - (105 / 2), bar_PosY[j] - 10.f, NomalNote, true);
                    break;
                }
            }
        }
    }
}

void Scene::Clump_Point()
{

    if (MouseX <= (WIN_WIDTH + 572) / 4) {
        /*DrawCircle((WIN_WIDTH / 4) / 2, WIN_HEIGHT / 5 * 4, 25, GetColor(255, 255, 255), true);*/
        DrawGraph(572 + (WIN_WIDTH / 4) / 2 - (197 / 2), 770, Cursor, true);
        C_MouseX = (WIN_WIDTH + 572 / 4) / 2 - (197 / 2);
    }
    else if (MouseX <= ((WIN_WIDTH + 572) / 4) * 2) {
        /*DrawCircle((WIN_WIDTH / 4 * 3) / 2, WIN_HEIGHT / 5 * 4, 25, GetColor(255, 255, 255), true);*/
        DrawGraph(572 + (WIN_WIDTH / 4 * 3) / 2 - (197 / 2), 770, Cursor, true);
        C_MouseX = (WIN_WIDTH + 572 / 4 * 3) / 2 - (197 / 2);
    }
    else if (MouseX <= ((WIN_WIDTH + 572) / 4) * 3) {
        /*DrawCircle(WIN_WIDTH - ((WIN_WIDTH / 4) * 3) / 2, WIN_HEIGHT / 5 * 4, 25, GetColor(255, 255, 255), true);*/
        DrawGraph(572 + (WIN_WIDTH - (572 + WIN_WIDTH / 4) * 3) / 2 - (197 / 2), 770, Cursor, true);
        C_MouseX = WIN_WIDTH + 572 - ((WIN_WIDTH + 572 / 4) * 3) / 2 - (197 / 2);
    }
    else {
        /*DrawCircle(WIN_WIDTH - (WIN_WIDTH / 4) / 2, WIN_HEIGHT / 5 * 4, 25, GetColor(255, 255, 255), true);*/
        DrawGraph(572 + WIN_WIDTH - (572 + WIN_WIDTH / 4) / 2 - (197 / 2), 770, Cursor, true);
        C_MouseX = WIN_WIDTH + 572 - (WIN_WIDTH + 572 / 4) / 2 - (197 / 2);
    }
}