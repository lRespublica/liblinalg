#include <exception>
#include <liblinalg/matrix.h>
#include <gtest/gtest.h>
#include <ostream>
#include <stdexcept>
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

TEST(MathTest, Diff)
{
    linalg::Matrix mat1 ({ {1, 333, 1, 1, 333}, {22, 1, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} });
    linalg::Matrix mat2 ({ {1, 42, 0, 23, 12}, {75, 38, 16, 2, -12}, {546, 2, 1, 2, 0}, {24, -1, -15, 85, 2} });

    std::cout << mat1 << std::endl;
    std::cout << mat2;

    linalg::Matrix mat3;
    mat3 = mat1 - mat2;

    std::cout << mat3;
}

TEST(MathTest, DiffAssignment)
{
    linalg::Matrix mat1 ({ {1, 333, 1, 1, 333}, {22, 1, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} });
    linalg::Matrix mat2 ({ {1, 42, 0, 23, 12}, {75, 38, 16, 2, -12}, {546, 2, 1, 2, 0}, {24, -1, -15, 85, 2} });

    std::cout << mat1 << std::endl;
    std::cout << mat2;

    linalg::Matrix mat3(mat1.rows(), mat1.columns());

    mat3 -= mat1 - mat2;
    std::cout << mat3;
}

TEST(MathTest, WrongShapeOnDiff)
{
    uint32_t height = 10;
    uint32_t width = 12;
    try
    {
        linalg::Matrix mat1(height, width);
        linalg::Matrix mat2(width, height);

        mat1 -= mat2;
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

TEST(MathTest, DiffEmptyMatrices)
{
    try
    {
        linalg::Matrix mat1;
        linalg::Matrix mat2;

        auto mat3 = mat1 - mat2;
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

TEST(MathTest, ProdMatrixOnDouble)
{
    try
    {
        linalg::Matrix mat1 ({ {1, 42, 0, 23, 12}, {75, 38, 16, 2, -12}, {546, 2, 1, 2, 0}, {24, -1, -15, 85, 2} });
        std::cout << mat1 << std::endl;

        auto mat2 = mat1 * (-1);
        std::cout << mat2 << std::endl;
    }
    catch (std::exception error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
}

TEST(MathTest, ProdDoubleOnMatrix)
{
    try
    {
        linalg::Matrix mat1 ({ {1, 42, 0, 23, 12}, {75, 38, 16, 2, -12}, {546, 2, 1, 2, 0}, {24, -1, -15, 85, 2} });
        std::cout << mat1 << std::endl;

        auto mat2 = -10 * mat1;
        std::cout << mat2 << std::endl;
    }
    catch (std::exception error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
}

TEST(MathTest, ProdEmptyMatrixOnDouble)
{
    try
    {
        linalg::Matrix mat1;

        auto mat3 = mat1 * -1;
        FAIL();
    }
    catch(const std::invalid_argument error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ("Matrix: Trying to multiply a number by an empty matrix", error.what());
    }
    catch (std::exception error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
}

TEST(MathTest, ProdMatrixOnMatrix1)
{
    try
    {
        linalg::Matrix mat1 = { {1, 42, 0, 23, 12}, {75, 38, 16, 2, -12}, {546, 2, 1, 2, 0}, {24, -1, -15, 85, 2} };
        std::cout << mat1 << std::endl;

        linalg::Matrix mat2 = { {7, 1, 3, 0}, {2, 8, 17, 25}, {-3, 4, 0, 1}, {5, 6, 73, 12}, {62, 283, 0, 1} };
        std::cout << mat2 << std::endl;

        linalg::Matrix avaitedResult ({ {950, 3871, 2396, 1338}, {-181, -2941, 1017, 978}, {3833, 578, 1818, 75}, {760, 1032, 6260, 982}});

        mat1 *= mat2;
        std::cout << mat1 << std::endl;
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
}

TEST(MathTest, ProdMatrixOnMatrix2)
{
    try
    {
        linalg::Matrix mat1 = { {7, 1, 3, 0}, {2, 8, 17, 25}, {-3, 4, 0, 1}, {5, 6, 73, 12}, {62, 283, 0, 1} };
        std::cout << mat1 << std::endl;

        linalg::Matrix mat2 ({ {950, 3871, 2396, 1338}, {-181, -2941, 1017, 978}, {3833, 578, 1818, 75}, {760, 1032, 6260, 982}});
        std::cout << mat2 << std::endl;

        std::cout << mat1 * mat2 << std::endl;
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
}

TEST(MathTest, ProdMatrixOnMatrixWithError)
{
    try
    {
        linalg::Matrix mat1 ({ {950, 3871, 2396, 1338}, {-181, -2941, 1017, 978}, {3833, 578, 1818, 75}, {760, 1032, 6260, 982}});
        std::cout << mat1 << std::endl;

        linalg::Matrix mat2 = { {7, 1, 3, 0}, {2, 8, 17, 25}, {-3, 4, 0, 1}, {5, 6, 73, 12}, {62, 283, 0, 1} };
        std::cout << mat2 << std::endl;

        std::cout << mat1 * mat2 << std::endl;
        FAIL();
    }
    catch(const std::out_of_range error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ("Matrix: Matrices are incompatible for multiplication", error.what());
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
}
