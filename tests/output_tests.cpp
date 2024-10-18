#include <liblinalg/matrix.h>
#include <gtest/gtest.h>
#include <ostream>
#include <utility>
#include <iostream>

TEST(OutputTest, CoutIntegers)
{
    linalg::Matrix mat ({ {1, 333, 1, 1, 333}, {22, 1, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} });
    std::cout << mat;
}

TEST(OutputTest, CoutWithPoint)
{
    linalg::Matrix mat({ {1, 333.124, 1, 1, 333}, {22, 1.90001, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} });
    std::cout << mat;
    std::cout << mat(0, 1);
}

TEST(OutputTest, Row)
{
    linalg::Matrix mat = { 1, 333, 1, 22};
    std::cout << mat;
}
