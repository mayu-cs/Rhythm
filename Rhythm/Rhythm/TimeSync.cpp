#include "DxLib.h"
#include "TimeSync.h"

void TimeSync::SetBaseTime() {
	baseTime = GetNowHiPerformanceCount();
}

//1us単位の経過時間を返す
long long TimeSync::GetTime1USSync() {
	return (GetNowHiPerformanceCount() - baseTime) / SET_1US;
}

//10us単位の経過時間を返す
long long TimeSync::GetTime10USSync() {
	return (GetNowHiPerformanceCount() - baseTime) / SET_10US;
}

//100us単位の経過時間を返す
long long TimeSync::GetTime100USSync() {
	return (GetNowHiPerformanceCount() - baseTime) / SET_100US;
}

//1ms単位の経過時間を返す
long long TimeSync::GetTime1MSSync() {
	return (GetNowHiPerformanceCount() - baseTime) / SET_1MS;
}

//10ms単位の経過時間を返す
long long TimeSync::GetTime10MSSync() {
	return (GetNowHiPerformanceCount() - baseTime) / SET_10MS;
}

//100ms単位の経過時間を返す
long long TimeSync::GetTime100MSSync() {
	return (GetNowHiPerformanceCount() - baseTime) / SET_100MS;
}

//1000ms単位の経過時間を返す
long long TimeSync::GetTime1SSync() {
	return (GetNowHiPerformanceCount() - baseTime) / SET_1S;
}
