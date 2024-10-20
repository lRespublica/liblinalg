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
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Trace)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2}, {-1, 0, 1}, {2, 3, 4}});
        EXPECT_EQ(mat.trace(), 0);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, TraceWithNonSquare)
{
    try
    {
        linalg::Matrix mat ({{0, 0, 0}, {-4, -3, -2}, {-1, 0, 1}, {2, 3, 4}});
        EXPECT_EQ(mat.trace(), 0);
        FAIL();
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Matrix: Cannot calculate trace from non-square matrix");
    }
    catch (...)
    {
        FAIL();
    }
}
