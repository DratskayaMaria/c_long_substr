#include "pch.h"
#include "functions.h"

//макимальный размер матрицы, которую можно записать в файл
const int MAX_SIZE_OF_MATRIX_FOR_OUTPUT = 300; 

//функция, которая выводит длину LCS, возвращает LCS
String LCS(String & str1, String & str2)
{
	//поиск длины LCS
	int height = str2.getLength();
	int width = str1.getLength();

	//создаётся матрица необходимого размера
	Matrix<int> matrix(height, width);
	//заполняем всю матрицу 0
	matrix.fillWholeMatrix(0);

	//заполняется матрица по соотвествующему правилу (для поиска длины)
	for (int i = 1; i < height; i++)
	{
		for (int j = 1; j < width; j++)
		{
			if ((str2[i - 1] == str1[j - 1])&&(str2[i-1] != '\n')&&(str1[j - 1] != '\n'))
			{
				(matrix[i])[j] = (matrix[i - 1])[j - 1] + 1;
			}
			else
			{
				(matrix[i])[j] = std::max((matrix[i - 1])[j], (matrix[i])[j - 1]);
			}
		}
	}

	//проверка на то, есть ли общая подпоследовательность 
	if ((matrix[height - 1])[width - 1] == 0)
	{
		return "Общая подпоследовательность не найдена!";
	}
	//запись длины LCS
	else
	{
		out << "Длина наибольшей общей последовательности:\n";
		out << (matrix[height - 1])[width - 1] << "\n\n";
	}

	//запись матрицы в файл (в случае, если матрица не превышает заданный размер) 
	if (height * width < MAX_SIZE_OF_MATRIX_FOR_OUTPUT)
	{
		outputMatrix(str1, str2, matrix);
	}
	else
	{
		out << "Матрица слишком велика, чтобы её вывести!\n\n";
	}

	//восстановление LCS
	String lcs;
	int i = str2.getLength();
	int j = str1.getLength();

	//проход матрицы, начиная с последнего элемента, по заданному правилу
	while (i != 0 && j != 0)
	{
		if ((str2[i - 1] == str1[j - 1]))
		{
			lcs.pushBack(str2[i - 1]);
			--i;
			--j;
		}
		else
		{
			if ((matrix[i])[j - 1] > (matrix[i - 1])[j])
			{
				--j;
			}
			else
			{
				--i;
			}
		}
	}
    //LCS необходимо перевернуть, так как после прохода по матрицы она записана, начиная с последнего элемента
	lcs.reverse();

	//запись ответа и возврат LCS
	out << "Ответ: \n";
	return lcs;
}

//функция, которая выводит матрицу в необходимом виде
void outputMatrix(String str1, String str2, Matrix<int> matrix)
{
	out << "Матрица:\n";

	str1.newLineSymbolToSpace();
	str2.newLineSymbolToSpace();
	//отступаем от начала строки 3 пробела, чтобы записать в таблицу 1-ю последовательность в удобном виде
	out << "   ";
	for (int i = 0; i < str1.getLength(); i++)
	{
		out << " " << str1.getOurString()[i];
	}
	out << "\n";

	//после записи 1-й последовательности записываем матрицу, при этом перед каждой строкой матрицы записываем 
	//соответствующий элемент 2-й последовательности (удобный вид)
	for (int i = 0; i < matrix.getRows(); i++)
	{
		//запись для всех строк матрицы, кроме 0-й (содержат элемент 2-й последовательности)
		if (i != 0)
		{
			out << str2.getOurString()[i - 1] << " ";
			for (int j = 0; j < matrix.getColumns(); j++)
			{
				out << (matrix[i])[j] << " ";
			}
			out << "\n";
		}
		else
		{
			//запись для 0-й строки матрицы (оличается от остальных, т.к. не содержит элемент 2-й последовательности)
			out << "  ";
			for (int j = 0; j < matrix.getColumns(); j++)
			{
				out << (matrix[i])[j] << " ";
			}
			out << "\n";
		}
	}
	out << "\n";
}
