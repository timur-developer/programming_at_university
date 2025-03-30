#pragma once
#include <vector>
#include <iostream>

class Polynomial {
private:
    std::vector<double> coefficients;
    std::vector<int> exponents;

public:
    Polynomial();
    Polynomial(const std::vector<double>& coeffs, const std::vector<int>& exps);
    Polynomial(const Polynomial& p);
    ~Polynomial() = default;

    void setCoefficient(int exp, double coeff);
    double getCoefficient(int exp) const;
    int getDegree() const;
    double evaluate(double x) const;
    void print() const;

    Polynomial operator+(const Polynomial& p) const;
    Polynomial operator-(const Polynomial& p) const;
};

class VectPolynomial {
private:
    std::vector<Polynomial> v1, v2, vout;

public:
    void addPolynomials();
    void subtractPolynomials();
    void processPolynomials();
    void printResults() const;
};