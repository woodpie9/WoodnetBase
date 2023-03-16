#include "WinNetwork.h"

// Windows Socket을 사용하기 위한 라이브러리
#pragma comment(lib, "Ws2_32.lib")

WOODNET_BEGIN

bool WinNetwork::Init()
{
	if (0 != WSAStartup(MAKEWORD(2, 2), &m_wsd))
	{
		return false;
	}

	return true;
}

void WinNetwork::CleanUp()
{
	WSACleanup();
}

WOODNET_END