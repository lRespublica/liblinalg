#include "liblinalg/matrix.h"

namespace linalg {
    Matrix::Matrix()
    {init(0, 0);}

    Matrix::Matrix(const uint32_t rows)
    {init(rows, 1);}

    Matrix::Matrix(const uint32_t rows, const uint32_t columns)
    {init(rows, columns);}

    void Matrix::init(const uint32_t rows, const uint32_t columns)
    {
        m_rows = rows;
        m_columns = columns;

        m_empty = (m_rows * m_columns) == 0;

        m_ptr = new double[m_rows * m_columns];
    }

    uint32_t Matrix::rows() const
    {
        return m_rows;
    }

    uint32_t Matrix::columns() const
    {
        return m_columns;
    }

    void Matrix::reshape(uint32_t rows, uint32_t columns)
    {
        if(rows * columns != m_rows * m_columns)
            throw std::out_of_range("Matrix: Wrong shape");

        m_rows = rows;
        m_columns = columns;
    }

    double& Matrix::operator()(const uint32_t x, const uint32_t y)
    {
        if(x > m_rows || y > m_columns)
            throw std::out_of_range("Matrix: Out of bounds");

        return m_ptr[y*m_rows + x];
    }

    const double& Matrix::operator()(const uint32_t x, const uint32_t y) const
    {
        if(x > m_rows || y > m_columns)
            throw std::out_of_range("Matrix: Out of bounds");

        return m_ptr[y*m_rows + x];
    }

    bool Matrix::empty() const
    {
        return m_empty;
    }
}
