#ifndef LR2_SUPPLIER_H
#define LR2_SUPPLIER_H

#include "../User/User.h"
#include <iostream>
#include <string>

using namespace std;

// Forward declaration
template <typename T> class MyVector;
class Product;

class Supplier : public User {
private:
  int productIndex;

public:
  Supplier(string n, string s, int a, string l, string p, int prodIndex)
      : User(n, s, a, l, p), productIndex(prodIndex) {}

  Supplier(const Supplier &other) : User(other) {
    productIndex = other.productIndex;
  }

  Supplier &operator=(const Supplier &other) {
    if (this != &other) {
      User::operator=(other);
      productIndex = other.productIndex;
    }
    return *this;
  }

  IEntity *copy() const override { return new Supplier(*this); }

  void assign(const IEntity &other) override {
    const Supplier *s = dynamic_cast<const Supplier *>(&other);
    if (s) {
      User::assign(*s);
      productIndex = s->productIndex;
    }
  }

  void destroy() override { delete this; }

  void showInfo() const override;
  void performAction() override;

  bool isEqual(const IEntity &other) const override {
    const Supplier *s = dynamic_cast<const Supplier *>(&other);
    if (!s)
      return false;
    return login == s->login;
  }

  int getProductIndex() const { return productIndex; }
  void setProductIndex(int index) { productIndex = index; }

  void setProductName(string newName);
  void setProductPrice(int newPrice);
  class Product *getProduct() const;

  Supplier operator+(int qty) const;
  Supplier &operator+=(int qty);
};

#endif
