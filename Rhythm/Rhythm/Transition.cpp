#include "Transition.h"
#include"DxLib.h"

BoxTransitionHeight::BoxTransitionHeight()
{
	font = CreateFontToHandle("�a�c���׊ۃS�V�b�N2004�G����P", 150, 3, DX_FONTTYPE_ANTIALIASING);
	fontSpace = -20;//������
	adjustTextPosX = 0;//�������炷
	boxHeight = 0;//�l�p�`�̍���
	flame = 0;
	maxFlame = 20;
	speedX = flame / maxFlame;//�C�[�W���O�̈�ʎ�
	pal = 80;
}

void BoxTransitionHeight::Update()
{
	//�X�V����
	if (flame <= maxFlame)//�t���[�����ŏI�n�_�܂œ��B���Ă��Ȃ���
	{
		boxHeight = 460 * (1 - (1 - speedX) * (1 - speedX));//�l�p�`�̍���
		fontSpace = 40 * (1 - (1 - speedX) * (1 - speedX));//�����Ԃ̕�
		SetFontSpaceToHandle(fontSpace, font);//�t�H���g�̕����Ԃ̕��𔽉f
		adjustTextPosX = 240 * (1 - (1 - speedX) * (1 - speedX));//�����`��ʒu�̂���̏C��
	}

	//�t���[�����X�V
	flame++;
	speedX = flame / maxFlame;

	//��ʐ���
	if (flame > 100)//�|�[�Y����(100-20)
	{
		//BoxTransitionHeight::Initial();//������

		//���U���g��ʂ�
	}
}

void BoxTransitionHeight::Draw()
{
	//�l�p�`�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DrawBox(0, __WIN_HEIGHT / 2 - boxHeight/2, __WIN_WIDTH, __WIN_HEIGHT / 2 + boxHeight/2, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//����"GameClear"�̕`��
	DrawStringToHandle(610 - adjustTextPosX, 490, "Game Clear", GetColor(255, 255, 255), font);

}

void BoxTransitionHeight::Initial()
{
	//������
	fontSpace = -20;
	SetFontSpaceToHandle(fontSpace,font);
	adjustTextPosX = 0;
	boxHeight = 0;
	flame = 0;
}
