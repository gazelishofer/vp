#ifndef SALE_H
#define SALE_H

#include "../IEntity/IEntity.h"
#include "../Product/Product.h"
#include <iostream>
#include <string>

using namespace std;

class Sale : public IEntity {
private:
  Product product;
  int quantity;
  string date;
  int totalPrice;
  string buyer;
  string supplierName;

public:
  Sale() : quantity(0), totalPrice(0) {}

  Sale(Product p, int q, string d, int price, string b, string s)
      : product(p), quantity(q), date(d), totalPrice(price), buyer(b),
        supplierName(s) {}

  Sale(const Sale &other)
      : product(other.product), quantity(other.quantity), date(other.date),
        totalPrice(other.totalPrice), buyer(other.buyer),
        supplierName(other.supplierName) {}

  Sale &operator=(const Sale &other) {
    if (this != &other) {
      product = other.product;
      quantity = other.quantity;
      date = other.date;
      totalPrice = other.totalPrice;
      buyer = other.buyer;
      supplierName = other.supplierName;
    }
    return *this;
  }

  IEntity *copy() const override { return new Sale(*this); }

  void assign(const IEntity &other) override {
    const Sale *s = dynamic_cast<const Sale *>(&other);
    if (s) {
      product = s->product;
      quantity = s->quantity;
      date = s->date;
      totalPrice = s->totalPrice;
      buyer = s->buyer;
      supplierName = s->supplierName;
    }
  }

  void destroy() override { delete this; }

  void showInfo() const override {
    cout << "Product: " << product.getName() << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Date: " << date << endl;
    cout << "Total price: " << totalPrice << endl;
    cout << "Buyer: " << buyer << endl;
    cout << "Supplier: " << supplierName << endl;
  }

  bool isEqual(const IEntity &other) const override {
    const Sale *s = dynamic_cast<const Sale *>(&other);
    if (!s)
      return false;
    return product.getName() == s->product.getName() && date == s->date;
  }

  Product getProduct() const { return product; }
  int getQuantity() const { return quantity; }
  string getDate() const { return date; }
  int getTotalPrice() const { return totalPrice; }
  string getBuyer() const { return buyer; }
  string getSupplierName() const { return supplierName; }
};

#endif
