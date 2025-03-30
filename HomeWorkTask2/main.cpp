#include <iostream>
#include "warehouse.h"
#include "polynomial.h"

int main() {
    // ������ ������ �� ��������
    Warehouse center(WarehouseType::CENTER, 55.75, 37.62, 1000);
    center.menu();

    // ������ ������ � ����������
    VectPolynomial polySystem;
    polySystem.processPolynomials();
    polySystem.printResults();

    return 0;
}