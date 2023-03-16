#pragma once
#include "WinSocket.h"


// 20230316 �ڵ� ����
// Windows Socket�� ����ϱ� ���� �ʱ�ȭ�� ���Ḧ ���� Ŭ���� �ڵ�

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