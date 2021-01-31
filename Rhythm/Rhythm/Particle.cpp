#include "Particle.h"
#include "DxLib.h"
#include <iostream>
#include <ctime>

Particle::Particle(const int Handle, double PosX, double PosY, double MinSize, double MaxSize) : particle(Handle)
{
	this->PosX = (double)(PosX + rand() % 150);
	this->PosY = (double)(PosY + rand() % 150);
	XSize = MinSize + (double)(rand() * (MaxSize - MinSize + 1.0) / (1.0 + RAND_MAX));
	YSize = MinSize + (double)(rand() * (MaxSize - MinSize + 1.0) / (1.0 + RAND_MAX));
	UpPos = ((rand() % 20 + 30.0) / 5.0);
	Trans = 15;
	Transfer = 255;
	Flag = true;
}

void Particle::Draw()
{
	if (Flag == false) { return; }

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)Transfer);
	DrawExtendGraph(PosX, PosY, PosX + XSize, PosY + YSize, particle, true);
	PosY -= UpPos;
	Transfer -= Trans;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (Transfer <= 0) {
		Flag = false;
	}
}

bool Particle::GetFlag()
{
	return Flag;
}
