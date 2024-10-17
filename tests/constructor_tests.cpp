#include <liblinalg/matrix.h>

#include <gtest/gtest.h>

TEST(ConstructorTest, RowsAndColumns)
{
    try {
        linalg::Matrix nonEmpty(10, 4);

        EXPECT_EQ(nonEmpty.rows(), 10);
        EXPECT_EQ(nonEmpty.columns(), 4);
        EXPECT_EQ(nonEmpty.empty(), false);

        linalg::Matrix empty(0, 12);

        EXPECT_EQ(empty.empty(), true);
    }
    catch(...)
    {FAIL();}
}

TEST(ConstructorTest, ConstRowsAndColumns)
{
    try
    {
        const linalg::Matrix nonEmpty(10, 4);

        EXPECT_EQ(nonEmpty.rows(), 10);
        EXPECT_EQ(nonEmpty.columns(), 4);
        EXPECT_EQ(nonEmpty.empty(), false);

        linalg::Matrix empty(0, 12);

        EXPECT_EQ(empty.empty(), true);
    }
    catch(...)
    {FAIL();}
}

TEST(ConstructorTest, LesserShape)
{
    try
    {
        linalg::Matrix mat(10);

        EXPECT_EQ(mat.rows(), 10);
        EXPECT_EQ(mat.columns(), 1);
        EXPECT_EQ(mat.empty(), false);
    }
    catch(...)
    {FAIL();}

}

TEST(ConstructorTest, EmptyMatrix)
{
    try
    {
        linalg::Matrix mat;

        EXPECT_EQ(mat.rows(), 0);
        EXPECT_EQ(mat.columns(), 0);
        EXPECT_EQ(mat.empty(), true);
    }
    catch(...)
    {FAIL();}

}
