#include "solver.cpp"
#include <gtest/gtest.h>
#define INFINITESOLVEC std::vector<double>({0, 0, 0})

std::vector<double> getEquationsVector(const double a, const double b, const double c){
    std::vector<double> solution = {};
    double x1 = 0;
    double x2 = 0;
    int solutions_no = solveEquation(a, b, c, x1, x2);
    if(solutions_no == INFINITESOLUTIONS){
        solution = INFINITESOLVEC;
    }
    if(solutions_no == 1){
        solution = {x1};
    }
    if(solutions_no == 2){
        solution = {x1, x2};
    }
    return solution;
};

TEST(SquareEqTest, InfiniteSolutions) {
    ASSERT_EQ(INFINITESOLVEC, getEquationsVector(0, 0, 0));
}

TEST(SquareEqTest, NoSolutions) {
    ASSERT_EQ(std::vector<double>({}), getEquationsVector(0, 0, 1));
    ASSERT_EQ(std::vector<double>({}), getEquationsVector(1, 0, 1));
}

TEST(SquareEqTest, LinearEq) {
    ASSERT_EQ(std::vector<double>({-6.}), getEquationsVector(0, 1, 6));
    ASSERT_EQ(std::vector<double>({1}), getEquationsVector(0, -1, 1));
    ASSERT_EQ(std::vector<double>({1 / 5.}), getEquationsVector(0, -5, 1));
}

TEST(SquareEqTest, OneSolution) {
    ASSERT_EQ(std::vector<double>({-1}), getEquationsVector(1, 2, 1));
}

TEST(SquareEqTest, OrdinaryCases) {
    ASSERT_EQ(std::vector<double>({-1, 1}), getEquationsVector(1, 0, -1));
    ASSERT_EQ(std::vector<double>({-1, 1/2.}), getEquationsVector(1, 1/2., -1/2.));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}