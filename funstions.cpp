#include "pch.h"
#include "functions.h"

//����������� ������ �������, ������� ����� �������� � ����
const int MAX_SIZE_OF_MATRIX_FOR_OUTPUT = 300; 

//�������, ������� ������� ����� LCS, ���������� LCS
String LCS(String & str1, String & str2)
{
	//����� ����� LCS
	int height = str2.getLength();
	int width = str1.getLength();

	//�������� ������� ������������ �������
	Matrix<int> matrix(height, width);
	//��������� ��� ������� 0
	matrix.fillWholeMatrix(0);

	//����������� ������� �� ��������������� ������� (��� ������ �����)
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

	//�������� �� ��, ���� �� ����� ��������������������� 
	if ((matrix[height - 1])[width - 1] == 0)
	{
		return "����� ��������������������� �� �������!";
	}
	//������ ����� LCS
	else
	{
		out << "����� ���������� ����� ������������������:\n";
		out << (matrix[height - 1])[width - 1] << "\n\n";
	}

	//������ ������� � ���� (� ������, ���� ������� �� ��������� �������� ������) 
	if (height * width < MAX_SIZE_OF_MATRIX_FOR_OUTPUT)
	{
		outputMatrix(str1, str2, matrix);
	}
	else
	{
		out << "������� ������� ������, ����� � �������!\n\n";
	}

	//�������������� LCS
	String lcs;
	int i = str2.getLength();
	int j = str1.getLength();

	//������ �������, ������� � ���������� ��������, �� ��������� �������
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
    //LCS ���������� �����������, ��� ��� ����� ������� �� ������� ��� ��������, ������� � ���������� ��������
	lcs.reverse();

	//������ ������ � ������� LCS
	out << "�����: \n";
	return lcs;
}

//�������, ������� ������� ������� � ����������� ����
void outputMatrix(String str1, String str2, Matrix<int> matrix)
{
	out << "�������:\n";

	str1.newLineSymbolToSpace();
	str2.newLineSymbolToSpace();
	//��������� �� ������ ������ 3 �������, ����� �������� � ������� 1-� ������������������ � ������� ����
	out << "   ";
	for (int i = 0; i < str1.getLength(); i++)
	{
		out << " " << str1.getOurString()[i];
	}
	out << "\n";

	//����� ������ 1-� ������������������ ���������� �������, ��� ���� ����� ������ ������� ������� ���������� 
	//��������������� ������� 2-� ������������������ (������� ���)
	for (int i = 0; i < matrix.getRows(); i++)
	{
		//������ ��� ���� ����� �������, ����� 0-� (�������� ������� 2-� ������������������)
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
			//������ ��� 0-� ������ ������� (��������� �� ���������, �.�. �� �������� ������� 2-� ������������������)
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
