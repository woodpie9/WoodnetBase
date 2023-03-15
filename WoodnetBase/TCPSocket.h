// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#pragma once
#include "WinSocket.h"
#include "StreamQueue.h"

// 20230314 woodpie9 �ڵ� ���� 
// WinSocket�� ��� �޴� TCP ������ �����ϴ� Ŭ����


WOODNET_BEGIN

class TCPSocket : public WinSocket
{
	struct TCPBuffer
	{
		
	};

public:
	TCPSocket(const TCPSocket&) = delete;
	TCPSocket& operator=(const TCPSocket&) = delete;

	TCPSocket();
	~TCPSocket();

	bool	Connect(SOCKADDR_IN& remoteAddr);

	bool	Listen();

	int		Recv(char* pInBuf, int nLen, int& error, LPWSAOVERLAPPED pOv = NULL, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine = NULL);
	int		Send(char* pOutBuf, int nLen, int& error, LPWSAOVERLAPPED pOv = NULL, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine = NULL);



	bool SendUpdate();
	bool RecvUpdate();

	bool PostPacket(char* buffer, int nSize);
	bool ReadPacket(char* buffer, int nSize);
	bool PeekPacket(char* buffer, int nSize);

	void Reset();

protected:


private:
	TCPBuffer m_SendBuf;
	TCPBuffer m_RecvBuf;

	StreamQueue* m_pSendQ;
	StreamQueue* m_pRecvQ;
};


WOODNET_END