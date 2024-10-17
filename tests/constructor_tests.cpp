#include <liblinalg/matrix.h>

#include <gtest/gtest.h>
#include <ostream>
#include <utility>
#include <iostream>

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

TEST(ConstructorTest, CopyConstructor)
{
    uint32_t height = 10;
    uint32_t width = 12;
    try
    {
        linalg::Matrix test(height, width);

        for (auto i = 0; i < test.rows(); i++)
        {
            for (auto j = 0; j < test.columns(); j++)
            {
                test(i, j) = i * test.rows() + j;
            }
        }

        linalg::Matrix newMat{test};

        for (auto i = 0; i < newMat.rows(); i++)
        {
            for (auto j = 0; j < newMat.columns(); j++)
            {
                EXPECT_EQ(test(i,j),  newMat(i,j));
            }
        }
    }
    catch (...)
    {FAIL();}
}

TEST(ConstructorTest, CopyAndMoveConstructor)
{
    uint32_t height = 10;
    uint32_t width = 12;
    try
    {
        linalg::Matrix test(height, width);

        for (auto i = 0; i < test.rows(); i++)
        {
            for (auto j = 0; j < test.columns(); j++)
            {
                test(i, j) = i * test.rows() + j;
            }
        }

        linalg::Matrix tmpMat{test};
        EXPECT_NE(tmpMat.data(), nullptr);
        EXPECT_FALSE(tmpMat.empty());

        linalg::Matrix newMat{std::move(tmpMat)};
        EXPECT_EQ(tmpMat.data(), nullptr);
        EXPECT_TRUE(tmpMat.empty());

        for (auto i = 0; i < newMat.rows(); i++)
        {
            for (auto j = 0; j < newMat.columns(); j++)
            {
                EXPECT_EQ(test(i,j),  newMat(i,j));
            }
        }
    }
    catch (...)
    {FAIL();}
}

TEST(ConstructorTest, CopyAndMoveWithAssignment)
{
    uint32_t height = 10;
    uint32_t width = 12;
    try
    {
        linalg::Matrix test(height, width);
        test = {{1}, {2}, {3}, {4}, {5}};

        linalg::Matrix tmpMat = test;
        EXPECT_NE(tmpMat.data(), nullptr);
        EXPECT_FALSE(tmpMat.empty());

        linalg::Matrix newMat = std::move(tmpMat);
        EXPECT_EQ(tmpMat.data(), nullptr);
        EXPECT_TRUE(tmpMat.empty());

        for (auto i = 0; i < newMat.rows(); i++)
        {
            for (auto j = 0; j < newMat.columns(); j++)
            {
                EXPECT_EQ(test(i,j),  newMat(i,j));
            }
        }
    }
    catch (...)
    {FAIL();}
}

TEST(ConstructorTest, InitalizerList)
{
    uint32_t height = 3;
    uint32_t width = 5;
    try
    {
        linalg::Matrix test(height, width);

        for (auto i = 0; i < test.rows(); i++)
        {
            for (auto j = 0; j < test.columns(); j++)
            {
                test(i, j) = i * test.columns() + j + 1;
            }
        }

        linalg::Matrix ref = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14,15}};
        EXPECT_EQ(ref.rows(), 3);
        EXPECT_EQ(ref.columns(), 5);

        for (auto i = 0; i < test.rows(); i++)
        {
            for (auto j = 0; j < test.columns(); j++)
            {
                EXPECT_EQ(test(i, j), ref(i, j));
            }
        }
    }
    catch (...)
    {FAIL();}
}

