// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#pragma once
#include "WinSocket.h"

// 20230314 woodpie9 �ڵ� ���� 
// WinSocket�� ��� �޴� UDP ������ �����ϴ� Ŭ����

WOODNET_BEGIN

class UDPSocket : public WinSocket
{
	struct UDPBuffer
	{

	};

public:
	UDPSocket(const UDPSocket&) = delete;
	UDPSocket& operator=(const UDPSocket&) = delete;

	UDPSocket();
	~UDPSocket();

	int		RecvFrom(char* pInBuf, int nLen, int& error, SOCKADDR_IN& remoteAddr, LPWSAOVERLAPPED pOv = NULL);
	int		SendTo(char* pOutBuf, int nLen, int& error, SOCKADDR_IN& remoteAddr, LPWSAOVERLAPPED pOv = NULL);


};



WOODNET_END