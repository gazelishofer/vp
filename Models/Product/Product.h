#ifndef LR2_PRODUCT_H
#define LR2_PRODUCT_H

#include "../IEntity/IEntity.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Product : public IEntity {
private:
  string name;
  string type;
  int price;
  int amount;

public:
  Product() : name(""), type(""), price(0), amount(0) {}

  Product(string n, string t, int p, int a) {
    name = n;
    type = t;
    price = p;
    amount = a;
  }

  Product(const Product &other) {
    name = other.name;
    type = other.type;
    price = other.price;
    amount = other.amount;
  }

  Product &operator=(const Product &other) {
    if (this != &other) {
      name = other.name;
      type = other.type;
      price = other.price;
      amount = other.amount;
    }
    return *this;
  }

  IEntity *copy() const override { return new Product(*this); }

  void assign(const IEntity &other) override {
    const Product *p = dynamic_cast<const Product *>(&other);
    if (p) {
      name = p->name;
      type = p->type;
      price = p->price;
      amount = p->amount;
    }
  }

  void destroy() override { delete this; }

  void showInfo() const override {
    cout << "Name: " << name << endl;
    cout << "Type: " << type << endl;
    cout << "Price: " << price << endl;
    cout << "Amount: " << amount << endl;
  }

  bool isEqual(const IEntity &other) const override {
    const Product *p = dynamic_cast<const Product *>(&other);
    if (!p)
      return false;
    return name == p->name && type == p->type && price == p->price;
  }

  bool operator==(const Product &other) const {
    return name == other.name && type == other.type && price == other.price;
  }

  Product operator+(const Product &other) {
    if (*this == other) {
      return Product(name, type, price, amount + other.amount);
    }
    throw logic_error("Different products cannot be summed");
  }

  friend ostream &operator<<(ostream &out, const Product &p) {
    out << p.name << " " << p.type << " " << p.price << " " << p.amount;
    return out;
  }

  void setName(string n) { name = n; }
  void setType(string t) { type = t; }
  void setPrice(int p) { price = p; }
  void setAmount(int a) { amount = a; }
  string getName() const { return name; }
  string getType() const { return type; }
  int getPrice() const { return price; }
  int getAmount() const { return amount; }
};

#endif
