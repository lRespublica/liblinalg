#include <algorithm>
#include <exception>
#include <iterator>
#include <liblinalg/matrix.h>
#include <gtest/gtest.h>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <iostream>

TEST(MathTest, Norm)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2}, {-1, 0, 1}, {2, 3, 4}});
        auto norm = std::round(mat.norm() * 1000) / 1000;
        EXPECT_EQ(norm, 7.746);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Trace)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2}, {-1, 0, 1}, {2, 3, 4}});
        EXPECT_EQ(mat.trace(), 0);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, TraceWithNonSquare)
{
    try
    {
        linalg::Matrix mat ({{0, 0, 0}, {-4, -3, -2}, {-1, 0, 1}, {2, 3, 4}});
        EXPECT_EQ(mat.trace(), 0);
        FAIL();
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Matrix: Cannot calculate trace from non-square matrix");
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Minor)
{
    try
    {
        linalg::Matrix mat1 ({ {950, 3871, 2396, 1338}, {-181, -2941, 1017, 978}, {3833, 578, 1818, 75}, {760, 1032, 6260, 982}});
        std::cout << mat1 << std::endl;


        auto minor = mat1.minor (0, 3);
        std::cout << minor << std::endl;

        linalg::Matrix awaitedResult = {{-181, -2941, 1017}, {3833, 578, 1818}, {760, 1032, 6260}};
        EXPECT_EQ(awaitedResult, minor);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Matrix: Cannot calculate trace from non-square matrix");
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Det3x3)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2}, {-10, 7, 1}, {2, 3, 4}});
        EXPECT_EQ(mat.det(), -138);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Det4x4)
{
    try
    {
        linalg::Matrix mat ({ {950, 3871, 2396, 1338}, {-181, -2941, 1017, 978}, {3833, 578, 1818, 75}, {760, 1032, 6260, 982}});
        auto det = mat.det();

        EXPECT_EQ(det, -131821186550958);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}


TEST(MathTest, DetNonSquare)
{
    try
    {
        linalg::Matrix mat ({ {950, 3871, 2396, 1338, 1}, {-181, -2941, 1017, 978, 1}, {3833, 578, 1818, 75, 1}, {760, 1032, 6260, 982, 1}});
        auto det = mat.det();
        FAIL();
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Matrix: Cannot calculate determinant from non-square matrix");
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Concatenate)
{
    try
    {
        linalg::Matrix mat1 ({ {950, 3871, 2396, 1338, 1}, {-181, -2941, 1017, 978, 1}, {3833, 578, 1818, 75, 1}, {760, 1032, 6260, 982, 1}});
        std::cout << mat1 << std::endl;

        linalg::Matrix mat2 = { {7, 1, 3}, {2, 8, 25}, {-3, 4, 1}, {5, 6, 12} };
        std::cout << mat2 << std::endl;

        auto mat3 = linalg::concatenate(mat1, mat2);

        std::cout << mat3 << std::endl;
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, ConcatenateError)
{
    try
    {
        linalg::Matrix mat1 ({ {950, 3871, 2396, 1338, 1}, {-181, -2941, 1017, 978, 1}, {3833, 578, 1818, 75, 1}, {760, 1032, 6260, 982, 1}});
        std::cout << mat1 << std::endl;

        linalg::Matrix mat2 = { {7, 1, 3}, {2, 8, 25}, {-3, 4, 1}, {5, 6, 12}, {0, 0, 0} };
        std::cout << mat2 << std::endl;

        auto mat3 = linalg::concatenate(mat1, mat2);
        FAIL();
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Matrix: Cannot concatenate matrix with different height");
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Invert3x3)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2}, {-10, 7, 1}, {2, 3, 4}});
        std::cout << mat << std::endl;

        auto revMat = linalg::invert(mat);
        std::cout << revMat << std::endl;
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Power3x3_To_3)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2}, {-10, 7, 1}, {2, 3, 4}});
        std::cout << mat << std::endl;

        auto powMat = linalg::pow(mat, 3);
        linalg::Matrix awaitedResult = {{ -24, -240, -111 },
                                        {-646,  751,  262 },
                                        {-120,  324,  147 }};

        std::cout << powMat << std::endl;
        EXPECT_EQ(awaitedResult, powMat);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}

TEST(MathTest, Power5x5_To_9)
{
    try
    {
        linalg::Matrix mat ({{-4, -3, -2, 7, 12}, {-10, 7, 1, 1, -2}, {2, 3, 4, 2, 2}, {6, 1, 2, 3, 0}, {19, 1, 2, -1, -19}});
        std::cout << mat << std::endl;

        auto powMat = linalg::pow(mat, 9);
        linalg::Matrix awaitedResult = {{ -4440410788944,   -496067470984,   -645596005999,   1190672454220,   5303657726290 },
                                        { -778547989428,    -84351940931,   -112294192561,    204129889140,   921981647542 },
                                        { -231601322352,    -25358542811,    -33475558557,     61396263959,    275308394604 },
                                        { 869343498720,     96584615510,    126231065413,   -231969109574,  -1036505905002},
                                        { 8558230259887,    953513927628,   1243432938937,  -2290009965832, -10213895780405}};

        std::cout << powMat << std::endl;
        EXPECT_EQ(awaitedResult, powMat);
    }
    catch (std::logic_error error)
    {
        std::cout << error.what() << std::endl;
        FAIL();
    }
    catch (...)
    {
        FAIL();
    }
}
