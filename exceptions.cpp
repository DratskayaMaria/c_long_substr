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
	Exception("Ошибка! Файл для чтения не открыт!\n")
{}


IndexOutOfRangeException::IndexOutOfRangeException():
	Exception("Ошибка! Индекс вне диапазона!\n")
{}