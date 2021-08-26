#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include "exceptions.h"

template<typename T>
class Matrix
{
public:
	//конструктор без парметров (итог: пустая матрица, размер которой 0*0)
	Matrix();
	//конструктор, который в качестве параметра принимает количество строк и слобцов (итог: пустая строка указанного размера)
	Matrix(int newRows, int newColumns);
	//конструктор копирования
	Matrix(const Matrix & otherMatrix);
	//деструктор 
	~Matrix();

	//возвращает количество строк матрицы
	int getRows() const;
	//возвращает количество столбцов матрицы
	int getColumns() const;
	//возвращает указатель на матрицу
	T * getMatrix() const;

	//оператор индексирования: возвращает строку с указанным индексом
	T * operator [] (int rowIndex);
	//оператор присваивания 
	Matrix & operator = (const Matrix & otherMatrix);

	//заполняет всю матрицу указанным значением (используется в функции поиска LCS)
	void fillWholeMatrix(T value);

	//дружественная функция: оператор вывода матрицы
	template<typename T>
	friend std::ostream & operator << (std::ostream & cout, const Matrix<T> & matrix);
	//дружественная функция: оператор ввода матрицы
	template<typename T>
	friend std::istream & operator >> (std::istream & cin, Matrix<T> & matrix);

private:
	//указатель на матрицу 
	T ** ourMatrix_;
	//количество строк матрицы
	int rows_;
	//количество столбцов матрицы
	int columns_;
};

//конструктор без парметров (итог: пустая матрица, размер которой 0*0)
template<typename T>
Matrix<T>::Matrix():
	rows_ (0),
	columns_ (0),
	ourMatrix_ (nullptr)
{}

//конструктор, который в качестве параметра принимает количество строк и слобцов (итог: пустая строка указанного размера)
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

//конструктор копирования
template<typename T>
Matrix<T>::Matrix(const Matrix & otherMatrix)
{
	//случай, если исходная матрица уже равна матрице, которую необходимо скопировать
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

//деструктор 
template<typename T>
Matrix<T>::~Matrix()
{
	delete[] ourMatrix_;
	rows_ = 0;
	columns_ = 0;
}



//возвращает количество строк матрицы
template<typename T>
int Matrix<T>::getRows() const
{
	return rows_;
}

//возвращает количество столбцов матрицы
template<typename T>
int Matrix<T>::getColumns() const
{
	return columns_;
}

//возвращает указатель на матрицу
template<typename T>
T * Matrix<T>::getMatrix() const
{
	return ourMatrix_;
}



//оператор индексирования: возвращает строку с указанным индексом
template<typename T>
T * Matrix<T>::operator[] (int rowIndex)
{
	//проверка на то, что индекс больше или равен нулю, при этом меньше длины строки
	if ((rowIndex < 0) || (rowIndex >= rows_))
	{
		throw IndexOutOfRangeException();
	}
	return ourMatrix_[rowIndex];
}

//оператор присваивания
template<typename T>
Matrix<T> & Matrix<T>::operator = (const Matrix<T> & otherMatrix)
{
	//случай, если исходная матрица уже равна матрице, которую необходимо присвоить
	if (this == &otherMatrix)
	{
		return *this;
	}
	//если хотя бы один размер исходной матрице не соотвествует размеру матрицы, которую необходимо присвоить
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

	//присваиваем каждому элементу исходной матрицы нужное значение
	for (int i = 0; i < this->rows_; i++)
	{
		for (int j = 0; j < this->columns_; i++)
		{
			this->ourMatrix_[i][j] = otherMatrix.ourMatrix_[i][j];
		}
	}
	return *this;
}



//заполняет всю матрицу указанным значением (используется в функции поиска LCS)
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



//дружественная функция: оператор вывода матрицы
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

//дружественная функция: оператор ввода матрицы
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