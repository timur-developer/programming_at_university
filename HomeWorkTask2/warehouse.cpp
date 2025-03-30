#include "warehouse.h"
#include <iostream>
#include <iomanip>
#include <limits>

int Warehouse::warehouseCounter = 100;

Warehouse::Warehouse() : latitude(0), longitude(0), maxCapacity(0), currentStock(0) {
    generateID();
}

Warehouse::Warehouse(WarehouseType t, double lat, double lon, int maxCap)
    : type(t), latitude(lat), longitude(lon), maxCapacity(maxCap), currentStock(0) {
    generateID();
}

Warehouse::Warehouse(const Warehouse& w) {
    id = w.id;
    type = w.type;
    latitude = w.latitude;
    longitude = w.longitude;
    maxCapacity = w.maxCapacity;
    currentStock = w.currentStock;
    products = w.products;
}

void Warehouse::generateID() {
    id = "W" + std::to_string(warehouseCounter++);
}

int Warehouse::calculateManhattanDistance(const Product& p) const {
    return abs(latitude - p.getLatitude()) + abs(longitude - p.getLongitude());
}

bool Warehouse::addProduct(const Product& p) {
    if (currentStock + p.getQuantity() > maxCapacity) {
        std::cout << "Not enough space in the warehouse!" << std::endl;
        return false;
    }
    products.push_back(p);
    currentStock += p.getQuantity();
    return true;
}

bool Warehouse::removeProduct(const std::string& barcode) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getBarcode() == barcode) {
            currentStock -= it->getQuantity();
            products.erase(it);
            return true;
        }
    }
    return false;
}

void Warehouse::listProducts() const {
    std::cout << "\nProducts in Warehouse " << id << ":\n";
    std::cout << std::left << std::setw(15) << "Barcode"
        << std::setw(20) << "Description"
        << std::setw(10) << "Price"
        << std::setw(10) << "Quantity"
        << std::setw(10) << "Latitude"
        << std::setw(10) << "Longitude" << std::endl;
    for (const auto& p : products) {
        p.print();
    }
}

int Warehouse::searchProduct(const std::string& desc) const {
    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i].getDescription() == desc) {
            return i;
        }
    }
    return -1;
}

void Warehouse::menu() {
    int opc;
    do {
        std::cout << "\n--- Warehouse " << id << " Menu ---\n"
            << "1. Add Product\n"
            << "2. List Products\n"
            << "3. Search Product\n"
            << "4. Remove Product\n"
            << "5. Exit\n"
            << "Option: ";
        std::cin >> opc;

        switch (opc) {
        case 1: {
            std::string desc;
            double price, lat, lon;
            int qty;
            std::cout << "Description: ";
            std::cin.ignore();
            std::getline(std::cin, desc);
            std::cout << "Price: ";
            std::cin >> price;
            std::cout << "Quantity: ";
            std::cin >> qty;
            std::cout << "Latitude (41-82): ";
            std::cin >> lat;
            std::cout << "Longitude (19-169): ";
            std::cin >> lon;
            Product p(desc, price, qty, lat, lon);
            addProduct(p);
            break;
        }
        case 2:
            listProducts();
            break;
        case 3: {
            std::string desc;
            std::cout << "Enter product description: ";
            std::cin.ignore();
            std::getline(std::cin, desc);
            int pos = searchProduct(desc);
            if (pos != -1) {
                products[pos].print();
            }
            else {
                std::cout << "Product not found!" << std::endl;
            }
            break;
        }
        case 4: {
            std::string barcode;
            std::cout << "Enter product barcode: ";
            std::cin >> barcode;
            if (!removeProduct(barcode)) {
                std::cout << "Product not found!" << std::endl;
            }
            else {
                std::cout << "Product removed!" << std::endl;
            }
            break;
        }
        case 5:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
        }
    } while (opc != 5);
}