#include "../Models/Employee/Employee.h"
#include "../Models/Product/Product.h"
#include "../Models/Supplier/Supplier.h"
#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace XXX;

vector<Product> products;
vector<Supplier> suppliers;
vector<Employee> employees;

void showProducts(vector<Product> &products);
void showSuppliers(vector<Supplier> &suppliers);
void showEmployees(vector<Employee> &employees);
void showAllUsersPolymorphically(vector<Employee> &employees,
                                 vector<Supplier> &suppliers);

int handleAddMenu();
int handleEditMenu();
int handleDeleteMenu();
int handleShowMenu();
int handleMergeProducts();
int handleRestockSupplier();
int handleLogout();
int handleExit();

int handleAddProduct();
int handleAddSupplier();
int handleAddEmployee();

int handleEditProduct();
int handleEditSupplier();
int handleEditEmployee();

int handleDeleteProduct();
int handleDeleteSupplier();
int handleDeleteEmployee();

int handleShowProducts();
int handleShowSuppliers();
int handleShowEmployees();
int handleShowAllUsers();

int handleUserShow();

int main() {
  products.reserve(1000);

  while (true) {
    CMenuItem authItems[] = {
        CMenuItem("Login as admin", []() -> int { return 1; }),
        CMenuItem("Login as user", []() -> int { return 2; }),
        CMenuItem("Exit", []() -> int { return 3; })};
    CMenu authMenu("===== AUTHORIZATION =====", authItems, 3);

    int roleChoice = authMenu.runCommand();

    if (roleChoice == 0 || roleChoice == 3)
      return 0;

    string login, password;

    cout << "Login: ";
    cin >> login;

    cout << "Password: ";
    cin >> password;

    bool isAdmin = false;

    if (roleChoice == 1) {
      if (login == "admin" && password == "123") {
        isAdmin = true;
        cout << "Logged in as ADMIN\n";
      } else {
        cout << "Wrong admin login or password\n";
        continue;
      }
    } else if (roleChoice == 2) {
      if (login == "user" && password == "111") {
        cout << "Logged in as USER\n";
      } else {
        cout << "Wrong user login or password\n";
        continue;
      }
    }

    bool loggedIn = true;

    while (loggedIn) {
      if (isAdmin) {
        CMenuItem adminItems[] = {
            CMenuItem("Add", handleAddMenu),
            CMenuItem("Edit", handleEditMenu),
            CMenuItem("Delete", handleDeleteMenu),
            CMenuItem("Show", handleShowMenu),
            CMenuItem("Merge products (operator+)", handleMergeProducts),
            CMenuItem("Restock via supplier (operator+)",
                      handleRestockSupplier),
            CMenuItem("Logout", handleLogout),
            CMenuItem("Exit", handleExit)};
        CMenu adminMenu("===== ADMIN MENU =====", adminItems, 8);

        int choice = adminMenu.runCommand();

        if (choice == 7)
          loggedIn = false;
        else if (choice == 8)
          return 0;
      } else {
        CMenuItem userItems[] = {CMenuItem("Show", handleUserShow),
                                 CMenuItem("Logout", handleLogout),
                                 CMenuItem("Exit", handleExit)};
        CMenu userMenu("===== USER MENU =====", userItems, 3);

        int choice = userMenu.runCommand();

        if (choice == 2)
          loggedIn = false;
        else if (choice == 3)
          return 0;
      }
    }
  }
}

int handleAddMenu() {
  CMenuItem addItems[] = {CMenuItem("Product", handleAddProduct),
                          CMenuItem("Supplier", handleAddSupplier),
                          CMenuItem("Employee", handleAddEmployee)};
  CMenu addMenu("Add", addItems, 3);
  addMenu.runCommand();
  return 0;
}

int handleEditMenu() {
  CMenuItem editItems[] = {CMenuItem("Product", handleEditProduct),
                           CMenuItem("Supplier", handleEditSupplier),
                           CMenuItem("Employee", handleEditEmployee)};
  CMenu editMenu("Edit", editItems, 3);
  editMenu.runCommand();
  return 0;
}

int handleDeleteMenu() {
  CMenuItem deleteItems[] = {CMenuItem("Product", handleDeleteProduct),
                             CMenuItem("Supplier", handleDeleteSupplier),
                             CMenuItem("Employee", handleDeleteEmployee)};
  CMenu deleteMenu("Delete", deleteItems, 3);
  deleteMenu.runCommand();
  return 0;
}

int handleShowMenu() {
  CMenuItem showItems[] = {
      CMenuItem("Products", handleShowProducts),
      CMenuItem("Suppliers", handleShowSuppliers),
      CMenuItem("Employees", handleShowEmployees),
      CMenuItem("All users polymorphically", handleShowAllUsers)};
  CMenu showMenu("Show", showItems, 4);
  showMenu.runCommand();
  return 0;
}

int handleAddProduct() {
  string name, productType;
  int price, amount;

  cout << "Name: ";
  cin >> name;

  cout << "Type: ";
  cin >> productType;

  cout << "Price: ";
  cin >> price;

  cout << "Amount: ";
  cin >> amount;

  products.push_back(Product(name, productType, price, amount));
  cout << "Product added\n";
  return 0;
}

int handleAddSupplier() {
  if (products.empty()) {
    cout << "Add product first\n";
    return 0;
  }

  showProducts(products);

  int prodIndex;
  cout << "Choose product number for this supplier: ";
  cin >> prodIndex;
  prodIndex--;

  if (prodIndex < 0 || prodIndex >= static_cast<int>(products.size())) {
    cout << "Wrong product number\n";
    return 0;
  }

  string name, surname, login2, password2;
  int age;

  cout << "Name: ";
  cin >> name;

  cout << "Surname: ";
  cin >> surname;

  cout << "Age: ";
  cin >> age;

  cout << "Login: ";
  cin >> login2;

  cout << "Password: ";
  cin >> password2;

  suppliers.push_back(
      Supplier(name, surname, age, login2, password2, &products[prodIndex]));

  cout << "Supplier added (linked to product " << products[prodIndex].getName()
       << ")\n";
  return 0;
}

int handleAddEmployee() {
  string name, surname, login2, password2, job;
  int age;

  cout << "Name: ";
  cin >> name;

  cout << "Surname: ";
  cin >> surname;

  cout << "Age: ";
  cin >> age;

  cout << "Login: ";
  cin >> login2;

  cout << "Password: ";
  cin >> password2;

  cout << "Job: ";
  cin >> job;

  employees.push_back(Employee(name, surname, age, login2, password2, job));

  cout << "Employee added\n";
  return 0;
}

int handleEditProduct() {
  showProducts(products);

  int index;
  cout << "Choose product number: ";
  cin >> index;
  index--;

  if (index < 0 || index >= static_cast<int>(products.size())) {
    cout << "Wrong number\n";
    return 0;
  }

  string name, productType;
  int price, amount;

  cout << "New name: ";
  cin >> name;

  cout << "New type: ";
  cin >> productType;

  cout << "New price: ";
  cin >> price;

  cout << "New amount: ";
  cin >> amount;

  products[index].setName(name);
  products[index].setType(productType);
  products[index].setPrice(price);
  products[index].setAmount(amount);

  cout << "Updated\n";
  return 0;
}

int handleEditSupplier() {
  showSuppliers(suppliers);

  int index;
  cout << "Choose supplier number: ";
  cin >> index;
  index--;

  if (index < 0 || index >= static_cast<int>(suppliers.size())) {
    cout << "Wrong number\n";
    return 0;
  }

  string productName;
  int productPrice;

  cout << "New product name: ";
  cin >> productName;

  cout << "New product price: ";
  cin >> productPrice;

  suppliers[index].setProductName(productName);
  suppliers[index].setProductPrice(productPrice);

  cout << "Updated\n";
  return 0;
}

int handleEditEmployee() {
  showEmployees(employees);

  int index;
  cout << "Choose employee number: ";
  cin >> index;
  index--;

  if (index < 0 || index >= static_cast<int>(employees.size())) {
    cout << "Wrong number\n";
    return 0;
  }

  string job;

  cout << "New job: ";
  cin >> job;

  employees[index].setJob(job);

  cout << "Updated\n";
  return 0;
}

int handleDeleteProduct() {
  showProducts(products);

  int index;
  cout << "Choose product number: ";
  cin >> index;
  index--;

  if (index >= 0 && index < static_cast<int>(products.size())) {
    Product *base = products.data();
    vector<int> oldIdx(suppliers.size(), -1);
    for (size_t i = 0; i < suppliers.size(); ++i) {
      Product *p = suppliers[i].getProduct();
      if (p)
        oldIdx[i] = static_cast<int>(p - base);
    }

    products.erase(products.begin() + index);

    for (size_t i = 0; i < suppliers.size(); ++i) {
      int idx = oldIdx[i];
      if (idx < 0)
        continue;
      if (idx == index) {
        suppliers[i].setProduct(nullptr);
      } else if (idx > index) {
        suppliers[i].setProduct(&products[idx - 1]);
      }
    }
    cout << "Deleted\n";
  }
  return 0;
}

int handleDeleteSupplier() {
  showSuppliers(suppliers);

  int index;
  cout << "Choose supplier number: ";
  cin >> index;
  index--;

  if (index >= 0 && index < static_cast<int>(suppliers.size())) {
    suppliers.erase(suppliers.begin() + index);
    cout << "Deleted\n";
  }
  return 0;
}

int handleDeleteEmployee() {
  showEmployees(employees);

  int index;
  cout << "Choose employee number: ";
  cin >> index;
  index--;

  if (index >= 0 && index < static_cast<int>(employees.size())) {
    employees.erase(employees.begin() + index);
    cout << "Deleted\n";
  }
  return 0;
}

int handleShowProducts() {
  showProducts(products);
  return 0;
}

int handleShowSuppliers() {
  showSuppliers(suppliers);
  return 0;
}

int handleShowEmployees() {
  showEmployees(employees);
  return 0;
}

int handleShowAllUsers() {
  showAllUsersPolymorphically(employees, suppliers);
  return 0;
}

int handleMergeProducts() {
  if (products.size() < 2) {
    cout << "Need at least 2 products\n";
    return 0;
  }

  showProducts(products);

  int first, second;

  cout << "Choose first product number: ";
  cin >> first;

  cout << "Choose second product number: ";
  cin >> second;

  first--;
  second--;

  if (first < 0 || first >= static_cast<int>(products.size()) || second < 0 ||
      second >= static_cast<int>(products.size())) {
    cout << "Wrong numbers\n";
    return 0;
  }

  if (!(products[first] == products[second])) {
    cout << "Cannot sum different products\n";
    return 0;
  }

  Product *base = products.data();
  vector<int> oldIdx(suppliers.size(), -1);
  for (size_t i = 0; i < suppliers.size(); ++i) {
    Product *p = suppliers[i].getProduct();
    if (p)
      oldIdx[i] = static_cast<int>(p - base);
  }

  products[first] = products[first] + products[second];
  products.erase(products.begin() + second);

  int newFirstIdx = (first > second) ? first - 1 : first;

  for (size_t i = 0; i < suppliers.size(); ++i) {
    int idx = oldIdx[i];
    if (idx < 0)
      continue;
    if (idx == second) {
      suppliers[i].setProduct(&products[newFirstIdx]);
    } else if (idx > second) {
      suppliers[i].setProduct(&products[idx - 1]);
    }
  }

  cout << "Products merged successfully:\n";
  cout << products[newFirstIdx] << endl;

  return 0;
}

int handleRestockSupplier() {
  if (suppliers.empty()) {
    cout << "No suppliers available\n";
    return 0;
  }

  showSuppliers(suppliers);

  int supIndex, qty;

  cout << "Choose supplier number: ";
  cin >> supIndex;
  supIndex--;

  if (supIndex < 0 || supIndex >= static_cast<int>(suppliers.size())) {
    cout << "Wrong supplier number\n";
    return 0;
  }

  if (!suppliers[supIndex].getProduct()) {
    cout << "Supplier has no linked product\n";
    return 0;
  }

  cout << "Quantity to add: ";
  cin >> qty;

  suppliers[supIndex] = suppliers[supIndex] + qty;

  cout << "Stock updated. Product now:\n";
  cout << *suppliers[supIndex].getProduct() << endl;
  return 0;
}

int handleLogout() { return 7; }

int handleExit() { return 8; }

int handleUserShow() {
  handleShowMenu();
  return 0;
}

void showProducts(vector<Product> &products) {
  if (products.empty()) {
    cout << "No products available\n";
    return;
  }

  for (int i = 0; i < static_cast<int>(products.size()); i++) {
    cout << i + 1 << ". " << products[i].getName() << " "
         << products[i].getType() << " " << products[i].getPrice() << " "
         << products[i].getAmount() << endl;
  }
}

void showSuppliers(vector<Supplier> &suppliers) {
  if (suppliers.empty()) {
    cout << "No suppliers available\n";
    return;
  }

  for (int i = 0; i < static_cast<int>(suppliers.size()); i++) {
    cout << i + 1 << ". ";
    suppliers[i].showInfo();
  }
}

void showEmployees(vector<Employee> &employees) {
  if (employees.empty()) {
    cout << "No employees available\n";
    return;
  }

  for (int i = 0; i < static_cast<int>(employees.size()); i++) {
    cout << i + 1 << ". ";
    employees[i].showInfo();
  }
}

void showAllUsersPolymorphically(vector<Employee> &employees,
                                 vector<Supplier> &suppliers) {
  vector<User *> users;

  for (auto &employee : employees) {
    users.push_back(&employee);
  }

  for (auto &supplier : suppliers) {
    users.push_back(&supplier);
  }

  if (users.empty()) {
    cout << "No users available\n";
    return;
  }

  for (auto item : users) {
    item->showInfo();
    item->performAction();
    cout << endl;
  }
}
