#include "DxLib.h"
#include "IO.h"

//�R���X�g���N�^
Input::Input() {
	for (auto i = 0; i < 256; i++) {
		keys[i] = 0;
		oldkeys[0] = 0;
	}
}

void Input::Initialize()
{
	Update();
}

//�}�E�X/�L�[���A�b�v�f�[�g
void Input::Update() {
	//�O�t���[���L�[�{�[�h�����L���b�V��
	for (auto i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	//�L�[�h�[�h�����擾
	GetHitKeyStateAll(keys);

	//�}�E�X���W���擾
	GetMousePoint(&MousePosX, &MousePosY);
}

//�L�[�������������Ă����
bool Input::GetKey(const int key) {
	return keys[key] ? true : false;
}

//�L�[�������ꂽ�u��
bool Input::GetKeyDown(const int key) {
	return !keys[key] && oldkeys[key] ? true : false;
}

//�L�[�������ꂽ�u��
bool Input::GetKeyUp(const int key) {
	return keys[key] && !oldkeys[key] ? true : false;
}

//�}�E�X��X���W�擾
int Input::GetMousePointX() {
	return MousePosX;
}

//�}�E�X��Y���W�擾
int Input::GetMousePointY() {
	return MousePosY;
}

bool Input::GetMouseClick(const int MouseInput)
{
	return GetMouseInput() & MouseInput;
}
