#include <exception>
#include <liblinalg/matrix.h>
#include <gtest/gtest.h>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <iostream>

TEST(MathTest, Norm)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2}, {-1, 0, 1}, {2, 3, 4}});
        auto norm = std::round(mat.norm() * 1000) / 1000;
        EXPECT_EQ(norm, 7.746);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
}
