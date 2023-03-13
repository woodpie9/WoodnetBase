// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#pragma once
#include <WinSock2.h>
#include <ws2ipdef.h>

#include "CommonDefines.h"
//#include "StreamQueue.h"

// 20230313 woodpie9 코드 생성 헤더파일작성
// TCP와 UDP의 공통분모를 묘사하는 클래스
// 두 프로토콜이 같이 사용하는 건 bind랑 주소뿐인가...?


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