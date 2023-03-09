// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#include "StreamQueue.h"

#include <algorithm>
#include <cstring>

void woodnet::StreamQueue::clear()
{
	// ������� ���۸� 0���� ��ȯ�մϴ�.
	m_dataCount = m_readIndex = m_writeIndex = 0;
	memset(m_buffer, 0, m_size);
}

bool woodnet::StreamQueue::is_empty() const
{
	return m_dataCount == 0 ? true : false;
}

bool woodnet::StreamQueue::is_full() const
{
	return m_size == m_dataCount ? true : false;
}

int woodnet::StreamQueue::remain() const
{
	// ��� ������ ������ ����Ʈ ���� �����մϴ�.
	return m_size - m_dataCount;
}

int woodnet::StreamQueue::size() const
{
	return m_size;
}

int woodnet::StreamQueue::count() const
{
	// ���� ť�� ����� ����Ʈ ���� ��ȯ�մϴ�.
	return m_dataCount;
}

bool woodnet::StreamQueue::peek(char* peekBuf, int peekLen) const
{
	// ť���� �����͸� �������� �ʰ� �����͸� �����մϴ�.
	// ť�� �ִ� ũ�⺸�� �� ���� peek �� ���� �����ϴ�.
	if (peekLen > count())
		return false;

	// ���� �ε����� �� ũ�� ó������ �б� �ε������� �����մϴ�.
	if (m_readIndex < m_writeIndex)
	{
		memcpy(peekBuf, &m_buffer[m_readIndex], peekLen);
	}
	else
	{
		// �б� �ε����κ��� ť�� �������� ũ�⸦ ���մϴ�.
		const int back_part = m_size - m_readIndex;

		if (peekLen <= back_part)
		{
			memcpy(peekBuf, &m_buffer[m_readIndex], peekLen);
		}
		else
		{
			// ���� peek ���̸� ���մϴ�.
			const int fore_part = peekLen - back_part;

			memcpy(&peekBuf[0], &m_buffer[m_readIndex], back_part);
			memcpy(&peekBuf[back_part], &m_buffer[0], fore_part);
		}
	}

	return true;
}

int woodnet::StreamQueue::read(char* desBuf, int bufLen)
{
	if (is_empty()) return 0;

	// ���� ���� �ִ� ������ �� or ���ϴ� ������ �� �� �߿� ���� ����ŭ �д´�.
	const int read_count = std::min<short>(m_dataCount, bufLen);

	// �б� �ε����� ���� �ε������� �տ� ������ ó������ �б� �ε������� ����
	if (m_readIndex < m_writeIndex)
	{
		memcpy(desBuf, &m_buffer[m_readIndex], read_count);
	}
	else
	{
		// �б� �ε����κ��� ť�� �������� ũ�⸦ ���մϴ�.
		int back_part = m_size - m_readIndex;

		if (read_count <= back_part)
		{

			memcpy(desBuf, &m_buffer[m_readIndex], read_count);
		}
		else
		{
			int fore_part = read_count - back_part;
			memcpy(&desBuf[0], &m_buffer[m_readIndex], back_part);
			memcpy(&desBuf[back_part], &m_buffer[0], fore_part);
		}
	}

	m_dataCount -= read_count;
	m_readIndex += read_count;

	if (m_readIndex >= m_size)
		m_readIndex -= m_size;

	return read_count;
}

int woodnet::StreamQueue::write(const char* srcData, int bytesData)
{
	if (is_full()) return 0;

	const int left = remain();
	const int write_count = std::min<short>(left, bytesData);

	if (m_readIndex > m_writeIndex)
	{
		memcpy(&m_buffer[m_writeIndex], srcData, write_count);
	}
	else
	{
		const int back_space = m_size - m_writeIndex;

		if (back_space >= write_count)
		{
			memcpy(&m_buffer[m_writeIndex], srcData, write_count);
		}
		else
		{
			const int fore_space = write_count - back_space;
			memcpy(&m_buffer[m_writeIndex], &srcData[0], back_space);
			memcpy(&m_buffer[0], &srcData[back_space], fore_space);
		}
	}

	m_dataCount += write_count;
	m_writeIndex += write_count;

	if (m_writeIndex >= m_size)
		m_writeIndex -= m_size;

	return write_count;
}
