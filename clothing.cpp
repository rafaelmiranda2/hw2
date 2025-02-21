#include <sstream>
#include <iomanip>
#include "product.h"
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : Product (category, name, price, qty) 
{
    size_ = size;
    brand_ = brand;
}
std::string Clothing::getSize() {
    return size_;
}
std::string Clothing::getBrand() {
    return brand_;
}
std::set<std::string> Clothing::keywords() const {
    std::set<std::string> words;
    //std::set<std::string> parsedName = parseStringToWords(convToLower(name_));
    //std::set<std::string> parsedBrand = parseStringToWords(convToLower(name_));
    words.insert(convToLower(name_));
    words.insert(convToLower(size_));
    words.insert(convToLower(brand_));
    return words;
}
std::string Clothing::displayString() const {
    std::ostringstream os;
    os << std::fixed << std::setprecision(2) << price_;
    return name_ + "\n" +
    "Size: " + size_ + " " + "Brand: " + brand_ +  "\n" +
    os.str() + " " + std::to_string(qty_) + " left";
}
void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_;
}