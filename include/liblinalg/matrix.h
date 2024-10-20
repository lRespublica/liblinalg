#pragma once

#include "liblinalg/export.h"
#include <cstdint>
#include <ostream>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <string>
#include <vector>
#include <cmath>

namespace linalg {

    class LIBLINALG_EXPORT Matrix
    {
        public:
            Matrix();
            Matrix(const uint32_t rows);
            Matrix(const uint32_t rows, const uint32_t columns);

            Matrix(const Matrix& mat);
            Matrix& operator=(const Matrix& mat);

            Matrix(Matrix&& mat) noexcept;
            Matrix& operator=(Matrix&& mat) noexcept;

            Matrix(std::initializer_list<double> input);
            Matrix(std::initializer_list<std::vector<double>> input);

            ~Matrix();

            uint32_t rows() const;
            uint32_t columns() const;
            uint64_t size() const;

            void clear();
            void reshape(const uint32_t rows, const uint32_t columns);

            double& at(const uint32_t x, const uint32_t y);
            const double& at(const uint32_t x, const uint32_t y) const;

            double& operator()(const uint32_t x, const uint32_t y);
            const double& operator()(const uint32_t x, const uint32_t y) const;

            double norm() const;
            double trace() const;
            double det() const;

            Matrix minor(double x, double y) const;

            Matrix& operator+=(const Matrix& mat);
            Matrix operator+(const Matrix& mat) const;

            Matrix& operator-=(const Matrix& mat);
            Matrix operator-(const Matrix& mat) const;

            Matrix& operator*=(double val);
            Matrix operator*(double val) const;

            Matrix& operator*=(const Matrix& mat);
            Matrix operator*(const Matrix& mat) const;

            bool operator== (const Matrix& mat) const;
            bool operator!= (const Matrix& mat) const;

            const double* data() const;
            double* unsafeData();

            bool empty() const;

            LIBLINALG_EXPORT friend std::ostream& operator<<(std::ostream& os, linalg::Matrix const& mat);

        private:
            void init(const uint32_t rows, const uint32_t columns);

            std::vector<std::string> getStrings() const;

            double* m_ptr;
            uint32_t m_rows;
            uint32_t m_columns;

            uint64_t m_size;

            bool m_empty;
    };

    bool compareDouble(double val1, double val2);

    LIBLINALG_EXPORT Matrix operator*(double val, const Matrix& mat);

    LIBLINALG_EXPORT Matrix concatenate(const Matrix& mat1, const Matrix& mat2);

    LIBLINALG_EXPORT Matrix transpose(const Matrix& mat);

    LIBLINALG_EXPORT Matrix invert(const Matrix& mat);
}
