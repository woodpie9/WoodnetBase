#include "TCPSocket.h"

woodnet::TCPSocket::TCPSocket()
{
	//HAVE TO DO: ��Ʈ��ũ ���� �����ؼ��� ������ ���� ���Ϸ� �����ϴ� ���� �����ϴ�.
	const int sendBufSize = 4192;
	const int recvBufSize = 4192;

	m_NetID = -1;

	m_send_buf_.count = 0;
	m_send_buf_.done = 0;
	m_send_buf_.bufSize = sendBufSize;
	m_send_buf_.pBuffer = static_cast<char*>(malloc(sendBufSize));

	m_recv_buf_.count = 0;
	m_recv_buf_.done = 0;
	m_recv_buf_.bufSize = recvBufSize;
	m_recv_buf_.pBuffer = static_cast<char*>(malloc(recvBufSize));

	m_pRecvQ = new StreamQueue(sendBufSize * 4);
	m_pSendQ = new StreamQueue(recvBufSize * 4);
}

woodnet::TCPSocket::~TCPSocket()
{
	free(m_send_buf_.pBuffer);
	free(m_recv_buf_.pBuffer);

	delete m_pRecvQ;
	delete m_pSendQ;
}

bool woodnet::TCPSocket::Connect(SOCKADDR_IN& remoteAddr) const
{
	// ������� ���� ����, ������ �ּҸ� ����, ����ü�� ����, ...
	if (WSAConnect(m_socket_, (SOCKADDR*)(&remoteAddr), sizeof(SOCKADDR_IN), NULL,
		NULL, NULL, NULL) == SOCKET_ERROR)
	{
		// ���� ���� �� ���ŷ ������ ��� ������ ��� �Ϸ��� �� ���� ��찡 �����ϴ�.
		// �̷��� ��쿡�� WSAEWOULDBLOCK�� ��ȯ�Ѵ�. �۾��� �������̶�� �ǹ��Դϴ�.
		if (WSAEWOULDBLOCK != WSAGetLastError()) return false;
	}

	return true;
}

bool woodnet::TCPSocket::Listen()
{
	if (::listen(m_socket_, SOMAXCONN) == SOCKET_ERROR) return false;

	return true;
}

int woodnet::TCPSocket::Send(char* pOutBuf, int nLen, int& error, LPWSAOVERLAPPED pOv, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) const
{
	WSABUF wsabuf;		// Windock �Լ����� ����ϴ� ������ ����
	wsabuf.buf = pOutBuf;
	wsabuf.len = nLen;


	DWORD nSent = 0, flag = 0;

	if (WSASend(m_socket_, &wsabuf, 1, &nSent, flag, pOv, lpCompletionRoutine) != SOCKET_ERROR)
	{
		return nSent;
	}

	int err = WSAGetLastError();
	error = err;

	if (WSAEWOULDBLOCK == err || WSA_IO_PENDING == err) return 0;

	return -1;
}

int woodnet::TCPSocket::Recv(char* pInBuf, int nLen, int& error, LPWSAOVERLAPPED pOv, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	WSABUF wsabuf;		// Windock �Լ����� ����ϴ� ������ ����
	wsabuf.buf = pInBuf;
	wsabuf.len = nLen;

	DWORD nRecv = 0, flag = 0;

	// ����� ����, WSABUF ������ �迭�� ���� ������, ������ ��, �����۾� �Ϸ�� ���ŵ� �������� ����Ʈ ���� ��� ������, ... 
	if (WSARecv(m_socket_, &wsabuf, 1, &nRecv,
		&flag, (LPWSAOVERLAPPED)pOv, lpCompletionRoutine) != SOCKET_ERROR)
	{
		return nRecv;
	}

	int err = WSAGetLastError();
	error = err;

	if (WSAEWOULDBLOCK == err || WSA_IO_PENDING == err) return 0;

	return -1;
}

bool woodnet::TCPSocket::SendUpdate()
{
	int error = 0;
	int nSent = 0;
	char* pStart = nullptr;
	int remain = m_send_buf_.count - m_send_buf_.done;

	if (remain > 0)
	{
		// �۽� ���۰� ������� �ʴٸ� ���� �����͸� ���� �����ϴ�.
		pStart = &m_send_buf_.pBuffer[m_send_buf_.done];
	}
	else if (remain == 0)
	{
		// �۽� ������ �����͸� �� ���´ٸ� ��Ʈ��ť���� �����͸� �����ɴϴ�.
		m_send_buf_.count = m_pSendQ->read(m_send_buf_.pBuffer, m_send_buf_.bufSize);
		m_send_buf_.done = 0;

		remain = m_send_buf_.count;
		pStart = m_send_buf_.pBuffer;
	}

	// 0���� ���� ���� ������ �۾� ����
	assert(remain >= 0);

	nSent = Send(pStart, remain, error);
	if (nSent < 0) return false;

	m_send_buf_.done += nSent;

	return true;
}

bool woodnet::TCPSocket::RecvUpdate()
{
	int error = 0;

	// ���� ������ �����͸� �����ɴϴ�.
	int space = m_recv_buf_.bufSize - m_recv_buf_.count;
	if (space > 0)
	{
		int nRecv = Recv(&m_recv_buf_.pBuffer[m_recv_buf_.count], space, error);

		if (nRecv > 0)
		{
			m_recv_buf_.count += nRecv;
		}
	}

	// ���� ������ �����͸� ��Ʈ�� ť�� �����ϴ�.
	int remain = m_recv_buf_.count - m_recv_buf_.done;

	// 0���� ���� ���� ������ �۾� ����
	assert(remain >= 0);

	// ���� �����Ͱ� �ִٸ� �����ϴ�.
	if (remain > 0)
	{
		m_recv_buf_.done += m_pRecvQ->write(&m_recv_buf_.pBuffer[m_recv_buf_.done], remain);
	}

	// �����͸� ��� �������� ���� ���۸� �����մϴ�.
	if (m_recv_buf_.done == m_recv_buf_.count)
	{
		m_recv_buf_.count = 0;
		m_recv_buf_.done = 0;
	}

	return true;
}

bool woodnet::TCPSocket::PostPacket(char* buffer, int nSize) const
{
	if (m_pSendQ->remain() < nSize) return false;

	m_pSendQ->write(buffer, nSize);

	return true;
}

bool woodnet::TCPSocket::PeekPacket(char* buffer, int nSize) const
{
	return m_pRecvQ->peek(buffer, nSize);
}

bool woodnet::TCPSocket::ReadPacket(char* buffer, int nSize) const
{
	if (m_pRecvQ->count() < nSize) return false;

	m_pRecvQ->read(buffer, nSize);

	return true;
}

void woodnet::TCPSocket::Reset()
{
	m_send_buf_.count = 0;
	m_send_buf_.done = 0;

	m_recv_buf_.count = 0;
	m_recv_buf_.done = 0;

	m_pSendQ->clear();
	m_pRecvQ->clear();
}

