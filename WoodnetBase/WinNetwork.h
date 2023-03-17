#pragma once
#include "WinSocket.h"

// 20230317 �߰� �м�, �ּ� �ۼ�
// 20230316 �ڵ� ����
// Windows Socket�� ����ϱ� ���� �ʱ�ȭ�� ��                           

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
	WSADATA m_wsa_data_ = { 0, };		// Windows ���� ������ ���� ������ ��� ���� ����ü
};

WOODNET_END