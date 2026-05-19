#include "../Models/Employee/Employee.h"
#include "../Models/Product/Product.h"
#include "../Models/Supplier/Supplier.h"
#include "MyVector/MyVector.h"
#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include <iostream>
#include <string>

using namespace std;
using namespace XXX;

MyVector<Product> products;
MyVector<Supplier> suppliers;
MyVector<Employee> employees;

void showProducts(MyVector<Product> &products);
void showSuppliers(MyVector<Supplier> &suppliers);
void showEmployees(MyVector<Employee> &employees);
void showAllUsersPolymorphically(MyVector<Employee> &employees,
                                 MyVector<Supplier> &suppliers);

int handleAddMenu();
int handleEditMenu();
int handleDeleteMenu();
int handleShowMenu();
int handleMergeProducts();
int handleRestockSupplier();
int handleAdminLogout();
int handleAdminExit();
int handleUserLogout();
int handleUserExit();

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

int handleSortMenu();
int handleFilterMenu();

int handleSortProductsAsc();
int handleSortProductsDesc();
int handleSortSuppliersAsc();
int handleSortSuppliersDesc();
int handleSortEmployeesAsc();
int handleSortEmployeesDesc();

int handleFilterProductsByType();
int handleFilterSuppliersByProductName();
int handleFilterEmployeesByJob();

int main() {
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
            CMenuItem("Sort", handleSortMenu),
            CMenuItem("Filter", handleFilterMenu),
            CMenuItem("Logout", handleAdminLogout),
            CMenuItem("Exit", handleAdminExit)};
        CMenu adminMenu("===== ADMIN MENU =====", adminItems, 10);

        int choice = adminMenu.runCommand();

        if (choice == 9)
          loggedIn = false;
        else if (choice == 10)
          return 0;
      } else {
        CMenuItem userItems[] = {CMenuItem("Show", handleUserShow),
                                 CMenuItem("Logout", handleUserLogout),
                                 CMenuItem("Exit", handleUserExit)};
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
  return 1;
}

int handleEditMenu() {
  CMenuItem editItems[] = {CMenuItem("Product", handleEditProduct),
                           CMenuItem("Supplier", handleEditSupplier),
                           CMenuItem("Employee", handleEditEmployee)};
  CMenu editMenu("Edit", editItems, 3);
  editMenu.runCommand();
  return 2;
}

int handleDeleteMenu() {
  CMenuItem deleteItems[] = {CMenuItem("Product", handleDeleteProduct),
                             CMenuItem("Supplier", handleDeleteSupplier),
                             CMenuItem("Employee", handleDeleteEmployee)};
  CMenu deleteMenu("Delete", deleteItems, 3);
  deleteMenu.runCommand();
  return 3;
}

int handleShowMenu() {
  CMenuItem showItems[] = {
      CMenuItem("Products", handleShowProducts),
      CMenuItem("Suppliers", handleShowSuppliers),
      CMenuItem("Employees", handleShowEmployees),
      CMenuItem("All users polymorphically", handleShowAllUsers)};
  CMenu showMenu("Show", showItems, 4);
  showMenu.runCommand();
  return 4;
}

int handleSortMenu() {
  CMenuItem sortItems[] = {
      CMenuItem("Products by price (ascending)", handleSortProductsAsc),
      CMenuItem("Products by price (descending)", handleSortProductsDesc),
      CMenuItem("Suppliers by product name (A-Z)", handleSortSuppliersAsc),
      CMenuItem("Suppliers by product name (Z-A)", handleSortSuppliersDesc),
      CMenuItem("Employees by age (ascending)", handleSortEmployeesAsc),
      CMenuItem("Employees by age (descending)", handleSortEmployeesDesc)};
  CMenu sortMenu("===== SORT MENU =====", sortItems, 6);
  sortMenu.runCommand();
  return 7;
}

int handleFilterMenu() {
  CMenuItem filterItems[] = {
      CMenuItem("Filter products by type", handleFilterProductsByType),
      CMenuItem("Filter suppliers by product name",
                handleFilterSuppliersByProductName),
      CMenuItem("Filter employees by job", handleFilterEmployeesByJob)};
  CMenu filterMenu("===== FILTER MENU =====", filterItems, 3);
  filterMenu.runCommand();
  return 8;
}

int handleSortProductsAsc() {
  if (products.empty()) {
    cout << "No products to sort\n";
    return 1;
  }
  products.sort([](const Product &a,
                   const Product &b) { return a.getPrice() < b.getPrice(); },
                true);
  cout << "Products sorted by price (ascending):\n";
  showProducts(products);
  return 1;
}

int handleSortProductsDesc() {
  if (products.empty()) {
    cout << "No products to sort\n";
    return 2;
  }
  products.sort([](const Product &a,
                   const Product &b) { return a.getPrice() < b.getPrice(); },
                false);
  cout << "Products sorted by price (descending):\n";
  showProducts(products);
  return 2;
}

int handleSortSuppliersAsc() {
  if (suppliers.empty()) {
    cout << "No suppliers to sort\n";
    return 3;
  }
  suppliers.sort(
      [](const Supplier &a, const Supplier &b) {
        string nameA = a.getProduct() ? a.getProduct()->getName() : "";
        string nameB = b.getProduct() ? b.getProduct()->getName() : "";
        return nameA < nameB;
      },
      true);
  cout << "Suppliers sorted by product name (A-Z):\n";
  showSuppliers(suppliers);
  return 3;
}

int handleSortSuppliersDesc() {
  if (suppliers.empty()) {
    cout << "No suppliers to sort\n";
    return 4;
  }
  suppliers.sort(
      [](const Supplier &a, const Supplier &b) {
        string nameA = a.getProduct() ? a.getProduct()->getName() : "";
        string nameB = b.getProduct() ? b.getProduct()->getName() : "";
        return nameA < nameB;
      },
      false);
  cout << "Suppliers sorted by product name (Z-A):\n";
  showSuppliers(suppliers);
  return 4;
}

int handleSortEmployeesAsc() {
  if (employees.empty()) {
    cout << "No employees to sort\n";
    return 5;
  }
  employees.sort([](const Employee &a,
                    const Employee &b) { return a.getAge() < b.getAge(); },
                 true);
  cout << "Employees sorted by age (ascending):\n";
  showEmployees(employees);
  return 5;
}

int handleSortEmployeesDesc() {
  if (employees.empty()) {
    cout << "No employees to sort\n";
    return 6;
  }
  employees.sort([](const Employee &a,
                    const Employee &b) { return a.getAge() < b.getAge(); },
                 false);
  cout << "Employees sorted by age (descending):\n";
  showEmployees(employees);
  return 6;
}

int handleFilterProductsByType() {
  if (products.empty()) {
    cout << "No products to filter\n";
    return 1;
  }
  string type;
  cout << "Enter product type to filter: ";
  cin >> type;
  MyVector<Product> filtered = products.filter(
      [&type](const Product &p) { return p.getType() == type; });
  if (filtered.empty()) {
    cout << "No products of type '" << type << "'\n";
  } else {
    cout << "Filtered products (type = " << type << "):\n";
    for (size_t i = 0; i < filtered.getSize(); ++i) {
      cout << i + 1 << ". " << filtered[i].getName() << " "
           << filtered[i].getPrice() << " rub\n";
    }
  }
  return 1;
}

int handleFilterSuppliersByProductName() {
  if (suppliers.empty()) {
    cout << "No suppliers to filter\n";
    return 2;
  }
  string prodName;
  cout << "Enter product name to filter suppliers: ";
  cin >> prodName;
  MyVector<Supplier> filtered =
      suppliers.filter([&prodName](const Supplier &s) {
        return s.getProduct() && s.getProduct()->getName() == prodName;
      });
  if (filtered.empty()) {
    cout << "No suppliers for product '" << prodName << "'\n";
  } else {
    cout << "Filtered suppliers (product = " << prodName << "):\n";
    for (size_t i = 0; i < filtered.getSize(); ++i) {
      cout << i + 1 << ". " << filtered[i].getName() << " "
           << filtered[i].getSurname() << "\n";
    }
  }
  return 2;
}

int handleFilterEmployeesByJob() {
  if (employees.empty()) {
    cout << "No employees to filter\n";
    return 3;
  }
  string job;
  cout << "Enter job title to filter: ";
  cin >> job;
  MyVector<Employee> filtered =
      employees.filter([&job](const Employee &e) { return e.getJob() == job; });
  if (filtered.empty()) {
    cout << "No employees with job '" << job << "'\n";
  } else {
    cout << "Filtered employees (job = " << job << "):\n";
    for (size_t i = 0; i < filtered.getSize(); ++i) {
      cout << i + 1 << ". " << filtered[i].getName() << " "
           << filtered[i].getSurname() << ", age " << filtered[i].getAge()
           << "\n";
    }
  }
  return 3;
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
  return 1;
}

int handleAddSupplier() {
  if (products.empty()) {
    cout << "Add product first\n";
    return 2;
  }

  showProducts(products);

  int prodIndex;
  cout << "Choose product number for this supplier: ";
  cin >> prodIndex;
  prodIndex--;

  if (prodIndex < 0 || prodIndex >= static_cast<int>(products.getSize())) {
    cout << "Wrong product number\n";
    return 2;
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
  return 2;
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
  return 3;
}

int handleEditProduct() {
  showProducts(products);

  int index;
  cout << "Choose product number: ";
  cin >> index;
  index--;

  if (index < 0 || index >= static_cast<int>(products.getSize())) {
    cout << "Wrong number\n";
    return 1;
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
  return 1;
}

int handleEditSupplier() {
  showSuppliers(suppliers);

  int index;
  cout << "Choose supplier number: ";
  cin >> index;
  index--;

  if (index < 0 || index >= static_cast<int>(suppliers.getSize())) {
    cout << "Wrong number\n";
    return 2;
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
  return 2;
}

int handleEditEmployee() {
  showEmployees(employees);

  int index;
  cout << "Choose employee number: ";
  cin >> index;
  index--;

  if (index < 0 || index >= static_cast<int>(employees.getSize())) {
    cout << "Wrong number\n";
    return 3;
  }

  string job;

  cout << "New job: ";
  cin >> job;

  employees[index].setJob(job);

  cout << "Updated\n";
  return 3;
}

int handleDeleteProduct() {
  showProducts(products);

  int index;
  cout << "Choose product number: ";
  cin >> index;
  index--;

  if (index >= 0 && index < static_cast<int>(products.getSize())) {
    Product *base = products.getData();
    MyVector<int> oldIdx;
    for (size_t i = 0; i < suppliers.getSize(); ++i) {
      Product *p = suppliers[i].getProduct();
      if (p)
        oldIdx.push_back(static_cast<int>(p - base));
      else
        oldIdx.push_back(-1);
    }

    products.erase(index);
    for (size_t i = 0; i < suppliers.getSize(); ++i) {
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
  return 1;
}

int handleDeleteSupplier() {
  showSuppliers(suppliers);

  int index;
  cout << "Choose supplier number: ";
  cin >> index;
  index--;

  if (index >= 0 && index < static_cast<int>(suppliers.getSize())) {
    suppliers.erase(index);
    cout << "Deleted\n";
  }
  return 2;
}

int handleDeleteEmployee() {
  showEmployees(employees);

  int index;
  cout << "Choose employee number: ";
  cin >> index;
  index--;

  if (index >= 0 && index < static_cast<int>(employees.getSize())) {
    employees.erase(index);
    cout << "Deleted\n";
  }
  return 3;
}

int handleShowProducts() {
  showProducts(products);
  return 1;
}

int handleShowSuppliers() {
  showSuppliers(suppliers);
  return 2;
}

int handleShowEmployees() {
  showEmployees(employees);
  return 3;
}

int handleShowAllUsers() {
  showAllUsersPolymorphically(employees, suppliers);
  return 4;
}

int handleMergeProducts() {
  if (products.getSize() < 2) {
    cout << "Need at least 2 products\n";
    return 5;
  }

  showProducts(products);

  int first, second;

  cout << "Choose first product number: ";
  cin >> first;

  cout << "Choose second product number: ";
  cin >> second;

  first--;
  second--;

  if (first < 0 || first >= static_cast<int>(products.getSize()) ||
      second < 0 || second >= static_cast<int>(products.getSize())) {
    cout << "Wrong numbers\n";
    return 5;
  }

  if (!(products[first] == products[second])) {
    cout << "Cannot sum different products\n";
    return 5;
  }

  Product *base = products.getData();
  MyVector<int> oldIdx;
  for (size_t i = 0; i < suppliers.getSize(); ++i) {
    Product *p = suppliers[i].getProduct();
    if (p)
      oldIdx.push_back(static_cast<int>(p - base));
    else
      oldIdx.push_back(-1);
  }

  products[first] = products[first] + products[second];
  products.erase(second);

  int newFirstIdx = (first > second) ? first - 1 : first;

  for (size_t i = 0; i < suppliers.getSize(); ++i) {
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

  return 5;
}

int handleRestockSupplier() {
  if (suppliers.empty()) {
    cout << "No suppliers available\n";
    return 6;
  }

  showSuppliers(suppliers);

  int supIndex, qty;

  cout << "Choose supplier number: ";
  cin >> supIndex;
  supIndex--;

  if (supIndex < 0 || supIndex >= static_cast<int>(suppliers.getSize())) {
    cout << "Wrong supplier number\n";
    return 6;
  }

  if (!suppliers[supIndex].getProduct()) {
    cout << "Supplier has no linked product\n";
    return 6;
  }

  cout << "Quantity to add: ";
  cin >> qty;

  suppliers[supIndex] = suppliers[supIndex] + qty;

  cout << "Stock updated. Product now:\n";
  cout << *suppliers[supIndex].getProduct() << endl;
  return 6;
}

int handleAdminLogout() { return 9; }
int handleAdminExit() { return 10; }
int handleUserLogout() { return 2; }
int handleUserExit() { return 3; }

int handleUserShow() {
  handleShowMenu();
  return 1;
}

void showProducts(MyVector<Product> &products) {
  if (products.empty()) {
    cout << "No products available\n";
    return;
  }

  for (int i = 0; i < static_cast<int>(products.getSize()); i++) {
    cout << i + 1 << ". " << products[i].getName() << " "
         << products[i].getType() << " " << products[i].getPrice() << " "
         << products[i].getAmount() << endl;
  }
}

void showSuppliers(MyVector<Supplier> &suppliers) {
  if (suppliers.empty()) {
    cout << "No suppliers available\n";
    return;
  }

  for (int i = 0; i < static_cast<int>(suppliers.getSize()); i++) {
    cout << i + 1 << ". ";
    suppliers[i].showInfo();
  }
}

void showEmployees(MyVector<Employee> &employees) {
  if (employees.empty()) {
    cout << "No employees available\n";
    return;
  }

  for (int i = 0; i < static_cast<int>(employees.getSize()); i++) {
    cout << i + 1 << ". ";
    employees[i].showInfo();
  }
}

void showAllUsersPolymorphically(MyVector<Employee> &employees,
                                 MyVector<Supplier> &suppliers) {
  MyVector<User *> users;

  for (size_t i = 0; i < employees.getSize(); i++) {
    users.push_back(&employees[i]);
  }

  for (size_t i = 0; i < suppliers.getSize(); i++) {
    users.push_back(&suppliers[i]);
  }

  if (users.empty()) {
    cout << "No users available\n";
    return;
  }

  for (size_t i = 0; i < users.getSize(); i++) {
    users[i]->showInfo();
    users[i]->performAction();
    cout << endl;
  }
}
