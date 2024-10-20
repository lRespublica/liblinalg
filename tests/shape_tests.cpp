#include <iostream>
#include <liblinalg/matrix.h>

#include <gtest/gtest.h>

TEST(ShapeTest, CorrectReshape)
{
    try
    {
        linalg::Matrix mat(10, 4);

        mat.reshape(2, 20);

        EXPECT_EQ(mat.rows(), 2);
        EXPECT_EQ(mat.columns(), 20);
        EXPECT_EQ(mat.empty(), false);
    }
    catch(...)
    {FAIL();}
}

TEST(ShapeTest, UncorrectReshape)
{
    try
    {
        linalg::Matrix mat(10, 4);

        mat.reshape(2, 25);
        FAIL();
    }
    catch(const std::out_of_range& expected)
    {}
    catch(...)
    {FAIL();}
}

TEST(ShapeTest, Transpose1)
{
    try
    {
        linalg::Matrix mat1 ({ {950, 3871, 2396, 1338, 1}, {-181, -2941, 1017, 978, 1}, {3833, 578, 1818, 75, 1}, {760, 1032, 6260, 982, 1}});
        std::cout << mat1 << std::endl;

        auto mat2 = linalg::transpose(mat1);
        std::cout << mat2 << std::endl;
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(ShapeTest, Transpose2)
{
    try
    {
        linalg::Matrix mat1 ({ {950, 3871, 2396, 1338, 1}});
        std::cout << mat1 << std::endl;

        auto mat2 = linalg::transpose(mat1);
        std::cout << mat2 << std::endl;
    }
    catch (...)
    {
        FAIL();
    }
}
