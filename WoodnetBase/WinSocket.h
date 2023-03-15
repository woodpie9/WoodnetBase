// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#pragma once
#include <WinSock2.h>
#include <ws2ipdef.h>

#include "CommonDefines.h"
//#include "StreamQueue.h"

// 20230313 woodpie9 �ڵ� ���� ��������ۼ�
// TCP�� UDP�� ����и� �����ϴ� Ŭ����
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

	}


	SOCKET GetHandle();
	bool IsValid();

	HANDLE GetEventHandle();

	void Attach(SOCKET s);
	SOCKET Detach();


	bool Open(int iProtocol);
	bool Bind(SOCKADDR_IN& localAddr);

	void Close();
	void Shuthdown(int how = SD_BOTH);

protected:

	SOCKET m_socket_ = INVALID_SOCKET;
	HANDLE m_hEvent_ = WSA_INVALID_EVENT;
	SOCKADDR_IN m_localAddr = { 0, };


private:

	WinSocket(const WinSocket&) = delete;
	WinSocket& operator=(const WinSocket&) {}
	WinSocket(WinSocket&&) = delete;

};

WOODNET_END