#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "string.h"

// базовый класс исключений
class Exception	
{
public:
	//конструктор, который в качестве параметра принимает указатель на массив символов (итог: строка с символами)
	Exception(const char * message);
	//возвращает сообщение об ошибки
	String getMessage() const;
private:
	//строка, содержащая сообщение об ошибке
	String message_;
};

//производный класс исключений (открыт ли файл для чтения)
class FileIsNotOpenException : public Exception
{
public:
	//конструктор без параметров
	FileIsNotOpenException();
};


//производный класс исключений (не выходит ли индекс за границы допустимого диапазона)
class IndexOutOfRangeException : public Exception
{
public:
	//конструктор без параметров
	IndexOutOfRangeException();
};

#endif