#include "product.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

Product::Product() : price(0), quantity(0), latitude(0), longitude(0) {
    generateBarcode();
}

Product::Product(std::string desc, double pr, int qty, double lat, double lon)
    : description(desc), price(pr), quantity(qty), latitude(lat), longitude(lon) {
    generateBarcode();
}

Product::Product(const Product& p) {
    barcode = p.barcode;
    description = p.description;
    price = p.price;
    quantity = p.quantity;
    latitude = p.latitude;
    longitude = p.longitude;
}

void Product::generateBarcode() {
    srand(time(0));
    std::string part1 = "460";
    std::string part2 = std::to_string(1000 + (rand() % 9) * 1000);
    std::string part3 = std::to_string(100000 + rand() % 900000);
    barcode = part1 + part2 + part3;
}

void Product::setDescription(std::string desc) { description = desc; }
void Product::setPrice(double pr) { price = pr; }
void Product::setQuantity(int qty) { quantity = qty; }
void Product::setLatitude(double lat) { latitude = lat; }
void Product::setLongitude(double lon) { longitude = lon; }

std::string Product::getBarcode() const { return barcode; }
std::string Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
double Product::getLatitude() const { return latitude; }
double Product::getLongitude() const { return longitude; }

void Product::print() const {
    std::cout << std::left << std::setw(15) << barcode
        << std::setw(20) << description
        << std::setw(10) << price
        << std::setw(10) << quantity
        << std::setw(10) << latitude
        << std::setw(10) << longitude << std::endl;
}