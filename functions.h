#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "matrix.h"
#include "string.h"
#include <fstream>
#include <algorithm>

extern std::ofstream out;

//�������, ������� ������� ����� LCS, ���������� LCS
String LCS(String & str1, String & str2);
//�������, ������� ������� ������� � ����������� ����
void outputMatrix(String str1, String str2, Matrix<int> matrix);

#endif