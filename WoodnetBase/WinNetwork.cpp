#include "WinNetwork.h"

// Windows Socket�� ����ϱ� ���� ���̺귯��
#pragma comment(lib, "Ws2_32.lib")

WOODNET_BEGIN

// Windows ���� �Լ� �� ù ������ ȣ���ؾ��ϴ� �Լ�
// windows ���� ������ �����ϰ� ���� ������ ���� ������ �ִ´�
// ���ø����̼� �Ǵ� DLL�� WSAStartup�� ���������� ȣ���� �Ŀ��� ���� �Լ��� ���� ����
bool WinNetwork::Init()
{
	// Windows ���� ����� 2.2�� �����Ѵ�.
	// Windows ���� ������ ���� ������ �����ϱ� ���Ͽ� WSADATA ����ü�� �����͸� �ѱ��.
	if (!WSAStartup(MAKEWORD(2, 2), &m_wsa_data_))
	{
		return false;
	}

	return true;
}

void WinNetwork::CleanUp()                           
{
	// Winsock2�� ����� �����Ѵ�.
	WSACleanup();
}

WOODNET_END