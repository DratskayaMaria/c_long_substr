#include "pch.h"
#include "exceptions.h"

Exception::Exception(const char * message):
	message_(message)
{}

String Exception::getMessage() const
{
	return message_;
}

FileIsNotOpenException::FileIsNotOpenException():
	Exception("������! ���� ��� ������ �� ������!\n")
{}


IndexOutOfRangeException::IndexOutOfRangeException():
	Exception("������! ������ ��� ���������!\n")
{}