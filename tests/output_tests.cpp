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

TEST(OutputTest, Dot)
{
    linalg::Matrix mat = {1};
    std::cout << mat << std::endl;
    std::cout << mat.at(0, 0) << std::endl;
}

TEST(OutputTest, LongMatrix)
{
    linalg::Matrix mat2 = { {7, 1, 3, 0}, {2, 8, 17, 25}, {-3, 4, 0, 1}, {5, 6, 73, 12}, {95, 16, 40, 37}, {62, 283, 0, 1} };
    std::cout << mat2 << std::endl;
}
