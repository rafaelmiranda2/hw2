#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class MyDataStore : public DataStore {
    public: 
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToUserCart(std::string& username, Product* product);
    void buyUserCart(std::string& username);
    void viewUserCart(std::string& username, std::ostream& out);
    void prodCount();

    protected:
    std::vector<Product*> prodSet;
    std::vector<User*>  userSet;
    std::map<std::string, std::vector<Product*>> userCart;
};

#endif