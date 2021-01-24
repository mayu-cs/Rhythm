#pragma once

#pragma region Definition
constexpr auto SET_1US		=	static_cast<long long>(1);
constexpr auto SET_10US		=	static_cast<long long>(10);
constexpr auto SET_100US	=	static_cast<long long>(100);
constexpr auto SET_1MS		=	static_cast<long long>(1000);
constexpr auto SET_10MS		=	static_cast<long long>(10000);
constexpr auto SET_100MS	=	static_cast<long long>(100000);
constexpr auto SET_1S		=	static_cast<long long>(1000000);
#pragma endregion

class TimeSync
{
private:
	//�����
	long long baseTime;
	long long cacheTime;

	//���t���[������
	long long Time;

public:
	void SetBaseTime();
	long long GetTime1USSync();		//1us�P�ʂ̌o�ߎ��Ԃ�Ԃ�
	long long GetTime10USSync();	//10us�P�ʂ̌o�ߎ��Ԃ�Ԃ�
	long long GetTime100USSync();	//100us�P�ʂ̌o�ߎ��Ԃ�Ԃ�
	long long GetTime1MSSync();		//1ms�P�ʂ̌o�ߎ��Ԃ�Ԃ�
	long long GetTime10MSSync();	//10ms�P�ʂ̌o�ߎ��Ԃ�Ԃ�
	long long GetTime100MSSync();	//100ms�P�ʂ̌o�ߎ��Ԃ�Ԃ�
	long long GetTime1SSync();		//1000ms�P�ʂ̌o�ߎ��Ԃ�Ԃ�
};