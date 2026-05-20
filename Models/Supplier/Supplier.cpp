#include "Supplier.h"
#include "../../TestMenu/MyVector/MyVector.h"
#include "../Product/Product.h"
#include <iostream>

using namespace std;

extern MyVector<Product> products;

void Supplier::showInfo() const {
  cout << "[Supplier]" << endl;
  cout << "Name: " << getName() << endl;
  cout << "Surname: " << getSurname() << endl;
  cout << "Age: " << getAge() << endl;
  cout << "Login: " << getLogin() << endl;
  cout << "Product info:" << endl;

  Product *product = getProduct();
  if (product) {
    cout << "  Name: " << product->getName() << endl;
    cout << "  Type: " << product->getType() << endl;
    cout << "  Price: " << product->getPrice() << endl;
    cout << "  Amount: " << product->getAmount() << endl;
  } else {
    cout << "  (no product)" << endl;
  }
}

void Supplier::performAction() {
  cout << "Supplier delivers products..." << endl;
}

Product *Supplier::getProduct() const {
  if (productIndex >= 0 &&
      productIndex < static_cast<int>(products.getSize())) {
    return &products[productIndex];
  }
  return nullptr;
}

void Supplier::setProductName(string newName) {
  Product *p = getProduct();
  if (p)
    p->setName(newName);
}

void Supplier::setProductPrice(int newPrice) {
  Product *p = getProduct();
  if (p)
    p->setPrice(newPrice);
}

Supplier Supplier::operator+(int qty) const {
  Supplier result = *this;
  Product *p = result.getProduct();
  if (p) {
    p->setAmount(p->getAmount() + qty);
  }
  return result;
}

Supplier &Supplier::operator+=(int qty) {
  Product *p = getProduct();
  if (p) {
    p->setAmount(p->getAmount() + qty);
  }
  return *this;
}
