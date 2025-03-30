#pragma once
#include <string>
#include <vector>
#include <cmath>

class Product {
private:
    std::string barcode;
    std::string description;
    double price;
    int quantity;
    double latitude;
    double longitude;

public:
    Product();
    Product(std::string desc, double pr, int qty, double lat, double lon);
    Product(const Product& p);
    ~Product() = default;

    void generateBarcode();
    void setDescription(std::string desc);
    void setPrice(double pr);
    void setQuantity(int qty);
    void setLatitude(double lat);
    void setLongitude(double lon);

    std::string getBarcode() const;
    std::string getDescription() const;
    double getPrice() const;
    int getQuantity() const;
    double getLatitude() const;
    double getLongitude() const;

    void print() const;
};