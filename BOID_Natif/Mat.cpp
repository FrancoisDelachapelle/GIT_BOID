#include "Mat.h"

#include <iostream>

using namespace std;
Mat::Mat()
{
    row = 4;
    column = 4;
    InitMat();
}

Mat::Mat(const int& _sizeX, const int& _sizeY)
{
    row = _sizeX;
    column = _sizeY;
    InitMat();
}

Mat::Mat(const sf::Vector2f& _size)
{
    row = static_cast<int>(_size.x);
    column = static_cast<int>(_size.y);
    InitMat();
}

Mat::Mat(const Mat& _mat)
{
    row = _mat.row;
    column = _mat.column;
    InitMat(_mat);

}

Mat::~Mat()
{
    for (int i = 0; i < row; i++)
    {
        delete[] matriceArray[i];
    }
    delete[] matriceArray;
}

void Mat::InitMat()
{
    matriceArray = new float* [row];
    for (int i = 0; i < row; i++)
    {
        matriceArray[i] = new float[column];
        for (int j = 0; j < column; j++)
        {
            matriceArray[i][j] = 0;		
        }
    }
}

void Mat::InitMat(const Mat& _mat)
{
    matriceArray = new float* [row];
    for (int i = 0; i < row; i++)
    {
        matriceArray[i] = new float[column];
        for (int j = 0; j < column; j++)
        {
            matriceArray[i][j] = _mat[i][j];
        }
    }
}

float Mat::GetLastValueFromRow(const int& _row)const
{
    return matriceArray[_row][column-1];
}

void Mat::InsertValue(const int& _row, const int& _column, const float& _value)
{
    if (_column > column || _column < 0 || _row > row || _row < 0)
        return;
    matriceArray[_row][_column] = _value;
}

void Mat::InitTranslationMatrix()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (i == j)
            {
                matriceArray[i][j] = 1;
            }
        }
    }
}

void Mat::DebugMat()
{
    cout << "init" << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            std::cout <<"| " << matriceArray[i][j]<< " | ";
        }
        std::cout << "" << std::endl;
    }
}
