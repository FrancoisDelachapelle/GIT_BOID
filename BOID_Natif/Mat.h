#pragma once
#include <SFML/System/Vector2.hpp>

class Mat
{
    public :
        Mat();
    Mat(const int& _sizeX, const int& _sizeY);
    Mat(const int& _size);
    Mat(const Mat& _mat);
    Mat(const sf::Vector2f& _size); //vec2
    ~Mat();

    public :
        float** matriceArray;
    int row;
    int column;


    void InitMat();
    void InitMat(const Mat& _mat);
    void InitTranslationMatrix();
    float GetLastValueFromRow(const int& _column)const;
    void InsertValue(const int& _row, const int& _column,const float& _value);
    void DebugMat();


private:

    inline float MulResult( float** _first, float** _second,
        const int& _currentRow, const int& _currentCol, const int& _sizeRow)const
    {
        if (_sizeRow < 1)return 0;
        float _value = 0;
		
        for (int j = 0; j < _sizeRow; j++)
        {
            _value += _first[_currentRow][j] * _second[j][_currentCol];
        }
		
        return _value;
    }

public:
    Mat operator*(const Mat& _other)const
    {
        if (column != _other.row)return *this;
        Mat _mat(row, _other.column);
        int _sizeCol = _mat.column, _sizeRow = _mat.row;
        for (int i = 0; i < _sizeRow; i++)
        {
            for (int j = 0; j < _sizeCol; j++)
            {
                _mat[i][j] = MulResult(matriceArray, _other.matriceArray,i,j, _other.row);
            }
        }
        return _mat;
    }

    Mat operator+(const Mat& _other)const
    {
        if (column != _other.column || row != _other.row)return *this;
        Mat _mat(row, column);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                _mat[i][j] = matriceArray[i][j] + _other[j][i];
            }
        }
        return _mat;
    }
    Mat operator-(const Mat& _other)const
    {
        if (column != _other.column || row != _other.row)return *this;
        Mat _mat(row, column);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                _mat[i][j] = matriceArray[i][j] - _other[j][i];
            }
        }
        return _mat;
    }
    Mat operator =(const Mat& _other)const
    {
        Mat _mat(_other);
        return _mat;
    }
    float* operator[](int _index)const
    {
        return matriceArray[_index];
    }
    
};
