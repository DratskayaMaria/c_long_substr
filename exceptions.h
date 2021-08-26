#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "string.h"

// ������� ����� ����������
class Exception	
{
public:
	//�����������, ������� � �������� ��������� ��������� ��������� �� ������ �������� (����: ������ � ���������)
	Exception(const char * message);
	//���������� ��������� �� ������
	String getMessage() const;
private:
	//������, ���������� ��������� �� ������
	String message_;
};

//����������� ����� ���������� (������ �� ���� ��� ������)
class FileIsNotOpenException : public Exception
{
public:
	//����������� ��� ����������
	FileIsNotOpenException();
};


//����������� ����� ���������� (�� ������� �� ������ �� ������� ����������� ���������)
class IndexOutOfRangeException : public Exception
{
public:
	//����������� ��� ����������
	IndexOutOfRangeException();
};

#endif