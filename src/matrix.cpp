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

    Matrix& Matrix::operator=(const Matrix& mat)
    {
        this->~Matrix();
        new (this) Matrix(mat);
        return *this;
    }

    Matrix::Matrix(Matrix&& mat) noexcept
    {
        m_ptr = std::exchange(mat.m_ptr, nullptr);
        m_columns = std::exchange(mat.m_columns, 0);
        m_rows = std::exchange(mat.m_rows, 0);
        m_size = std::exchange(mat.m_size, 0);
        m_empty = std::exchange(mat.m_empty, true);
    }

    Matrix& Matrix::operator=(Matrix&& mat) noexcept
    {
       this->~Matrix();
       new (this) Matrix(std::move(mat));
       return *this;
    }

    Matrix::Matrix(std::initializer_list<double> input) : Matrix ({static_cast<std::vector<double>>(input)})
    {}

    Matrix::Matrix(std::initializer_list<std::vector<double>> input)
    {
        if(input.size() == 0)
        {
            init(0, 0);
            return;
        }

        auto rows = input.size();
        auto columns = input.begin()->size();

        for (auto row : input)
        {
            if(row.size() != columns)
                throw std::out_of_range("Matrix: Given array is not matrix");
        }

        init(rows, columns);

        int rowCount = 0;
        for(auto row : input)
        {
            int colCount = 0;

            for(auto elem : row)
            {
                at(rowCount, colCount) = elem;

                colCount++;
            }
            rowCount++;
        }
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

    uint64_t Matrix::size() const
    {
        return m_size;
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

    double& Matrix::at(const uint32_t x, const uint32_t y)
    {
        if(x >= m_rows || y >= m_columns)
            throw std::out_of_range("Matrix: Out of bounds");

        return m_ptr[y*m_rows + x];
    }

    const double& Matrix::at(const uint32_t x, const uint32_t y) const
    {
        if(x >= m_rows || y >= m_columns)
            throw std::out_of_range("Matrix: Out of bounds");

        return m_ptr[y*m_rows + x];
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

    double Matrix::norm() const
    {
        double res = 0;
        for(int i = 0; i < m_size; i++)
            res += std::pow(m_ptr[i], 2);

        return std::sqrt(res);
    }

    double Matrix::trace() const
    {
        if(m_rows != m_columns)
        {
            throw std::invalid_argument("Matrix: Cannot calculate trace from non-square matrix");
        }

        double res = 0;
        for(int i = 0; i < m_rows; i++)
            res += this->at(i, i);

        return res;
    }

    double Matrix::det() const
    {
        if(m_rows != m_columns)
        {
            throw std::invalid_argument("Matrix: Cannot calculate determinant from non-square matrix");
        }

        if(m_size == 1)
            return m_ptr[0];

        double res = 0;
        for(int i = 0; i < m_columns; i++)
        {
            res += std::pow(-1, i + 2) * this->at(i, 0) * minor(i, 0).det();
        }

        return res;
    }

    Matrix Matrix::minor(double x, double y) const
    {
        Matrix retMat(m_rows - 1, m_columns - 1);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_columns; j++)
            {
                if(i == x || j == y)
                    continue;

                auto row = i;
                auto col = j;

                if(i > x)
                    row--;
                if(j > y)
                    col--;

                retMat.at(row, col) = this->at(i, j);
            }
        }

        return retMat;
    }

    Matrix& Matrix::operator+=(const Matrix& mat)
    {
        if(this->rows() != mat.rows() || this->columns() != mat.columns())
            throw std::out_of_range("Matrix: Different size of matrices");

        if(this->empty())
            throw std::invalid_argument("Matrix: Trying to sum empty matrices");

        for(int i = 0; i < m_size; i++)
            m_ptr[i] +=  mat.data()[i];

        return *this;
    }

    Matrix Matrix::operator+(const Matrix& mat) const
    {
        auto retMat = Matrix(*this);
        retMat += mat;
        return retMat;
    }

    Matrix& Matrix::operator-=(const Matrix& mat)
    {
        if(this->rows() != mat.rows() || this->columns() != mat.columns())
            throw std::out_of_range("Matrix: Different size of matrices");

        if(this->empty())
            throw std::invalid_argument("Matrix: Trying to sum empty matrices");

        for(int i = 0; i < m_size; i++)
            m_ptr[i] -=  mat.data()[i];

        return *this;
    }

    Matrix Matrix::operator-(const Matrix& mat) const
    {
        auto retMat = Matrix(*this);
        retMat -= mat;
        return retMat;
    }

    Matrix& Matrix::operator*=(double val)
    {
        if(this->empty())
            throw std::invalid_argument("Matrix: Trying to multiply a number by an empty matrix");

        for(int i = 0; i < m_size; i++)
            m_ptr[i] *= val;

        return *this;
    }

    Matrix Matrix::operator*(double val) const
    {
        auto retMat = Matrix(*this);
        retMat *= val;
        return retMat;
    }

    Matrix operator*(double val, const Matrix& mat)
    {
        auto retMat = Matrix(mat);
        retMat *= val;
        return retMat;
    }

    Matrix& Matrix::operator*=(const Matrix& mat)
    {
        if(this->columns() != mat.rows())
        {
            throw std::out_of_range("Matrix: Matrices are incompatible for multiplication");
        }

        Matrix resMat(this->rows(), mat.columns());

        auto sameDim = mat.rows(); // = this->columns()

        for(int i = 0; i < resMat.rows(); i++)
        {
            for(int j = 0; j < resMat.columns(); j++)
            {
                double newElem = 0;
                for(int k = 0; k < sameDim; k++)
                {
                    newElem += this->at(i, k) * mat.at(k, j);
                }
                resMat.at(i, j) = newElem;
            }
        }


        this->~Matrix();
        new (this) Matrix(std::move(resMat));
        return *this;
    }

    Matrix Matrix::operator*(const Matrix& mat) const
    {
        auto retMat = Matrix(*this);
        retMat *= mat;
        return retMat;
    }

    bool Matrix::operator== (const Matrix& mat) const
    {
        if(m_size != mat.size())
            return false;

        if(m_empty == true && mat.empty() == true)
            return true;

        auto data = mat.data();

        for(int i = 0; i < m_size; i++)
        {
            if (compareDouble(m_ptr[i], data[i]) != true)
            {
                return false;
            }
        }

        return true;
    }

    bool Matrix::operator!= (const Matrix& mat) const
    {
        return !(*this == mat);
    }

    bool compareDouble(double val1, double val2)
    {
        const auto relative_difference_factor = 0.0001;
        const auto greater_magnitude = std::max(std::abs(val1),std::abs(val2));

        if ( std::abs(val1-val2) < relative_difference_factor * greater_magnitude )
            return true;
        else
            return false;
    }

    std::vector<std::string> Matrix::getStrings() const
    {
        std::vector<std::string> strings;

        for(int i = 0; i < m_size; i++)
        {
            auto str = std::to_string(m_ptr[i]);

            str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
            str.erase ( str.find_last_not_of('.') + 1, std::string::npos );

            strings.push_back(str);
        }

        return strings;
    }

    std::ostream& operator<<(std::ostream& os, linalg::Matrix const& mat)
    {
        auto strings = std::move(mat.getStrings());
        uint32_t maxLen = 0;

        for(auto str : strings)
        {
            auto tmp = str.length();

            if (tmp > maxLen)
                maxLen = tmp;
        }

        auto oldWidth = os.width();

        for(auto i = 0; i < mat.m_rows; i++)
        {
            os << "|";

            for(auto j = 0; j < mat.m_columns; j++)
            {
                os.width(maxLen);
                os << strings[j*mat.m_rows + i];
                os << " ";
            }

            os.width(oldWidth);
            os << "|\n";
        }

        return os;
    }

    bool Matrix::empty() const
    {
        return m_empty;
    }

    const double* Matrix::data() const
    {
        return m_ptr;
    }

    double* Matrix::unsafeData()
    {
        return m_ptr;
    }
}
