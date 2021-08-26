#pragma once
#ifndef STRING_H
#define STRING_H
#include<iostream>

class String
{
public:
	//����������� ��� ��������� (����: ������ ������, ����� ������� ����� 0)
	String(); 
	//�����������, ������� � �������� ��������� ��������� ������ ������ (����: ������ ������ ���������� �������)
	String(int newLength); 
	//�����������, ������� � �������� ��������� ��������� ��������� �� ������ �������� (����: ������ � ���������)
	String(const char * newString);
	//����������� �����������
	String(const String & otherString); 
	//���������� 
	~String(); 

	//���������� ����� ������
	int getLength() const; 
	//���������� ��������� �� ������ �������� ������
	char * getOurString() const; 

	//�������� ��������������: ���������� ������ � ��������� ��������
	char & operator [] (int index) const; 
	//�������� ������������ 
	String & operator = (const String & otherString); 
	//�������� ��������� ����� (����� �� ���)
	bool const operator == (const String & otherString) const;
	//��������� ������ � ����� ������ � ����������� � ������ (������������ � ������� ������ LCS)
	void pushBack(const char &newElement); 
	//������������ �������� ������� � �������� ������� (������������ � ������� ������ LCS)
	void reverse();
	//�������� ��� ������� �������� �� ����� ������ �� ������� (������������ ��� ����� �������� ������ LCS)
	void newLineSymbolToSpace();

	//������������� �������: �������� ������ ������
	friend std::ostream & operator << (std::ostream & out, const String & string); 
	//������������� �������: �������� ����� ������
	friend std::istream & operator >> (std::istream & in, String & string); 
	
private:
	//��������� �� ������ �������� ������
	char *ourString_; 
	//����� ������
	int length_; 
};

#endif