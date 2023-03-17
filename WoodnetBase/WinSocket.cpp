#include "WinSocket.h"

SOCKET woodnet::WinSocket::GetHandle() const
{
	return m_socket_;
}

bool woodnet::WinSocket::IsValid() const
{
	return ((INVALID_SOCKET == m_socket_) ? false : true);
}


HANDLE woodnet::WinSocket::GetEventHandle() const
{
	return m_hEvent_;
}

void woodnet::WinSocket::Attach(SOCKET s)
{
	m_socket_ = s;
}

SOCKET woodnet::WinSocket::Detach()
{
	SOCKET s = m_socket_;
	m_socket_ = INVALID_SOCKET;
	return s;
}

bool woodnet::WinSocket::Open(int iProtocol)
{
	if (iProtocol == IPPROTO_TCP)
	{
		// IPv4 �ּ� �йи� ���, �ŷ��� �� �ִ� ����� ���� ��� ����Ʈ ��Ʈ���� �����ϴ� ����, ����� ��������, ������ ������ Ư��, ���� �׷� ID, �߰� �Ӽ� ����
		m_socket_ = WSASocket(AF_INET, SOCK_STREAM, iProtocol, NULL, NULL, WSA_FLAG_OVERLAPPED);
	}
	else if (IPPROTO_UDP)
	{
		// IPv4�ּ� �йи� ���, ������ ���� ������ ������ �� ���� ������ �����ͱ׷��� �����ϴ� ����, ... 
		m_socket_ = WSASocket(AF_INET, SOCK_DGRAM, iProtocol, NULL, NULL, WSA_FLAG_OVERLAPPED);
	}

	if (!IsValid()) return false;

	return true;
}

bool woodnet::WinSocket::Bind(SOCKADDR_IN& localAddr)
{
	if (::bind(m_socket_, (SOCKADDR*)(&localAddr), sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		return false;

	m_local_addr_ = localAddr;

	return false;
}

void woodnet::WinSocket::Close()
{
	::closesocket(m_socket_);
	m_socket_ = INVALID_SOCKET;
}

void woodnet::WinSocket::Shuthdown(int how)
{
	::shutdown(m_socket_, how);
}
