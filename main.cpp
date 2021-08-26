#include "pch.h"
#include <iostream>
#include <fstream>
#include "string.h"
#include "functions.h"
#include "exceptions.h"

//функция, которая записывает номер пары последовательностей, сами последовательности, вызывает функцию LCS
void serchOfLCS(String str1, String str2);
std::ofstream out("output.txt");

int main()
{
	setlocale(LC_ALL, "Russian");
	std::ifstream file1 ("string1.txt");
	std::ifstream file2 ("string2.txt");
	try
	{
		if (!file1)
		{
			throw FileIsNotOpenException();
		}
		if (!file2)
		{
			throw FileIsNotOpenException();
		}
		std::cout << "Файлы открыты!\n";

	}
	//проверка на то, которыты файлы или нет
	catch (FileIsNotOpenException & error)
	{
		std::cout << error.getMessage();
		return 0;
	}

	//чтение из файлов
	while (!(file1.eof()) || !(file2.eof()))
	{
		try 
		{
			String string1;
			String string2;
			file1 >> string1;
			file2 >> string2;

			serchOfLCS(string1, string2);
		}
		//проверка на то, не выходит ли индекс за пределы допустимого диапазона
		catch (IndexOutOfRangeException & error)
		{
			std::cout << error.getMessage();
			return 0;
		}
	}

	file1.close();
	file2.close();
	out.close();

	return 0;
}

//функция, которая записывает номер пары последовательностей, сами последовательности, вызывает функцию LCS
void serchOfLCS(String str1, String str2)
{
	out << "-----СТРОКА НОМЕР 1-----\n";
	out << str1 <<"\n";

	out << "-----СТРОКА НОМЕР 2-----\n";
	out << str2<<"\n";
	out << LCS(str1, str2) << "\n\n";
}
