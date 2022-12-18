#include <iostream>


class Matrix

{

public:
    Matrix()
    {
        rows = 0;
        cols = 0;
        M = nullptr;
    }

    Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;

        M = new int*[rows];

        for (int i = 0; i < rows; i++)
            M[i] = new int[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                M[i][j] = 0;
    }

    int getRows()
    {
        return rows;
    }

    int getColumns()
    {
        return cols;
    }

    int getElement(int i, int j) 
    {
        if (i <= rows && j <= cols)
        {
            return M[i][j];
        }
        else 
        {
            throw std::out_of_range("Element is out of range!");
        }
    }

    void setElement(int i, int j, int value)
    {
        if (i <= rows && j <= cols)
        {
            M[i][j] = value;
        }
        else 
        {
            throw std::out_of_range("Element is out of range!");
        }
    }

    void operator*=(int num)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                M[i][j] *= num;
    }

    Matrix operator+(const Matrix& _M)
    {
        Matrix newMatrix(rows, cols);
        if (rows != _M.rows || cols != _M.cols)
        {
            throw std::out_of_range("Sizes are different!");

        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                newMatrix.M[i][j] = M[i][j] + _M.M[i][j];
        return newMatrix;
    }

    bool operator==(const Matrix& _M) const 
    {
        if (rows != _M.rows || cols != _M.cols)
        {
            throw std::out_of_range("Sizes are different!");

        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (M[i][j] != _M.M[i][j])
                {
                    return false;
                }
                    
        return true;
    }

    friend std::ostream& operator<< (std::ostream& out, const Matrix& mat);


    ~Matrix()
    {
        if (cols > 0)
        {
            for (int i = 0; i < rows; i++)
                delete[] M[i];
        }

        if (rows > 0)
            delete[] M;
    }
    

private:
    int** M = nullptr;
    int rows;
    int cols;
};

inline std::ostream& operator<< (std::ostream& out, const Matrix& matrix)
{
    for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.cols; j++)
            {
                out << matrix.M[i][j];
                out << "\t";
            }
                
            out << "\n";
        };
    return out;
}

