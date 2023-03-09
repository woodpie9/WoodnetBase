// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#pragma once
#include "CommonDefines.h"
#include <cstdlib>


// 230309 woodpie9 �ڵ� ����, �ּ� �ۼ���
// TCP ��Ʈ��ũ �����ʹ� ����Ʈ��Ʈ������ �ٷ��.
// ȯ�� ť�� ����Ʈ��Ʈ���� �����Ѵ�.

WOODNET_BEGIN

class StreamQueue
{
public:
	// ������ �ʴ� �����ڵ��� �����Ѵ�.
	StreamQueue() = delete;
	StreamQueue(const StreamQueue&) = delete;
	StreamQueue& operator=(const StreamQueue&) = delete;		// ��������� ����

	StreamQueue(const int size)
	{
		m_size = size;
		m_buffer = static_cast<char*>(malloc(size));
		clear();
	}
	~StreamQueue()
	{
		free(m_buffer);
	}

	void clear();

	bool is_empty() const;
	bool is_full() const;

	int remain() const;
	int size() const;
	int count() const;

	bool peek(char* peekBuf, int peekLen) const;
	int read(char* desBuf, int bufLen);
	int write(const char* srcData, int bytesData);

private:
	int m_size;					// ȯ�� ť�� ũ��
	short m_dataCount;			// ť�� �ִ� �������� ����
	short m_readIndex;			// ���� �����Ͱ� �ִ� ��ġ
	short m_writeIndex;			// �����͸� �� ���ִ� ��ġ
	char* m_buffer;				// �������� �迭�� ������

};



WOODNET_END