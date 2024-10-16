#include "liblinalg/matrix.h"

namespace linalg {
    Matrix::Matrix(uint32_t rows, uint32_t columns)
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

    bool Matrix::empty()
    {
        return m_empty;
    }
}
