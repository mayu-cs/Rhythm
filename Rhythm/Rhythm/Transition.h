#pragma once

const int __WIN_WIDTH = 1920; //�E�B���h�E����
const int __WIN_HEIGHT = 1080;//�E�B���h�E�c��

class BoxTransitionHeight
{
private:
	int font;
	int fontSpace;//������
	int adjustTextPosX;//�������炷
	float boxHeight;//�l�p�`�̍�����1/2
	float flame;
	float maxFlame;
	float speedX;//�C�[�W���O�̈�ʎ�
	int pal;
public:
	BoxTransitionHeight();
	void Update();
	void Draw();
private:
	void Initial();
};