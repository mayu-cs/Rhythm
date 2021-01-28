#include "Line.h"
#include "DxLib.h"

Line::Line(int x) : x(x) { 
    height = 792 ;
    image = LoadGraph("Resources\\Particle\\tap.png");
}

void Line::draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
    DrawGraph(x, WIN_HEIGHT - height, image, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
