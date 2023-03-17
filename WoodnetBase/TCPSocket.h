#pragma once
#include <assert.h>
#include "WinSocket.h"
#include "StreamQueue.h"

// 20230314 woodpie9 �ڵ� ���� 
// WinSocket�� ��� �޴� TCP ������ �����ϴ� Ŭ����


WOODNET_BEGIN

class TCPSocket : public WinSocket
{
	struct TCPBuffer
	{
		short count;		// �������� �� ����
		short done;			// ���� �������� ��
		short bufSize;
		char* pBuffer;
	};

public:
	TCPSocket(const TCPSocket&) = delete;
	TCPSocket& operator=(const TCPSocket&) = delete;

	TCPSocket();
	~TCPSocket();

	// Ŭ���̾�Ʈ�� ������ �����ϱ� ���� IP�ּҿ� ��Ʈ��ȣ ����
	bool Connect(SOCKADDR_IN& remoteAddr) const;		
	// ������ ������ ������ ��� ���Ͽ� ������ ��ġ�մϴ�.
	bool Listen();

	// ����� ���Ͽ� �����͸� �����ϴ�.
	int	Send(char* pOutBuf, int nLen, int& error, LPWSAOVERLAPPED pOv = NULL, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine = NULL) const;
	// ����� ���� �Ǵ� ���ε��� ���� ���� ���Ͽ��� �����͸� �޽��ϴ�.
	int	Recv(char* pInBuf, int nLen, int& error, LPWSAOVERLAPPED pOv = NULL, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine = NULL);


	bool SendUpdate();		// �����͸� 
	bool RecvUpdate();

	bool PostPacket(char* buffer, int nSize) const;		// �����͸� ť�� ���ϴ�.
	bool PeekPacket(char* buffer, int nSize) const;		// �����͸� ť���� ������ �ʰ� �н��ϴ�.
	bool ReadPacket(char* buffer, int nSize) const;		// �����͸� ť���� �н��ϴ�.

	void Reset();


	void SetNetID(NetworkObjectID ID);
	NetworkObjectID GetNetID();

protected:
	NetworkObjectID m_NetID;

private:
	TCPBuffer m_send_buf_;		// �۽Ź���. �۽��� �����͸� �����ϴ� ����
	TCPBuffer m_recv_buf_;		// ���Ź���. ������ �����͸� �����ϴ� ����

	StreamQueue* m_pSendQ;		// �۽Ź���. ���α׷����� �۽��� �����͸� �����ϴ� ��Ʈ�� ť
	StreamQueue* m_pRecvQ;		// ���Ź���. ���α׷��� ������ �����͸� �����ϴ� ��Ʈ�� ť
};


WOODNET_END