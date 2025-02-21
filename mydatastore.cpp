#include <sstream>
#include <iomanip>
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore() : DataStore() {

}
MyDataStore::~MyDataStore() {
  for (size_t i = 0; i < prodSet.size(); ++i) {
    delete prodSet[i];
  }
  prodSet.clear();
  for (size_t i = 0; i < userSet.size(); i++) {
    delete userSet[i];
  }
  userSet.clear();
}
void MyDataStore::addProduct(Product* p){
    prodSet.push_back(p);
}
void MyDataStore::addUser(User* u) {
    userSet.push_back(u);
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> result;
    if (type == 1) { //OR search
        for (size_t i = 0; i < terms.size(); i++) { //Turn terms into keywords
            std::set<std::string> parsedTerms = parseStringToWords(terms[i]);
            for (size_t j = 0; j < prodSet.size(); j++) {
                std::set<std::string> keyWords = prodSet[j]->keywords();
                std::set<std::string>::iterator it;
                std::set<std::string>::iterator it2;
                std::set<std::string> parsedKeyWords;
                for (it = keyWords.begin(); it != keyWords.end(); ++it) {
                    parsedKeyWords = parseStringToWords(*it);
                    for (it2 = parsedTerms.begin(); it2 != parsedTerms.end(); ++it2) {
                        if (parsedKeyWords.find(*it2) != parsedKeyWords.end()) {
                            result.push_back(prodSet[j]);
                            break;
                        }
                    }
                }
            }
        }
    }
    if (type == 0) { //AND search
      std::set<Product*> differentResults;
      for (size_t i = 0; i < prodSet.size(); i++) {
        std::set<std::string> keyWords = prodSet[i]->keywords();
        std::set<std::string> parsedKeyWords;

        std::set<std::string>::iterator it;
        for (it = keyWords.begin(); it != keyWords.end(); ++it) {
            std::set<std::string> temp = parseStringToWords(*it);
            parsedKeyWords.insert(temp.begin(), temp.end());
        }

        bool perfectMatch = true;

        for (size_t j = 0; j < terms.size(); j++) {
          std::set<std::string> parsedTerms = parseStringToWords(terms[j]);
          std::set<std::string> cross = setIntersection(parsedTerms, parsedKeyWords);
          if (cross.empty() == true) {
            perfectMatch = false;
            break;
          }
        }
        if (perfectMatch == true) {
          differentResults.insert(prodSet[i]);
        }
      }
      result.assign(differentResults.begin(), differentResults.end());
    }
    return result;
}
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    for (size_t i = 0; i < prodSet.size(); i++) {
        prodSet[i]->dump(ofile);
        //if (i < prodSet.size() - 1) {
        ofile << "\n";
        //}
    }
    ofile << "</products>\n";
    ofile << "<users>\n";
    for (size_t i = 0; i < userSet.size(); i++) {
        userSet[i]->dump(ofile);
        if (i < userSet.size() - 1) {
          //ofile << "\n";
        }
    }
    ofile << "</users>\n";
}
void MyDataStore::addToUserCart(std::string& username, Product* product) {
    userCart[username].push_back(product);
}
void MyDataStore::viewUserCart(std::string& username, std::ostream& out) {
    std::map<std::string, std::vector<Product*>>::iterator it = userCart.find(username);
    std::vector<Product*>& itemsInCart = it->second;
    if (it == userCart.end()) {
        out << "Invalid Username" << "\n";
        return;
    }
    for (size_t i = 0; i < itemsInCart.size(); i++) {
        out << "Item " << i + 1 << "\n";
        out << itemsInCart[i]->displayString() << endl << endl;
    }
}
void MyDataStore::prodCount() {
    for (size_t i = 0; i < prodSet.size(); i++) {
        cout << "Product #" << i + 1 << endl;
    }
}
void MyDataStore::buyUserCart(std::string& username) {
    std::map<std::string, std::vector<Product*>>::iterator it = userCart.find(username);
    std::vector<Product*>& itemsInCart = it->second;
    
    User* user = nullptr;
    for (size_t i = 0; i < userSet.size(); i++) {
      if (userSet[i]->getName() == username) {
        user = userSet[i];
        break;
      }
    }
    if (user == nullptr) {
      cout << "Invalid username" << endl;
      return;
    }
    double userBal = user->getBalance();
    double price = 0.0;
    double totalPrice = 0.0;

     if (it == userCart.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    for (size_t i = 0; i < itemsInCart.size(); i++) { //Iterate through cart
        Product* product = itemsInCart[i];
        price = product->getPrice();
        if (price + totalPrice < userBal && product->getQty() > 0) {
          totalPrice += price;
          product->subtractQty(1);
          user->deductAmount(price);
          itemsInCart.erase(itemsInCart.begin() + i);
          i--;
        }
        //cout << "Enough Available" << endl;
        price = 0.0;
    }
}
