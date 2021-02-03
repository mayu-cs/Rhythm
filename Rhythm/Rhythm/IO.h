#pragma once

class Input
{
private:
	//キーボード用変数
	char keys[256];
	char oldkeys[256];

	//マウス用変数
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
	/// キーボード入力
	/// </summary>
	/// <param name="key">入力キー</param>
	/// <returns>key状態</returns>
	bool GetKey(const int key);					//キーが押し続けられている間
	bool GetKeyDown(const int key);				//キーが押された瞬間
	bool GetKeyUp(const int key);				//キーが離された瞬間

	//マウス入力
	int GetMousePointX();						//マウスのX座標を取得
	int GetMousePointY();						//マウスのY座標を取得
	bool GetMouseClick(const int MouseInput);	//
	bool GetMouseDown(const int MouseInput);	//
	bool GetMouseUp(const int MouseInput);		//
};

