#include <exception>
#include <iterator>
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

TEST(MathTest, Minor)
{
    try
    {
        linalg::Matrix mat1 ({ {950, 3871, 2396, 1338}, {-181, -2941, 1017, 978}, {3833, 578, 1818, 75}, {760, 1032, 6260, 982}});
        std::cout << mat1 << std::endl;


        auto minor = mat1.minor (0, 3);
        std::cout << minor << std::endl;

        linalg::Matrix awaitedResult = {{-181, -2941, 1017}, {3833, 578, 1818}, {760, 1032, 6260}};
        EXPECT_EQ(awaitedResult, minor);
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

TEST(MathTest, Det3x3)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2}, {-10, 7, 1}, {2, 3, 4}});
        EXPECT_EQ(mat.det(), -138);
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

TEST(MathTest, Det4x4)
{
    try
    {
        linalg::Matrix mat ({ {950, 3871, 2396, 1338}, {-181, -2941, 1017, 978}, {3833, 578, 1818, 75}, {760, 1032, 6260, 982}});
        auto det = mat.det();

        EXPECT_EQ(det, -131821186550958);
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


TEST(MathTest, DetNonSquare)
{
    try
    {
        linalg::Matrix mat ({ {950, 3871, 2396, 1338, 1}, {-181, -2941, 1017, 978, 1}, {3833, 578, 1818, 75, 1}, {760, 1032, 6260, 982, 1}});
        auto det = mat.det();
        FAIL();
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Matrix: Cannot calculate determinant from non-square matrix");
    }
    catch (...)
    {
        FAIL();
    }
}

