
#ifndef LR2_CLASS1_H
#define LR2_CLASS1_H
#include "../Product/Product.h"
#include "../User/User.h"

class Supplier : public User {

private:
  Product *product;

public:
  Supplier(string n, string s, int a, string l, string p, Product *pr)
      : User(n, s, a, l, p), product(pr) {}

  void showInfo() override;
  void performAction() override;

  Supplier &operator+=(int qty) {
    if (product) {
      product->setAmount(product->getAmount() + qty);
    }
    return *this;
  }

  Supplier operator+(int qty) {
    if (product) {
      product->setAmount(product->getAmount() + qty);
    }
    return *this;
  }

  Product *getProduct() const { return product; }

  void setProduct(Product *pr) { product = pr; }

  void setProductName(string n) {
    if (product)
      product->setName(n);
  }

  void setProductType(string t) {
    if (product)
      product->setType(t);
  }

  void setProductPrice(int p) {
    if (product)
      product->setPrice(p);
  }

  void setProductAmount(int a) {
    if (product)
      product->setAmount(a);
  }

  string getProductName() { return product ? product->getName() : ""; }

  string getProductType() { return product ? product->getType() : ""; }

  int getProductPrice() { return product ? product->getPrice() : 0; }

  int getProductAmount() { return product ? product->getAmount() : 0; }
};

#endif // LR2_CLASS1_H
