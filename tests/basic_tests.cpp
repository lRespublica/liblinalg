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
