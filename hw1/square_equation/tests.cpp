#include "solver.cpp"
#include <gtest/gtest.h>

TEST(SquareEqTest, InfiniteSolutions) {
    ASSERT_EQ(INFINITESOLUTIONS, solveEquation(0, 0, 0));
}

TEST(SquareEqTest, NoSolutions) {
    ASSERT_EQ(std::vector<double>({}), solveEquation(0, 0, 1));
    ASSERT_EQ(std::vector<double>({}), solveEquation(1, 0, 1));
}

TEST(SquareEqTest, LinearEq) {
    ASSERT_EQ(std::vector<double>({-6.}), solveEquation(0, 1, 6));
    ASSERT_EQ(std::vector<double>({1}), solveEquation(0, -1, 1));
    ASSERT_EQ(std::vector<double>({1 / 5.}), solveEquation(0, -5, 1));
}

TEST(SquareEqTest, OneSolution) {
    ASSERT_EQ(std::vector<double>({-1}), solveEquation(1, 2, 1));
}

TEST(SquareEqTest, OrdinaryCases) {
    ASSERT_EQ(std::vector<double>({-1, 1}), solveEquation(1, 0, -1));
    ASSERT_EQ(std::vector<double>({-1, 1/2.}), solveEquation(1, 1/2., -1/2.));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}