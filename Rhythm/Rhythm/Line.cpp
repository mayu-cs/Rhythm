#include "Line.h"
#include "DxLib.h"

Line::Line(int x) :
    x(x)
{

}

void Line::draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
    DrawGraph(x, WIN_HEIGHT - height, LoadGraph("tap.png"), true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
