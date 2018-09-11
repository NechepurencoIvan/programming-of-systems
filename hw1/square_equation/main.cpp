#include <iostream>
#include <vector>
#include <cmath>

#define infiniteSolutions  std::vector<double>({0, 0, 0, 0});
#define epsilont  0.00001

/**
 * Считывает коэффициенты с потока ввода
 * @param a старший коэффициент
 * @param b коэффициент линейного члена
 * @param c свободный член
 */
void readCoefficients(double& a, double& b, double& c){
    std::cout<<"Please enter coefficients a, b, c of equation \"ax^2 + bx + c = 0\": ";
    std::cin>>a>>b>>c;
}

/**
 * Сравнивает данные переменные на равенство с учетом погрешности
 * @param d1 первая переменная
 * @param d2 вторая переменная
 * @return ответ, равны ли переменные
 */

bool equals(const double d1, const double d2) {
    return (d1 - d2 < epsilont) && (d1 - d2 > -epsilont);
}

/**
 * Избавляет вектор решений от -0 -ей
 * @param solutions полученные решения
 */
void normalize(std::vector<double>& solutions){
    for(double& d : solutions){
        if(equals(d, 0)){
            d = 0;
        }
    }
};

/**
 * Выврдит решения на экран
 * @param solutions вектор с решениями уравнения
 */

void printSolution(const std::vector<double>& solutions) {
    switch(solutions.size()){
        case 0:
            std::cout<<"no solutions"<<std::endl;
            break;
        case 1:
            std::cout<<"one solution "<<solutions[0]<<std::endl;
            break;
        case 2:
            std::cout<<"two solutions: "<< solutions[0] << ", " << solutions[1]<<std::endl;
            break;
        default:
            std::cout<<" infinitely many solutions"<<std::endl;
    }
}
/**
 * решает линейное уравнение
 * @param b коэффициент линейного члена
 * @param c свободный член
 * @param solutions вектор решений
 */
void solveLinearEquation(const double b, const double c, std::vector<double>& solutions) {
    if(equals(b, 0)){
        if (equals(c, 0)) {
            solutions = infiniteSolutions;
            return;
        } else {
            return;
        }
    }
    solutions = {-c / b};
}
/**
 * вычисляеи детерминант квадратного уравнения
 * @param a старший коэффициент
 * @param b коэффициент линейного члена
 * @param c свободный член
 * @return детерминант
 */
double getDeterminant(const double a, const double b, const double c){
    return b*b - 4*a*c;
}
/**
 * решает квадратное уравнение
 * @param a старший коэффициент
 * @param b коэффициент линейного члена
 * @param c свободный член
 * @param solutions вектор решений
 */
void solveEquation(const double a, const double b, const double c, std::vector<double>& solutions) {
    if(equals(a, 0) ){
        solveLinearEquation(b, c, solutions);
    } else {
        double d = getDeterminant(a, b, c);
        if(equals(d, 0)){
            solutions = {-b / 2 / a};
            return;
        }
        if(d < 0){
            return;
        }
        double x1 = (-b - std::sqrt(d))/(2 * a);//Дважды считать корень?
        double x2 = (-b + std::sqrt(d))/(2 * a);
        solutions = {x1, x2};
    }
}

int main() {
    double a, b, c;
    std::vector<double> solutions;
    readCoefficients(a, b, c);
    solveEquation(a, b, c, solutions);
    normalize(solutions);
    printSolution(solutions);
    return 0;
}