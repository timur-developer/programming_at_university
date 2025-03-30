#include <iostream>
#include "warehouse.h"
#include "polynomial.h"

int main() {
    // Пример работы со складами
    Warehouse center(WarehouseType::CENTER, 55.75, 37.62, 1000);
    center.menu();

    // Пример работы с полиномами
    VectPolynomial polySystem;
    polySystem.processPolynomials();
    polySystem.printResults();

    return 0;
}