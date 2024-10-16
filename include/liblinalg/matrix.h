#pragma once

#include "liblinalg/export.h"
#include <cstdint>
#include <stdexcept>

namespace linalg {

    class LIBLINALG_EXPORT Matrix
    {
        public:
            Matrix(uint32_t rows, uint32_t columns);

            uint32_t rows();
            uint32_t columns();

            void reshape(uint32_t rows, uint32_t columns);

            bool empty();
        private:
            double* m_ptr;
            uint32_t m_rows;
            uint32_t m_columns;

            bool m_empty;
    };
}
