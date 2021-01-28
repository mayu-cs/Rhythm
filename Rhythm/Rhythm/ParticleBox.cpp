#include "ParticleBox.h"
#include"DxLib.h"

extern const int WIN_WIDTH; //�E�B���h�E����
extern const int WIN_HEIGHT;//�E�B���h�E�c��

Box::Box()
{
	flag = 0;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	pal = 0;
	speed = 0;
}

bool Box::Create()
{
	if (flag == 0)
	{
		flag = 1;

		height = rand() % 100 + 5;
		do {//�������c�����傫���Ԑ����������i�K���c���ɂȂ�悤�ɂ���j
			width = rand() % 70 + 4;
		} while (width > height);
		do {//�o���ӏ��𕶎��̔��Ȃ��ʒu�Ɍ��肷��
			x = rand() % WIN_WIDTH - width / 2;
		} while (x > WIN_WIDTH / 3 && x < WIN_WIDTH * 2 / 3);
		y = WIN_HEIGHT + height / 2;
		pal = 100;
		speed = rand() % 10 + 4;

		return true;
	}
	return false;
}

void Box::Update()
{
	if (flag)
	{
		y -= speed;
		pal--;
		if (pal < 0)
		{
			flag = 0;
		}
	}
}

void Box::Draw()
{
	if (flag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, pal);
		DrawBox(x - width / 2, y - height / 2, x + width / 2, y + height / 2, GetColor(50, 60, 220), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}