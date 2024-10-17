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

