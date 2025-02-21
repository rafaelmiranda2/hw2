#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

class Book : public Product {
    public:
    Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    std::string getISBN();
    std::string getAuthor();
    void dump(std::ostream& os) const;
    
    protected:
    std::string isbn_;
    std::string author_;
    
};
#endif

