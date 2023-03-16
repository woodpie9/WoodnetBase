#pragma once
#include "WinSocket.h"


// 20230316 코드 생성
// Windows Socket을 사용하기 위한 초기화와 종료를 위한 클린업 코드

WOODNET_BEGIN

class WinNetwork
{
public:
	WinNetwork(const WinNetwork&) = delete;
	WinNetwork(WinNetwork&&) = delete;
	WinNetwork& operator=(const WinNetwork&) = delete;

	WinNetwork() {}
	~WinNetwork() {}

	bool Init();
	void CleanUp();

private:
	WSADATA m_wsd = { 0, };
};

WOODNET_END