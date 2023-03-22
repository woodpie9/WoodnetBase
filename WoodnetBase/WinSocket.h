#pragma once
#include <WinSock2.h>
#include <ws2ipdef.h>

#include "CommonDefines.h"

// 20230317 �ڵ� �ۼ� �Ϸ�
// 20230313 woodpie9 �ڵ� ���� ��������ۼ�
// TCP�� UDP�� �����κ��� �����ϴ� Ŭ����
// �� ���������� ���� ����ϴ� �� bind�� �ּһ��ΰ�...?


WOODNET_BEGIN

struct SOCKET_INFO
{
	SOCKET s;
	SOCKADDR_IN addr;
};


class WinSocket
{
public:
	WinSocket()
	{

	}

	~WinSocket()
	{
		if (m_socket_ != INVALID_SOCKET) closesocket(m_socket_);
		if (m_hEvent_ != WSA_INVALID_EVENT) WSACloseEvent(m_hEvent_);
	}


	SOCKET GetHandle() const;
	bool IsValid() const;

	HANDLE GetEventHandle() const;

	void Attach(SOCKET s);				// ������ �����մϴ�.
	SOCKET Detach();					// ���� ������ �����մϴ�.

	bool EventSelect(long lNetworkEvents);

	bool Open(int iProtocol);			// Ư�� ���� ������ݿ� ���߾� ���ε� �� ������ ����ϴ�.
	bool Bind(SOCKADDR_IN& localAddr);	// ���Ͽ� �����ּҸ� �����մϴ�.

	void Close();
	void Shuthdown(int how = SD_BOTH);	// ���Ͽ��� �۽� �Ǵ� ������ ������� �ʵ��� �����մϴ�.

protected:

	SOCKET m_socket_ = INVALID_SOCKET;
	HANDLE m_hEvent_ = WSA_INVALID_EVENT;
	SOCKADDR_IN m_local_addr_ = { 0, };


private:

	WinSocket(const WinSocket&) = delete;
	WinSocket& operator=(const WinSocket&) {}
	WinSocket(WinSocket&&) = delete;

};

WOODNET_END