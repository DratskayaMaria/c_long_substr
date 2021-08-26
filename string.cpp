#include "pch.h"
#include "string.h"
#include <iostream>
#include "exceptions.h"

//����������� ��� ��������� (����: ������ ������, ����� ������� ����� 0)
String::String():
	length_ (0),
	ourString_ (nullptr)
{}

//�����������, ������� � �������� ��������� ��������� ������ ������ (����: ������ ������ ���������� �������)
String::String(int newLength)
{
	length_ = newLength;
	ourString_ = new char[newLength + 1];
	//������ '\0' - ������� ����� ������
	ourString_[newLength] = '\0';
}

//�����������, ������� � �������� ��������� ��������� ��������� �� ������ �������� (����: ������ � ���������)
String::String(const char * newString)
{
	length_ = strlen(newString);
	ourString_ = new char[length_ + 1];

	for (int i = 0; i < length_; i++)
	{
		ourString_[i] = newString[i];
	}
	//������ '\0' - ������� ����� ������
	ourString_[length_] = '\0';
}

//����������� �����������
String::String(const String & otherString)
{
	//������, ���� �������� ������ ��� ����� ������, ������� ���������� �����������
	if (this != &otherString)
	{
		this->length_ = strlen(otherString.ourString_);
		this->ourString_ = new char[this->length_ + 1];

		for (int i = 0; i < this->length_; i++)
		{
			this->ourString_[i] = otherString.ourString_[i];
		}
		//������ '\0' - ������� ����� ������
		this->ourString_[this->length_] = '\0';
	}

}

//���������� 
String::~String()
{
	delete[] ourString_;
	length_ = 0;
}



//���������� ����� ������
int String::getLength() const
{
	return length_;
}

//���������� ��������� �� ������ �������� ������
char * String::getOurString() const
{
	return ourString_;
}



//�������� ��������������: ���������� ������ � ��������� ��������
char & String::operator [] (int index) const
{
	//�������� �� ��, ��� ������ ������ ��� ����� ����, ��� ���� ������ ����� ������
	if ((index < 0) || (index >= length_))
	{
		throw IndexOutOfRangeException();
	}
	return ourString_[index];
}

//�������� ������������
String & String::operator = (const String &otherString)
{
	//������, ���� �������� ������ ��� ����� ������, ������� ���������� ���������
	if (this == &otherString)
	{
		return *this;
	}
	//������, ���� �������� ������ �� ����� ������, ������� ���������� ���������, ��� ���� �������� ������ �� �������� �������
	if ((this != & otherString) && (this->ourString_ != nullptr))
	{
		delete[] this->ourString_;
	}
	
	this->length_ = strlen(otherString.ourString_);
	this->ourString_ = new char[this->length_ + 1];

	//����������� ������� �������� �������� ������ ������ ��������
	for (int i = 0; i < this->length_; i++)
	{
		this->ourString_[i] = otherString.ourString_[i];
	}
	this->ourString_[this->length_] = '\0';

	return *this;
}

//�������� ��������� ����� (����� �� ���)
bool const String::operator == (const String & otherString) const
{
	//��������� ��������
	if (this->length_ != otherString.length_)
	{
		return false;
	}
	//������������ ���������
	for (int i = 0; i < this->length_; i++)
	{
		if (this->ourString_[i] != otherString.ourString_[i])
		{
			return false;
		}
	}
	return true;
}

//��������� ������ � ����� ������ � ����������� � ������ (������������ � ������� ������ LCS)
void String::pushBack(const char &newElement)
{
	//�������� ��������� ������ � ������ ���� ���� ��������� ��������
	String temporaryString(this->length_);
	for (int i = 0; i < this->length_; i++)
	{
		temporaryString.ourString_[i] = this->ourString_[i];
	}
	delete[] this->ourString_;

	//���������� ����� �������� ������ �� 1 (����� ��� ������ ��������)
	this->length_ = temporaryString.length_ + 1;
	this->ourString_ = new char[this->length_ + 1];

	//������ ������ �� ��������� ������ � ��������, ������ ������ ��������
	for (int i = 0; i < temporaryString.length_; i++)
	{
		this->ourString_[i] = temporaryString.ourString_[i];
	}
	this->ourString_[this->length_ - 1] = newElement;
	//������ '\0' - ������� ����� ������
	this->ourString_[this->length_] = '\0';

}

//������������ �������� ������� � �������� ������� (������������ � ������� ������ LCS)
void String::reverse()
{
	//�������� ��������� ������ � ������ ���� ���� ��������� ��������
	String temporaryString;
	for (int i = this->length_-1; i >= 0; i--)
	{
		temporaryString.pushBack(this->ourString_[i]);
	}

	//������ ������ �� ��������� ������ � �������� � �������� �������
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



//������������� �������: �������� ������ ������
std::ostream & operator<< (std::ostream & out, const String & string)
{
	for (int i = 0; i < string.length_; i++)
	{
		out << string.ourString_[i];
	}
	return out;
}

//������������� �������: �������� ����� ������
std::istream & operator >> (std::istream & in, String & string)
{
	//���������� ��� �������� ���������� �������
	char symbol;
	//������ �� ����� �� ������� ����� ������
	while (!in.eof())
	{
		//������ �� ����� �������
		in.get(symbol);

		if (in.eof())
		{
			return in;
		}

		//�������� ��������� ������ � ������ ���� ���� ��������� ��������, � ����� ������ ��������
		char* tempString = new char[string.length_ + 1];

		for (int i = 0; i < string.length_; i++)
		{
			tempString[i] = string.ourString_[i];
		}
		tempString[string.length_] = symbol;
		//�������� �������� ������
		delete[] string.ourString_;

		//���������� ������� �������� ������
		string.length_++;
		//������ ������ �� ��������� ������ � ��������
		string.ourString_ = new char[string.length_ + 1];
		for (int i = 0; i < string.length_; i++)
		{
			string.ourString_[i] = tempString[i];
		}
		delete[] tempString;
		//������ '\0' - ������� ����� ������
		string.ourString_[string.length_] = '\0';
	};

}
