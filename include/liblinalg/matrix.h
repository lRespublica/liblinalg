#pragma once

#include "liblinalg/export.h"
#include <cstdint>
#include <stdexcept>
#include <utility>

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

            ~Matrix();

            uint32_t rows() const;
            uint32_t columns() const;

            void clear();
            void reshape(const uint32_t rows, const uint32_t columns);

            double& operator()(const uint32_t x, const uint32_t y);
            const double& operator()(const uint32_t x, const uint32_t y) const;

            const double* data() const;

            bool empty() const;
        private:
            void init(const uint32_t rows, const uint32_t columns);

            double* m_ptr;
            uint32_t m_rows;
            uint32_t m_columns;

            uint64_t m_size;

            bool m_empty;
    };
}
