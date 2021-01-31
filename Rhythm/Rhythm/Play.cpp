#include "Play.h"
#include "DxLib.h"
#include "Result.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

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

//Load json score data
void Scene::loadJson(const char *ScoreFile, const char *level)
{
    //���ʓǂݍ���/���`
    std::string ScoreFData = "Resources\\MusicScore\\Data\\";
    ScoreFData += ScoreFile;
    ScoreFData += ".json";

    std::ifstream stream(ScoreFData.c_str());
    ScoreData = nlohmann::json::parse(stream);
    std::string score = ScoreData[level];
    std::string BPM_Cache = ScoreData["BPM"];
    BPM = std::stoi(BPM_Cache);

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

//Constructor
Scene::Scene(const char *MusicFile, const char *level) : SongName(MusicFile)
{
    //IO������
    input           = new Input();
    input           ->Initialize();
    MouseX          = input->GetMousePointX();
    MouseY          = input->GetMousePointY();

    //�摜������
    Background      = LoadGraph ("Resources\\Background\\gameBack.png");
    PauseBack       = LoadGraph ("Resources\\Background\\PauseBack.png");
    particle_img    = LoadGraph ("Resources\\Particle\\particle.png");
    line_img        = LoadGraph ("Resources\\Particle\\tap.png");
    NomalNote       = LoadGraph ("Resources\\Notes\\NomalNote.png");
    Cursor          = LoadGraph ("Resources\\Cursor\\Cursor.png");
    particle        = new Particle*[PARTICLE_QUANTITY];

    for (auto i = 0; i < PARTICLE_QUANTITY; i++) {
        particle[i] = new Particle(particle_img, (double)MouseX, (double)MouseY, 5, 18);
    }

    //���ʃf�[�^������
    loadJson(MusicFile, level);
    PlayScore   = 0;
    PosX        = new double[MusicScore.size()];
    PosY        = new double[MusicScore.size()];
    flag        = new bool[MusicScore.size()];
    for (auto i = 0; i < MusicScore.size(); i++) {
        flag[i] = false;
    }

    //�V�X�e���ϐ�������
    std::string SoundData = "Resources\\MusicScore\\Data\\";
    SoundData   += MusicFile;
    SoundData   += ".mp3";
    MusicHandle = LoadSoundMem(SoundData.c_str());
    ChangeVolumeSoundMem(100, MusicHandle);
    counter             = 0;
    EndCounter          = 0;
    speed               = 20.f;
    PlayCombo           = 0;
    PlayMaxCombo        = 0;
    SoundFlag           = false;
    EndFlag             = false;
    ActiveNotes_Counter = 0;
    alpha               = 0;

    //�t�H���g
    Font = CreateFontToHandle("�a�c���׊ۃS�V�b�N2004�G����P", 40, 8, DX_FONTTYPE_ANTIALIASING);

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

//Destructor
Scene::~Scene()
{
    delete input;
    delete[] PosX;
    delete[] PosY;
    delete[] flag;
}

void Scene::GameStart()
{
    //�������ԃZ�b�g
    time_sync.SetBaseTime();
    while (ScreenFlip() == false && ProcessMessage() == false && ClearDrawScreen() == false)
    {
        //���͏�����
        input->Update();

        if (PauseFlag == false) {
            Update();
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
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

        if (input->GetKeyDown(KEY_INPUT_ESCAPE)) {
            DxLib_End();
        }

        if (EndCounter >= 200) {
            clear.Update();
            clear.Draw();
        }
        if (EndCounter >= 300) {

            alpha -= 5;

            if (alpha <= 0) {
                break;
            }
        }
        else {
            if (alpha != 255) {
                alpha += 5;
            }
        }
    }

    Result result(PlayMaxCombo, PlayJudge, PlayScore, ActiveNotes_Counter);
    StopSoundMem(MusicHandle);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    result.Start();

    return;
}

void Scene::Update()
{
    //�ő�Combo���㏑��
    if (PlayCombo < PlayMaxCombo) {
        PlayMaxCombo = PlayCombo;
    }

    //1���҂��Ă���Ȃ𗬂�(Adjust)
    if (counter == 8 && SoundFlag == false) {
        PlaySoundMem(MusicHandle, DX_PLAYTYPE_BACK);
        SoundFlag = true;
    }

    //���͏�����
    MouseX = input->GetMousePointX();
    MouseY = input->GetMousePointY();
    oldClick = ClickFlag;
    if (input->GetKey(KEY_INPUT_D) || input->GetKey(KEY_INPUT_F) || 
        input->GetKey(KEY_INPUT_J) || input->GetKey(KEY_INPUT_K) || 
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
    if (time_sync.GetTime1MSSync() >= (unsigned long long)15000 / BPM * counter) {
        if (EndFlag == true) {
            //�I���J�E���^���Z
            EndCounter++;
        }
        else {
            if (MusicScore[counter] == END_FLAG) { EndFlag = true; }
            if (MusicScore[counter] != NULL && MusicScore[counter] != END_FLAG && flag[counter] == false) {
                PosY[counter] = -100.0;
                switch (MusicScore[counter]) {
                case 1: PosX[counter] = LANE1_POSITION_X; break;
                case 2: PosX[counter] = LANE2_POSITION_X; break;
                case 3: PosX[counter] = LANE3_POSITION_X; break;
                case 4: PosX[counter] = LANE4_POSITION_X; break;
                }
                flag[counter] = true;
            }
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
            PlayJudge[BAD]++;
            ActiveNotes_Counter++;
        }

        //�N���b�N����
        if (ClickFlag && collision.CircleCollision(
            PosX[i] + 198.0 / 2.0, PosY[i] + 198.0 / 2.0, 198.0 / 2.0,
            (double)CursorPosX + 100, (double)CursorPosY + 100.0, 20.0, &Distance)) {
            flag[i] = false;
            Timing_Judge(MusicScore[i], Distance);
        }
    }
    if (EndFlag == true) { return; }
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
    //�G�t�F�N�g�`��
    if (ClickFlag) {
        SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
        DrawGraph(CursorPosX, 400, line_img, true);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    }

    //�m�[�c�`��
    for (auto i = 0; i < MusicScore.size(); i++) {
        if (flag[i] == false) { continue; }
        DrawGraph(PosX[i], PosY[i], NomalNote, true);
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
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        }
    }

    std::string msg = "score : ";
    msg += std::to_string(PlayScore);
    DrawStringToHandle(50, 80, msg.c_str(), GetColor(120, 200, 255), Font);
    DrawStringToHandle(50, 150, SongName.c_str(), GetColor(120, 200, 255), Font);

    //DEBUG
    DrawStringToHandle(50, 220, std::to_string(ActiveNotes_Counter).c_str(), GetColor(120, 200, 255), Font);

    DrawGraph(MouseX - 100, CursorPosY, Cursor, true);

#ifdef DEBUG
    DrawStringToHandle(10, 100, std::to_string(PlayScore).c_str(), GetColor(255, 255, 255), Font);
    DrawGraph(MouseX - 100, CursorPosY, Cursor, true);
    /*DrawPixel(MouseX, 500, GetColor(255, 255, 255));*/
#endif // DEBUG
}

void Scene::ClumpCursor()
{
    if (MouseX - 100 <= 570) {
        CursorPosX = LANE1_POSITION_X - 25.0;
    }
    else if (MouseX >= 570 && MouseX <= 780) {
        CursorPosX = LANE1_POSITION_X - 25.0;
    }
    else if (MouseX >= 780 && MouseX <= 985) {
        CursorPosX = LANE2_POSITION_X - 25.0;
    }
    else if (MouseX >= 985 && MouseX <= 1185) {
        CursorPosX = LANE3_POSITION_X - 25.0;
    }
    else {
        CursorPosX = LANE4_POSITION_X - 25.0;
    }
}

void Scene::Timing_Judge(const unsigned int lane, const double Distance)
{
    if (Distance < 70) {
        Judge[lane - 1] = "Perfect";
        JudgePosY[lane - 1] = 789;
        Trans[lane - 1] = 255;
        PlayScore += 220;
        PlayJudge[PERFECT]++;
        PlayCombo++;
        ActiveNotes_Counter++;
    }
    else if (Distance < 80) {
        Judge[lane - 1] = "Excellent";
        JudgePosY[lane - 1] = 789;
        Trans[lane - 1] = 255;
        PlayScore += 100;
        PlayJudge[EXCELLENT]++;
        PlayCombo++;
        ActiveNotes_Counter++;
    }
    else if (Distance < 90) {
        Judge[lane - 1] = "Good";
        JudgePosY[lane - 1] = 789;
        Trans[lane - 1] = 255;
        PlayScore += 50;
        PlayJudge[GOOD]++;
        PlayCombo++;
        ActiveNotes_Counter++;
    }
    else if (Distance >= 90) {
        Judge[lane - 1] = "Bad";
        JudgePosY[lane - 1] = 789;
        Trans[lane - 1] = 255;
        PlayJudge[BAD]++;
        PlayCombo = 0;
        ActiveNotes_Counter++;
    }
}