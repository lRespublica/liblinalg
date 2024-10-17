#include "liblinalg/matrix.h"

namespace linalg {
    Matrix::Matrix()
    {init(0, 0);}

    Matrix::Matrix(uint32_t rows)
    {init(rows, 1);}

    Matrix::Matrix(uint32_t rows, uint32_t columns)
    {init(rows, columns);}

    void Matrix::init(uint32_t rows, uint32_t columns)
    {
        m_rows = rows;
        m_columns = columns;

        m_empty = (m_rows * m_columns) == 0;

        m_ptr = new double[m_rows * m_columns];
    }

    uint32_t Matrix::rows()
    {
        return m_rows;
    }

    uint32_t Matrix::columns()
    {
        return m_columns;
    }

    void Matrix::reshape(uint32_t rows, uint32_t columns)
    {
        if(rows * columns != m_rows * m_columns)
            throw std::out_of_range("Wrong shape");

        m_rows = rows;
        m_columns = columns;
    }

    bool Matrix::empty()
    {
        return m_empty;
    }
}
