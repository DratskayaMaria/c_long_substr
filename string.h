#pragma once
#ifndef STRING_H
#define STRING_H
#include<iostream>

class String
{
public:
	//конструктор без парметров (итог: пустая строка, длина которой равна 0)
	String(); 
	//конструктор, который в качестве параметра принимает размер строки (итог: пустая строка указанного размера)
	String(int newLength); 
	//конструктор, который в качестве параметра принимает указатель на массив символов (итог: строка с символами)
	String(const char * newString);
	//конструктор копирования
	String(const String & otherString); 
	//деструктор 
	~String(); 

	//возвращает длину строки
	int getLength() const; 
	//возвращает указатель на массив символов строки
	char * getOurString() const; 

	//оператор индексирования: возвращает символ с указанным индексом
	char & operator [] (int index) const; 
	//оператор присваивания 
	String & operator = (const String & otherString); 
	//оператор сравнения строк (равны ли они)
	bool const operator == (const String & otherString) const;
	//добавляет символ в конец строки и увеличивает её размер (используется в функции поиска LCS)
	void pushBack(const char &newElement); 
	//переставляет элементы массива в обратном порядке (используется в функции поиска LCS)
	void reverse();
	//заменяет все символы перехода на новую строку на пробелы (используется для более удобного поиска LCS)
	void newLineSymbolToSpace();

	//дружественная функция: оператор вывода строки
	friend std::ostream & operator << (std::ostream & out, const String & string); 
	//дружественная функция: оператор ввода строки
	friend std::istream & operator >> (std::istream & in, String & string); 
	
private:
	//указатель на массив символов строки
	char *ourString_; 
	//длина строки
	int length_; 
};

#endif