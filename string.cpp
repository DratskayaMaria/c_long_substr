#include "pch.h"
#include "string.h"
#include <iostream>
#include "exceptions.h"

//конструктор без парметров (итог: пустая строка, длина которой равна 0)
String::String():
	length_ (0),
	ourString_ (nullptr)
{}

//конструктор, который в качестве параметра принимает размер строки (итог: пустая строка указанного размера)
String::String(int newLength)
{
	length_ = newLength;
	ourString_ = new char[newLength + 1];
	//символ '\0' - признак конца строки
	ourString_[newLength] = '\0';
}

//конструктор, который в качестве параметра принимает указатель на массив символов (итог: строка с символами)
String::String(const char * newString)
{
	length_ = strlen(newString);
	ourString_ = new char[length_ + 1];

	for (int i = 0; i < length_; i++)
	{
		ourString_[i] = newString[i];
	}
	//символ '\0' - признак конца строки
	ourString_[length_] = '\0';
}

//конструктор копирования
String::String(const String & otherString)
{
	//случай, если исходная строка уже равна строке, которую необходимо скопировать
	if (this != &otherString)
	{
		this->length_ = strlen(otherString.ourString_);
		this->ourString_ = new char[this->length_ + 1];

		for (int i = 0; i < this->length_; i++)
		{
			this->ourString_[i] = otherString.ourString_[i];
		}
		//символ '\0' - признак конца строки
		this->ourString_[this->length_] = '\0';
	}

}

//деструктор 
String::~String()
{
	delete[] ourString_;
	length_ = 0;
}



//возвращает длину строки
int String::getLength() const
{
	return length_;
}

//возвращает указатель на массив символов строки
char * String::getOurString() const
{
	return ourString_;
}



//оператор индексирования: возвращает символ с указанным индексом
char & String::operator [] (int index) const
{
	//проверка на то, что индекс больше или равен нулю, при этом меньше длины строки
	if ((index < 0) || (index >= length_))
	{
		throw IndexOutOfRangeException();
	}
	return ourString_[index];
}

//оператор присваивания
String & String::operator = (const String &otherString)
{
	//случай, если исходная строка уже равна строке, которую необходимо присвоить
	if (this == &otherString)
	{
		return *this;
	}
	//случай, если исходная строка не равна строке, которую необходимо присвоить, при этом исходная строка не является нулевой
	if ((this != & otherString) && (this->ourString_ != nullptr))
	{
		delete[] this->ourString_;
	}
	
	this->length_ = strlen(otherString.ourString_);
	this->ourString_ = new char[this->length_ + 1];

	//присваиваем каждому элементу исходной строка нужное значение
	for (int i = 0; i < this->length_; i++)
	{
		this->ourString_[i] = otherString.ourString_[i];
	}
	this->ourString_[this->length_] = '\0';

	return *this;
}

//оператор сравнения строк (равны ли они)
bool const String::operator == (const String & otherString) const
{
	//сравнение размеров
	if (this->length_ != otherString.length_)
	{
		return false;
	}
	//поэлементное сравнение
	for (int i = 0; i < this->length_; i++)
	{
		if (this->ourString_[i] != otherString.ourString_[i])
		{
			return false;
		}
	}
	return true;
}

//добавляет символ в конец строки и увеличивает её размер (используется в функции поиска LCS)
void String::pushBack(const char &newElement)
{
	//создание временной строки и запись туда всех элементов исходной
	String temporaryString(this->length_);
	for (int i = 0; i < this->length_; i++)
	{
		temporaryString.ourString_[i] = this->ourString_[i];
	}
	delete[] this->ourString_;

	//увеличение длины сиходной строки на 1 (место для нового элемента)
	this->length_ = temporaryString.length_ + 1;
	this->ourString_ = new char[this->length_ + 1];

	//запись данных из временной строки в исходную, запись нового элемента
	for (int i = 0; i < temporaryString.length_; i++)
	{
		this->ourString_[i] = temporaryString.ourString_[i];
	}
	this->ourString_[this->length_ - 1] = newElement;
	//символ '\0' - признак конца строки
	this->ourString_[this->length_] = '\0';

}

//переставляет элементы массива в обратном порядке (используется в функции поиска LCS)
void String::reverse()
{
	//создание временной строки и запись туда всех элементов исходной
	String temporaryString;
	for (int i = this->length_-1; i >= 0; i--)
	{
		temporaryString.pushBack(this->ourString_[i]);
	}

	//запись данных из временной строки в исходную в обратном порядке
	for (int i = 0; i < this->length_; i++)
	{
		this->ourString_[i] = temporaryString.ourString_[i];
	}
}

void String::newLineSymbolToSpace()
{
	for (int i = 0; i < length_; i++)
	{
		if (ourString_[i] == '\n')
		{
			ourString_[i] = ' ';
		}
	}
}



//дружественная функция: оператор вывода строки
std::ostream & operator<< (std::ostream & out, const String & string)
{
	for (int i = 0; i < string.length_; i++)
	{
		out << string.ourString_[i];
	}
	return out;
}

//дружественная функция: оператор ввода строки
std::istream & operator >> (std::istream & in, String & string)
{
	//переменная для хранения считанного символа
	char symbol;
	//чтение из файла до символа конца строки
	while (!in.eof())
	{
		//чтение из файла символа
		in.get(symbol);

		if (in.eof())
		{
			return in;
		}

		//создание временной строки и запись туда всех элементов исходной, а также нового элемента
		char* tempString = new char[string.length_ + 1];

		for (int i = 0; i < string.length_; i++)
		{
			tempString[i] = string.ourString_[i];
		}
		tempString[string.length_] = symbol;
		//удаление исходной строки
		delete[] string.ourString_;

		//увеличение размера исходной строки
		string.length_++;
		//запись данных из временной строки в исходную
		string.ourString_ = new char[string.length_ + 1];
		for (int i = 0; i < string.length_; i++)
		{
			string.ourString_[i] = tempString[i];
		}
		delete[] tempString;
		//символ '\0' - признак конца строки
		string.ourString_[string.length_] = '\0';
	};

}
