#include "DxLib.h"
#include "IO.h"

//コンストラクタ
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

//マウス/キー情報アップデート
void Input::Update() {
	//前フレームキーボード情報をキャッシュ
	for (auto i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	//キードード情報を取得
	GetHitKeyStateAll(keys);

	//マウス座標を取得
	GetMousePoint(&MousePosX, &MousePosY);
}

//キーが押し続けられている間
bool Input::GetKey(const int key) {
	return keys[key] ? true : false;
}

//キーが押された瞬間
bool Input::GetKeyDown(const int key) {
	return !keys[key] && oldkeys[key] ? true : false;
}

//キーが離された瞬間
bool Input::GetKeyUp(const int key) {
	return keys[key] && !oldkeys[key] ? true : false;
}

//マウスのX座標取得
int Input::GetMousePointX() {
	return MousePosX;
}

//マウスのY座標取得
int Input::GetMousePointY() {
	return MousePosY;
}
