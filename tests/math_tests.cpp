#include <exception>
#include <liblinalg/matrix.h>
#include <gtest/gtest.h>
#include <ostream>
#include <utility>
#include <iostream>

TEST(MathTest, Sum)
{
    linalg::Matrix mat1 ({ {1, 333, 1, 1, 333}, {22, 1, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} });
    linalg::Matrix mat2 ({ {1, 42, 0, 23, 12}, {75, 38, 16, 2, -12}, {546, 2, 1, 2, 0}, {24, -1, -15, 85, 2} });

    std::cout << mat1 << std::endl;
    std::cout << mat2;

    linalg::Matrix mat3;
    mat3 = mat1 + mat2;

    std::cout << mat3;
}

TEST(MathTest, SumAssignment)
{
    linalg::Matrix mat1 ({ {1, 333, 1, 1, 333}, {22, 1, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} });
    linalg::Matrix mat2 ({ {1, 42, 0, 23, 12}, {75, 38, 16, 2, -12}, {546, 2, 1, 2, 0}, {24, -1, -15, 85, 2} });

    std::cout << mat1 << std::endl;
    std::cout << mat2;

    linalg::Matrix mat3(mat1.rows(), mat1.columns());

    mat3 += mat1 + mat2;
    std::cout << mat3;
}

TEST(MathTest, WrongShapeOnSum)
{
    uint32_t height = 10;
    uint32_t width = 12;
    try
    {
        linalg::Matrix mat1(height, width);
        linalg::Matrix mat2(width, height);

        mat1 += mat2;
        FAIL();
    }
    catch(const std::out_of_range error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ("Matrix: Different size of matrices", error.what());
    }
    catch (std::exception error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }

}

TEST(MathTest, SumEmptyMatrices)
{
    try
    {
        linalg::Matrix mat1;
        linalg::Matrix mat2;

        auto mat3 = mat1 + mat2;
        FAIL();
    }
    catch(const std::invalid_argument error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ("Matrix: Trying to sum empty matrices", error.what());
    }
    catch (std::exception error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
}

