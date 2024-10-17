#pragma once

#include "liblinalg/export.h"
#include <cstdint>
#include <stdexcept>

namespace linalg {

    class LIBLINALG_EXPORT Matrix
    {
        public:
            Matrix();
            Matrix(const uint32_t rows);
            Matrix(const uint32_t rows, const uint32_t columns);

            uint32_t rows() const;
            uint32_t columns() const;

            void reshape(const uint32_t rows, const uint32_t columns);

            double& operator()(const uint32_t x, const uint32_t y);
            const double& operator()(const uint32_t x, const uint32_t y) const;

            bool empty() const;
        private:
            void init(const uint32_t rows, const uint32_t columns);

            double* m_ptr;
            uint32_t m_rows;
            uint32_t m_columns;

            bool m_empty;
    };
}
