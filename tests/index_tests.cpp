#include <cstdint>
#include <liblinalg/matrix.h>

#include <gtest/gtest.h>

TEST(IndexTest, OperatorReadAndWrite)
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

        for (auto i = 0; i < test.rows(); i++)
        {
            for (auto j = 0; j < test.columns(); j++)
            {
                EXPECT_EQ(test(i,j), i * test.rows() + j);
            }
        }
    }
    catch (...)
    {FAIL();}
}

TEST(IndexTest, UncorrectRead)
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
                test(i*i,j*j);
            }
        }
    }
    catch(const std::out_of_range error)
    {
        EXPECT_STREQ("Matrix: Out of bounds", error.what());
    }
    catch (...)
    {FAIL();}
}

TEST(IndexTest, OutOfRows)
{
    uint32_t height = 10;
    uint32_t width = 12;
    try
    {
        linalg::Matrix test(height, width);

        for (auto i = 0; i <= test.rows(); i++)
        {
            for (auto j = 0; j < test.columns(); j++)
            {
                test(i,j);
            }
        }
    }
    catch(const std::out_of_range error)
    {
        EXPECT_STREQ("Matrix: Out of bounds", error.what());
    }
    catch (...)
    {FAIL();}
}

TEST(IndexTest, OutOfColumns)
{
    uint32_t height = 10;
    uint32_t width = 12;
    try
    {
        linalg::Matrix test(height, width);

        for (auto i = 0; i < test.rows(); i++)
        {
            for (auto j = 0; j <= test.columns(); j++)
            {
                test(i,j);
            }
        }
    }
    catch(const std::out_of_range error)
    {
        EXPECT_STREQ("Matrix: Out of bounds", error.what());
    }
    catch (...)
    {FAIL();}
}
