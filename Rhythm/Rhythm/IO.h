#pragma once

class Input
{
private:
	//�L�[�{�[�h�p�ϐ�
	char keys[256];
	char oldkeys[256];

	//�}�E�X�p�ϐ�
	int MousePosX;
	int MousePosY;
	int Mouse;
	int oldMouse;

public:
	Input();
	void Initialize();
	void Update();

public:
	/// <summary>
	/// �L�[�{�[�h����
	/// </summary>
	/// <param name="key">���̓L�[</param>
	/// <returns>key���</returns>
	bool GetKey(const int key);					//�L�[�������������Ă����
	bool GetKeyDown(const int key);				//�L�[�������ꂽ�u��
	bool GetKeyUp(const int key);				//�L�[�������ꂽ�u��

	//�}�E�X����
	int GetMousePointX();						//�}�E�X��X���W���擾
	int GetMousePointY();						//�}�E�X��Y���W���擾
	bool GetMouseClick(const int MouseInput);	//
	bool GetMouseDown(const int MouseInput);	//
	bool GetMouseUp(const int MouseInput);		//
};

