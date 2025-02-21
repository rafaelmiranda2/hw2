#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

class Movie : public Product {
    public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    std::string getGenre();
    std::string getRating();
    void dump(std::ostream& os) const;
    
    protected:
    std::string genre_;
    std::string rating_;
    
};
#endif

