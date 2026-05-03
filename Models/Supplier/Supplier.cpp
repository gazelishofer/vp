#include "Supplier.h"
#include <iostream>
using namespace std;

void Supplier::showInfo() {
    cout << "[Supplier]" << endl;
    cout << "Name: " << getName() << endl;
    cout << "Surname: " << getSurname() << endl;
    cout << "Age: " << getAge() << endl;
    cout << "Login: " << getLogin() << endl;

    cout << "Product info:" << endl;
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
