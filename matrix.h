#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include "exceptions.h"

template<typename T>
class Matrix
{
public:
	//����������� ��� ��������� (����: ������ �������, ������ ������� 0*0)
	Matrix();
	//�����������, ������� � �������� ��������� ��������� ���������� ����� � ������� (����: ������ ������ ���������� �������)
	Matrix(int newRows, int newColumns);
	//����������� �����������
	Matrix(const Matrix & otherMatrix);
	//���������� 
	~Matrix();

	//���������� ���������� ����� �������
	int getRows() const;
	//���������� ���������� �������� �������
	int getColumns() const;
	//���������� ��������� �� �������
	T * getMatrix() const;

	//�������� ��������������: ���������� ������ � ��������� ��������
	T * operator [] (int rowIndex);
	//�������� ������������ 
	Matrix & operator = (const Matrix & otherMatrix);

	//��������� ��� ������� ��������� ��������� (������������ � ������� ������ LCS)
	void fillWholeMatrix(T value);

	//������������� �������: �������� ������ �������
	template<typename T>
	friend std::ostream & operator << (std::ostream & cout, const Matrix<T> & matrix);
	//������������� �������: �������� ����� �������
	template<typename T>
	friend std::istream & operator >> (std::istream & cin, Matrix<T> & matrix);

private:
	//��������� �� ������� 
	T ** ourMatrix_;
	//���������� ����� �������
	int rows_;
	//���������� �������� �������
	int columns_;
};

//����������� ��� ��������� (����: ������ �������, ������ ������� 0*0)
template<typename T>
Matrix<T>::Matrix():
	rows_ (0),
	columns_ (0),
	ourMatrix_ (nullptr)
{}

//�����������, ������� � �������� ��������� ��������� ���������� ����� � ������� (����: ������ ������ ���������� �������)
template<typename T>
Matrix<T>::Matrix(int newRows, int newColumns)
{
	rows_ = newRows;
	columns_ = newColumns;
	ourMatrix_ = new T *[rows_];
	for (int i = 0; i < rows_; i++)
	{
		ourMatrix_[i] = new T[columns_];
	}
}

//����������� �����������
template<typename T>
Matrix<T>::Matrix(const Matrix & otherMatrix)
{
	//������, ���� �������� ������� ��� ����� �������, ������� ���������� �����������
	if (this != &otherMatrix)
	{
		rows_ = otherMatrix.rows_;
		columns_ = otherMatrix.columns_;
		ourMatrix_ = new T *[rows_];
		for (int i = 0; i < rows_; i++)
		{
			ourMatrix_[i] = new T[columns_];
			for (int j = 0; j < columns_; j++)
			{
				ourMatrix_[i][j] = otherMatrix.ourMatrix_[i][j];
			}
		}
	}

}

//���������� 
template<typename T>
Matrix<T>::~Matrix()
{
	delete[] ourMatrix_;
	rows_ = 0;
	columns_ = 0;
}



//���������� ���������� ����� �������
template<typename T>
int Matrix<T>::getRows() const
{
	return rows_;
}

//���������� ���������� �������� �������
template<typename T>
int Matrix<T>::getColumns() const
{
	return columns_;
}

//���������� ��������� �� �������
template<typename T>
T * Matrix<T>::getMatrix() const
{
	return ourMatrix_;
}



//�������� ��������������: ���������� ������ � ��������� ��������
template<typename T>
T * Matrix<T>::operator[] (int rowIndex)
{
	//�������� �� ��, ��� ������ ������ ��� ����� ����, ��� ���� ������ ����� ������
	if ((rowIndex < 0) || (rowIndex >= rows_))
	{
		throw IndexOutOfRangeException();
	}
	return ourMatrix_[rowIndex];
}

//�������� ������������
template<typename T>
Matrix<T> & Matrix<T>::operator = (const Matrix<T> & otherMatrix)
{
	//������, ���� �������� ������� ��� ����� �������, ������� ���������� ���������
	if (this == &otherMatrix)
	{
		return *this;
	}
	//���� ���� �� ���� ������ �������� ������� �� ������������ ������� �������, ������� ���������� ���������
	if ((this->columns_ != otherMatrix.columns_) || (this->rows_ != otherMatrix.rows_))
	{
		delete[] this->ourMatrix_;
		this->columns_ = otherMatrix.columns_;
		this->rows_ = otherMatrix.rows_;

		ourMatrix_ = new T *[rows_];
		for (int i = 0; i < rows_; i++)
		{
			ourMatrix_[i] = new T[columns_];
		}
	}

	//����������� ������� �������� �������� ������� ������ ��������
	for (int i = 0; i < this->rows_; i++)
	{
		for (int j = 0; j < this->columns_; i++)
		{
			this->ourMatrix_[i][j] = otherMatrix.ourMatrix_[i][j];
		}
	}
	return *this;
}



//��������� ��� ������� ��������� ��������� (������������ � ������� ������ LCS)
template<typename T>
void Matrix<T>::fillWholeMatrix(T value)
{
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < columns_; j++)
		{
			ourMatrix_[i][j] = value;
		}
	}
}



//������������� �������: �������� ������ �������
template<typename T>
std::ostream & operator << (std::ostream & cout, const Matrix<T> & matrix)
{
	for (int i = 0; i < matrix.rows_; i++)
	{
		for (int j = 0; j < matrix.columns_; j++)
		{
			cout << " " << matrix.ourMatrix_[i][j];
		}
		cout << std::endl;
	}
	cout << std::endl;
	return cout;
}

//������������� �������: �������� ����� �������
template<typename T>
std::istream & operator >> (std::istream & cin, Matrix<T> & matrix)
{
	for (int i = 0; i < matrix.rows_; i++)
	{
		for (int j = 0; j < matrix.columns_; j++)
		{
			cin >> matrix.ourMatrix_[i][j];
		}
	}
	return cin;
}

#endif