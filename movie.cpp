#include <sstream>
#include <iomanip>
#include "product.h"
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) : Product (category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}
std::string Movie::getGenre() {
    return genre_;
}
std::string Movie::getRating() {
    return rating_;
}
std::set<std::string> Movie::keywords() const {
    std::set<std::string> words;
    words.insert(convToLower(name_));
    words.insert(convToLower(genre_));
    words.insert(convToLower(rating_));
    return words;
}
std::string Movie::displayString() const {
    std::ostringstream os;
    os << std::fixed << std::setprecision(2) << price_;
    return name_ + "\n" +
    "Genre: " + genre_ + " " + "Rating: " + rating_ +  "\n" +
    os.str() + " " + std::to_string(qty_) + " left";
}
void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_;
}