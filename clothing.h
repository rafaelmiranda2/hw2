#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

class Clothing : public Product {
    public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    std::string getSize();
    std::string getBrand();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    protected:
    std::string size_;
    std::string brand_;
    
};
#endif

