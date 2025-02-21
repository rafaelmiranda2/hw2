#include <sstream>
#include <iomanip>
#include "product.h"
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : Product (category, name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}
std::set<std::string> Book::keywords() const {
    std::set<std::string> words;
    words.insert(convToLower(name_));
    words.insert(isbn_);
    words.insert(convToLower(author_));
    return words;
}
std::string Book::getISBN() {
    return isbn_;
}
std::string Book::getAuthor() {
    return author_;
}
std::string Book::displayString() const {
    std::ostringstream os;
    os << std::fixed << std::setprecision(2) << price_;
    return name_ + "\n" +
    "Author: " + author_ + " " + "ISBN: " + isbn_ +  "\n" +
    os.str() + " " + std::to_string(qty_) + " left";
}
void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_;
}