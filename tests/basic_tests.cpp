#include <liblinalg/matrix.h>

#include <gtest/gtest.h>

TEST(ConstructorTest, RowsAndColumns)
{
    linalg::Matrix nonEmpty(10, 4);

    EXPECT_EQ(nonEmpty.rows(), 10);
    EXPECT_EQ(nonEmpty.columns(), 4);
    EXPECT_EQ(nonEmpty.empty(), false);

    linalg::Matrix empty(0, 12);

    EXPECT_EQ(empty.empty(), true);
}

TEST(ConstructorTest, ConstRowsAndColumns)
{
    const linalg::Matrix nonEmpty(10, 4);

    EXPECT_EQ(nonEmpty.rows(), 10);
    EXPECT_EQ(nonEmpty.columns(), 4);
    EXPECT_EQ(nonEmpty.empty(), false);

    linalg::Matrix empty(0, 12);

    EXPECT_EQ(empty.empty(), true);
}

TEST(ConstructorTest, LesserShape)
{
    linalg::Matrix mat(10);

    EXPECT_EQ(mat.rows(), 10);
    EXPECT_EQ(mat.columns(), 1);
    EXPECT_EQ(mat.empty(), false);
}

TEST(ConstructorTest, EmptyMatrix)
{
    linalg::Matrix mat;

    EXPECT_EQ(mat.rows(), 0);
    EXPECT_EQ(mat.columns(), 0);
    EXPECT_EQ(mat.empty(), true);
}

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
