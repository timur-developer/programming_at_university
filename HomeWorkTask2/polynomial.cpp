#include "polynomial.h"
#include <cmath>

Polynomial::Polynomial() {}

Polynomial::Polynomial(const std::vector<double>& coeffs, const std::vector<int>& exps)
    : coefficients(coeffs), exponents(exps) {
}

Polynomial::Polynomial(const Polynomial& p) {
    coefficients = p.coefficients;
    exponents = p.exponents;
}

void Polynomial::setCoefficient(int exp, double coeff) {
    for (size_t i = 0; i < exponents.size(); ++i) {
        if (exponents[i] == exp) {
            coefficients[i] = coeff;
            return;
        }
    }
    exponents.push_back(exp);
    coefficients.push_back(coeff);
}

double Polynomial::getCoefficient(int exp) const {
    for (size_t i = 0; i < exponents.size(); ++i) {
        if (exponents[i] == exp) {
            return coefficients[i];
        }
    }
    return 0.0;
}

int Polynomial::getDegree() const {
    if (exponents.empty()) return 0;
    int max = exponents[0];
    for (size_t i = 1; i < exponents.size(); ++i) {
        if (exponents[i] > max) max = exponents[i];
    }
    return max;
}

double Polynomial::evaluate(double x) const {
    double result = 0.0;
    for (size_t i = 0; i < coefficients.size(); ++i) {
        result += coefficients[i] * pow(x, exponents[i]);
    }
    return result;
}

void Polynomial::print() const {
    for (size_t i = 0; i < coefficients.size(); ++i) {
        if (i != 0) std::cout << " + ";
        std::cout << coefficients[i] << "x^" << exponents[i];
    }
    std::cout << std::endl;
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
    Polynomial result(*this);
    for (size_t i = 0; i < p.exponents.size(); ++i) {
        result.setCoefficient(p.exponents[i], result.getCoefficient(p.exponents[i]) + p.coefficients[i]);
    }
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& p) const {
    Polynomial result(*this);
    for (size_t i = 0; i < p.exponents.size(); ++i) {
        result.setCoefficient(p.exponents[i], result.getCoefficient(p.exponents[i]) - p.coefficients[i]);
    }
    return result;
}

void VectPolynomial::addPolynomials() {
    if (v1.size() != v2.size()) {
        std::cout << "Vectors must be of the same size!" << std::endl;
        return;
    }
    for (size_t i = 0; i < v1.size(); ++i) {
        vout.push_back(v1[i] + v2[i]);
    }
}

void VectPolynomial::subtractPolynomials() {
    if (v1.size() != v2.size()) {
        std::cout << "Vectors must be of the same size!" << std::endl;
        return;
    }
    for (size_t i = 0; i < v1.size(); ++i) {
        vout.push_back(v1[i] - v2[i]);
    }
}

void VectPolynomial::processPolynomials() {
    addPolynomials();
    subtractPolynomials();
}

void VectPolynomial::printResults() const {
    std::cout << "\nResults:\n";
    for (const auto& p : vout) {
        p.print();
        std::cout << "Value at x=2: " << p.evaluate(2) << std::endl;
    }
}