#pragma once
#include "product.h"
#include <vector>

enum class WarehouseType { CENTER, WEST, EAST };

class Warehouse {
private:
    std::string id;
    WarehouseType type;
    double latitude;
    double longitude;
    int maxCapacity;
    int currentStock;
    std::vector<Product> products;
    static int warehouseCounter;

public:
    Warehouse();
    Warehouse(WarehouseType t, double lat, double lon, int maxCap);
    Warehouse(const Warehouse& w);
    ~Warehouse() = default;

    void generateID();
    int calculateManhattanDistance(const Product& p) const;
    bool addProduct(const Product& p);
    bool removeProduct(const std::string& barcode);
    void listProducts() const;
    int searchProduct(const std::string& desc) const;
    void updateStock(int qty);

    void menu();
};