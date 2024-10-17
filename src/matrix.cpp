#include "liblinalg/matrix.h"

namespace linalg {
    Matrix::Matrix()
    {init(0, 0);}

    Matrix::~Matrix()
    {clear();}

    Matrix::Matrix(const uint32_t rows)
    {init(rows, 1);}

    Matrix::Matrix(const uint32_t rows, const uint32_t columns)
    {init(rows, columns);}

    Matrix::Matrix(const Matrix& mat)
    {
        init(mat.rows(), mat.columns());

        auto data = mat.data();

        for(int i = 0; i < m_size; i++)
            m_ptr[i] = data[i];
    }

    void Matrix::init(const uint32_t rows, const uint32_t columns)
    {
        m_rows = rows;
        m_columns = columns;
        m_size = rows*columns;

        m_empty = (m_size == 0);

        if (not m_empty)
            m_ptr = new double[m_size];
        else
            m_ptr = nullptr;
    }

    uint32_t Matrix::rows() const
    {
        return m_rows;
    }

    uint32_t Matrix::columns() const
    {
        return m_columns;
    }

    void Matrix::clear()
    {
        m_columns = 0;
        m_rows = 0;
        m_columns = 0;
        m_empty = true;

        if(m_ptr != nullptr)
        {
            delete [] m_ptr;
            m_ptr = nullptr;
        }
    }

    void Matrix::reshape(uint32_t rows, uint32_t columns)
    {
        if(rows * columns != m_size)
            throw std::out_of_range("Matrix: Wrong shape");

        m_rows = rows;
        m_columns = columns;
    }

    double& Matrix::operator()(const uint32_t x, const uint32_t y)
    {
        if(x >= m_rows || y >= m_columns)
            throw std::out_of_range("Matrix: Out of bounds");

        return m_ptr[y*m_rows + x];
    }

    const double& Matrix::operator()(const uint32_t x, const uint32_t y) const
    {
        if(x >= m_rows || y >= m_columns)
            throw std::out_of_range("Matrix: Out of bounds");

        return m_ptr[y*m_rows + x];
    }

    bool Matrix::empty() const
    {
        return m_empty;
    }

    const double* Matrix::data() const
    {
        return m_ptr;
    }
}
