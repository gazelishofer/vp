#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "../Employee/Employee.h"
#include "../IEntity/IEntity.h"
#include "../Product/Product.h"
#include <iostream>
#include <string>

using namespace std;

class Production : public IEntity {
private:
  Product product;
  int quantity;
  string date;
  Employee *worker;

public:
  Production() : quantity(0), worker(nullptr) {}

  Production(Product p, int q, string d, Employee *w)
      : product(p), quantity(q), date(d), worker(w) {}

  Production(const Production &other)
      : product(other.product), quantity(other.quantity), date(other.date),
        worker(other.worker) {}

  Production &operator=(const Production &other) {
    if (this != &other) {
      product = other.product;
      quantity = other.quantity;
      date = other.date;
      worker = other.worker;
    }
    return *this;
  }

  IEntity *copy() const override { return new Production(*this); }

  void assign(const IEntity &other) override {
    const Production *p = dynamic_cast<const Production *>(&other);
    if (p) {
      product = p->product;
      quantity = p->quantity;
      date = p->date;
      worker = p->worker;
    }
  }

  void destroy() override { delete this; }

  void showInfo() const override {
    cout << "Product: " << product.getName() << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Date: " << date << endl;
    cout << "Worker: " << (worker ? worker->getName() : "Unknown") << endl;
  }

  bool isEqual(const IEntity &other) const override {
    const Production *p = dynamic_cast<const Production *>(&other);
    if (!p)
      return false;
    return product.getName() == p->product.getName() && date == p->date;
  }

  Product getProduct() const { return product; }
  int getQuantity() const { return quantity; }
  string getDate() const { return date; }
  Employee *getWorker() const { return worker; }
};

#endif
