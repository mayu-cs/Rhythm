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

Particle **particle;
nlohmann::json ScoreData;
std::vector<int> MusicScore;
std::string Judge[4];

//������Split�֐�(C#�ɂ�����<~.split(',')>)
std::vector<std::string> S_Split(std::string str, char key)
{
    int first = 0;
    int last = str.find_first_of(key);

    std::vector<std::string> result;

    while (first < str.size()) {
        std::string cache(str, first, last - first);
        result.push_back(cache);

        first = last + 1;
        last = str.find_first_of(key, first);

        if (last == std::string::npos) {
            last = str.size();
        }
    }

    return result;
}

void loadJson()
{
    //���ʓǂݍ���/���`
    std::ifstream stream("Resources\\MusicScore\\Data\\Lyrith -���{�����X-.json");
    ScoreData = nlohmann::json::parse(stream);
    std::string score = ScoreData["map"];

    //�폜����
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
}

Scene::Scene(int NomalNoteGraphHandle, int CursorGraphHandle) :
    NomalNote(NomalNoteGraphHandle),
    Cursor(CursorGraphHandle)
{
    //IO������
    input = new Input();
    input->Initialize();
    MouseX = input->GetMousePointX();
    MouseY = input->GetMousePointY();

    //�摜������
    Background = LoadGraph("Resources\\Background\\gameBack.png");
    PauseBack = LoadGraph("Resources\\Background\\PauseBack.png");
    particle_img = LoadGraph("Resources\\Particle\\particle.png");

    particle = new Particle*[PARTICLE_QUANTITY];
    for (auto i = 0; i < PARTICLE_QUANTITY; i++) {
        particle[i] = new Particle(particle_img, (double)MouseX, (double)MouseY, 5, 18);
    }

    //���ʃf�[�^������
    loadJson();
    PlayScore = 0;
    PosX = new double[MusicScore.size()];
    PosY = new double[MusicScore.size()];
    flag = new bool[MusicScore.size()];
    for (auto i = 0; i < MusicScore.size(); i++) {
        flag[i] = false;
    }

    //�V�X�e���ϐ�������
    MusicHandle = LoadSoundMem("Resources\\MusicScore\\Data\\Lyrith -���{�����X-.mp3");
    ChangeVolumeSoundMem(70, MusicHandle);
    counter = 0;
    speed = 20.f;
    BPM = 177;
    SoundFlag = false;

    //�t�H���g
    Font = CreateFontToHandle("�a�c���׊ۃS�V�b�N2004�G����P", 40, 8, DX_FONTTYPE_ANTIALIASING_EDGE);

    //������W
    JudgePosX[0] = LANE1_POSITION_X;
    JudgePosX[1] = LANE2_POSITION_X;
    JudgePosX[2] = LANE3_POSITION_X;
    JudgePosX[3] = LANE4_POSITION_X;
    for (auto i = 0; i < 4; i++) {
        JudgePosY[i] = 790;
        Trans[i] = 255;
    }
}

Scene::~Scene()
{
    delete input;
    delete[] PosX;
    delete[] PosY;
    delete[] flag;
}

void Scene::GameStart()
{
    time_sync.SetBaseTime();

    while (ScreenFlip() == false && ProcessMessage() == false && ClearDrawScreen() == false)
    {
        input->Update();

        if (PauseFlag == false) {
            Update();
            Draw();
            ClumpCursor();
        }
        else {
            Draw();
            Pause();
        }

        if (input->GetKeyDown(KEY_INPUT_E)) {
            PauseFlag = true;
        }
    }
}

void Scene::Update()
{
    if (counter == 1 && SoundFlag == false) {
        PlaySoundMem(MusicHandle, DX_PLAYTYPE_BACK);
        SoundFlag = true;
    }

    MouseX = input->GetMousePointX();
    MouseY = input->GetMousePointY();
    oldClick = ClickFlag;
    if (input->GetKeyDown(KEY_INPUT_D) || input->GetKeyDown(KEY_INPUT_F) || 
        input->GetKeyDown(KEY_INPUT_J) || input->GetKeyDown(KEY_INPUT_K) || 
        input->GetMouseClick(KEY_INPUT_LEFT) || input->GetMouseClick(KEY_INPUT_RIGHT)) { ClickFlag = true; }
    else { ClickFlag = false; }

    //�p�[�e�B�N��������
    if (oldClick == false && ClickFlag == true) {
        for (auto i = 0; i < PARTICLE_QUANTITY; i++) {
            delete particle[i];
            particle[i] = new Particle(particle_img, CursorPosX + 25.0, CursorPosY, 5.0, 18.0);
        }
        Particle_Flag = true;
    }

    //�m�[�c����
    if (time_sync.GetTime1MSSync() >= (unsigned long long)60000 / BPM * counter) {
        if (MusicScore.size() == counter) { return; }
        if (MusicScore[counter] == 11) { return; }
        if (MusicScore[counter] != 0 && flag[counter] == false) {
            PosY[counter] = -100.0;
            switch (MusicScore[counter]) {
                case 1: PosX[counter] = LANE1_POSITION_X; break;
                case 2: PosX[counter] = LANE2_POSITION_X; break;
                case 3: PosX[counter] = LANE3_POSITION_X; break;
                case 4: PosX[counter] = LANE4_POSITION_X; break;
            }
            flag[counter] = true;
        }
        counter++;
    }

    //�m�[�c�X�V
    for (auto i = 0; i < MusicScore.size(); i++) {
        //�m�[�c���Ȃ���Ύ��̏���
        if (flag[i] == false) continue;

        //�X�s�[�h���Z
        PosY[i] += speed;
        if (PosY[i] > WIN_HEIGHT + 10.0) {
            flag[i] = false;
        }

        //�N���b�N����
        if (ClickFlag && collision.CircleCollision(
            PosX[i] + 198.0 / 2.0, PosY[i] + 198.0 / 2.0, 198.0 / 2.0,
            PosX[i] + 198.0 / 2.0, (double)CursorPosY + 100.0, 100.0, &Distance)) {
            flag[i] = false;
            Timing_Judge(MusicScore[i], Distance);
        }
    }
}

void Scene::Pause()
{
    DrawGraph(0, 0, PauseBack, true);
    if (input->GetKeyDown(KEY_INPUT_ESCAPE)) {
        PauseFlag = false;
    }
}

void Scene::Draw()
{
    DrawGraph(0, 0, Background, true);

    //�m�[�c�`��
    for (auto i = 0; i < MusicScore.size(); i++) {
        if (flag[i] == true) {
            DrawGraph(PosX[i], PosY[i], NomalNote, true);
        }
    }

    //�p�[�e�B�N���`��
    if (Particle_Flag) {
        for (auto i = 0; i < PARTICLE_QUANTITY; i++) {
            particle[i]->Draw();

            if (particle[PARTICLE_QUANTITY - 1]->GetFlag() == false) {
                Particle_Flag = false;
            }
        }
    }

    for (auto i = 0; i < 4; i++) {
        if (JudgePosY[i] <= 789) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, Trans[i]);
            if (Judge[i] == "Perfect") {
                DrawStringToHandle(JudgePosX[i] + 5, JudgePosY[i], Judge[i].c_str(), GetColor(255, 255, 255), Font);
            }
            else if (Judge[i] == "Excellent") {
                DrawStringToHandle(JudgePosX[i] - 15, JudgePosY[i], Judge[i].c_str(), GetColor(255, 255, 255), Font);
            }
            else {
                DrawStringToHandle(JudgePosX[i] + 40, JudgePosY[i], Judge[i].c_str(), GetColor(255, 255, 255), Font);
            }
            JudgePosY[i]--;
            Trans[i] -= 4;
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        }
    }

#ifdef DEBUG
    DrawStringToHandle(10, 100, std::to_string(PlayScore).c_str(), GetColor(255, 255, 255), Font);
    DrawGraph(MouseX - 100, CursorPosY, Cursor, true);
    DrawPixel(MouseX, 500, GetColor(255, 255, 255));
#endif // DEBUG
}

void Scene::ClumpCursor()
{
    if (MouseX - 100 <= 570) {
        CursorPosX = LANE1_POSITION_X - 25.0;
    }
    else if (MouseX - 100 >= 570 && MouseX <= 780) {
        CursorPosX = LANE1_POSITION_X - 25.0;
    }
    else if (MouseX >= 780 && MouseX <= 985) {
        CursorPosX = LANE2_POSITION_X - 25.0;
    }
    else if (MouseX - 100 >= 985 && MouseX <= 1185) {
        CursorPosX = LANE3_POSITION_X - 25.0;
    }
    else {
        CursorPosX = LANE4_POSITION_X - 25.0;
    }
}

void Scene::Timing_Judge(const unsigned int lane, const double Distance)
{
    if (Distance < 50) {
        Judge[lane - 1] = "Perfect";
        JudgePosY[lane - 1] = 789;
        Trans[lane - 1] = 255;
        PlayScore += 220;
    }
    else if (Distance < 70) {
        Judge[lane - 1] = "Excellent";
        JudgePosY[lane - 1] = 789;
        Trans[lane - 1] = 255;
        PlayScore += 100;
    }
    else if (Distance < 80) {
        Judge[lane - 1] = "Good";
        JudgePosY[lane - 1] = 789;
        Trans[lane - 1] = 255;
        PlayScore += 50;
    }
    else if (Distance >= 80) {
        Judge[lane - 1] = "Bad";
        JudgePosY[lane - 1] = 789;
        Trans[lane - 1] = 255;
    }
}