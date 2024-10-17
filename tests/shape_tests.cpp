#include <liblinalg/matrix.h>

#include <gtest/gtest.h>

TEST(ShapeTest, CorrectReshape)
{
    linalg::Matrix mat(10, 4);

    try
    {
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
    linalg::Matrix mat(10, 4);

    try
    {
        mat.reshape(2, 25);
        FAIL();
    }
    catch(const std::out_of_range& expected)
    {}
}

