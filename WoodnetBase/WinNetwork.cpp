#include "WinNetwork.h"

// Windows Socket�� ����ϱ� ���� ���̺귯��
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