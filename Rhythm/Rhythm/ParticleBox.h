#pragma once

extern const int WIN_WIDTH; //�E�B���h�E����
extern const int WIN_HEIGHT;//�E�B���h�E�c��
class Box
{
	int x;
	int y;
	int width;
	int height;
	int pal;//�����x
	int speed;
	int flag;//0�̎��`�悳��Ȃ�

public:
	Box();
	bool Create();
	void Update();
	void Draw();
};

