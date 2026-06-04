#include "../Models/Employee/Employee.h"
#include "../Models/Product/Product.h"
#include "../Models/Production/Production.h"
#include "../Models/Sale/Sale.h"
#include "../Models/Supplier/Supplier.h"
#include "MyVector/MyVector.h"
#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;
using namespace XXX;

MyVector<Product> products;
MyVector<Supplier> suppliers;
MyVector<Employee> employees;
MyVector<Production> productions;
MyVector<Sale> sales;

bool isValidDate(const string &date) {
  if (date.length() != 10)
    return false;
  if (date[4] != '-' || date[7] != '-')
    return false;

  for (int i = 0; i < 10; i++) {
    if (i == 4 || i == 7)
      continue;
    if (date[i] < '0' || date[i] > '9')
      return false;
  }

  int year = stoi(date.substr(0, 4));
  int month = stoi(date.substr(5, 2));
  int day = stoi(date.substr(8, 2));

  if (year < 2000 || year > 2100)
    return false;
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;

  if (month == 2) {
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (day > (isLeap ? 29 : 28))
      return false;
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    if (day > 30)
      return false;
  }

  return true;
}

bool isOnlyLetters(const string &str) {
  if (str.empty())
    return false;
  for (char c : str) {
    if (!isalpha(static_cast<unsigned char>(c)) && c != ' ' && c != '-') {
      return false;
    }
  }
  return true;
}

int safeStoi(const string &str) {
  try {
    size_t pos;
    int val = stoi(str, &pos);
    if (pos != str.length())
      throw invalid_argument("Trailing characters");
    return val;
  } catch (const exception &e) {
    throw runtime_error("Invalid number in file: " + str);
  }
}

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
int handleUserSortMenu();
int handleUserProductFilterMenu();
int handleUserSupplierFilterMenu();
int handleUserEmployeeFilterMenu();
int handleAdminProductFilterMenu();
int handleAdminSupplierFilterMenu();
int handleAdminEmployeeFilterMenu();
int handleUserLoadFile();

int handleSortMenu();
int handleFilterMenu();

int handleSortProductsByNameAsc();
int handleSortProductsByNameDesc();
int handleSortProductsByTypeAsc();
int handleSortProductsByTypeDesc();
int handleSortProductsByPriceAsc();
int handleSortProductsByPriceDesc();
int handleSortProductsByAmountAsc();
int handleSortProductsByAmountDesc();
int handleSortSuppliersByNameAsc();
int handleSortSuppliersByNameDesc();
int handleSortSuppliersBySurnameAsc();
int handleSortSuppliersBySurnameDesc();
int handleSortSuppliersByAgeAsc();
int handleSortSuppliersByAgeDesc();
int handleSortSuppliersByProductNameAsc();
int handleSortSuppliersByProductNameDesc();
int handleSortEmployeesByNameAsc();
int handleSortEmployeesByNameDesc();
int handleSortEmployeesBySurnameAsc();
int handleSortEmployeesBySurnameDesc();
int handleSortEmployeesByAgeAsc();
int handleSortEmployeesByAgeDesc();
int handleSortEmployeesByJobAsc();
int handleSortEmployeesByJobDesc();

int handleFilterProductsByName();
int handleFilterProductsByType();
int handleFilterProductsByPrice();
int handleFilterProductsByAmount();
int handleFilterSuppliersByName();
int handleFilterSuppliersBySurname();
int handleFilterSuppliersByAge();
int handleFilterSuppliersByProductName();
int handleFilterEmployeesByName();
int handleFilterEmployeesBySurname();
int handleFilterEmployeesByAge();
int handleFilterEmployeesByJob();

int handleProductionMenu();
int handleSalesMenu();
int handleReportsMenu();
int handleAddProduction();
int handleAddSale();
int handleShowProductions();
int handleShowSales();
int handleGenerateReport();
int handleSaveToCustomFile();
int handleLoadFromCustomFile();
void saveToFile(const string &filename);
void loadFromFile(const string &filename);

int handleUserLoadFile() {
  handleLoadFromCustomFile();
  return 0;
}

int handleSortProductsByNameAsc() {
  try {
    if (products.empty())
      throw runtime_error("No products to sort");
    products.sort([](const Product &a,
                     const Product &b) { return a.getName() < b.getName(); },
                  true);
    cout << "Products sorted by name (A-Z):\n";
    showProducts(products);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortProductsByNameDesc() {
  try {
    if (products.empty())
      throw runtime_error("No products to sort");
    products.sort([](const Product &a,
                     const Product &b) { return a.getName() < b.getName(); },
                  false);
    cout << "Products sorted by name (Z-A):\n";
    showProducts(products);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortProductsByTypeAsc() {
  try {
    if (products.empty())
      throw runtime_error("No products to sort");
    products.sort([](const Product &a,
                     const Product &b) { return a.getType() < b.getType(); },
                  true);
    cout << "Products sorted by type (A-Z):\n";
    showProducts(products);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortProductsByTypeDesc() {
  try {
    if (products.empty())
      throw runtime_error("No products to sort");
    products.sort([](const Product &a,
                     const Product &b) { return a.getType() < b.getType(); },
                  false);
    cout << "Products sorted by type (Z-A):\n";
    showProducts(products);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortProductsByPriceAsc() {
  try {
    if (products.empty())
      throw runtime_error("No products to sort");
    products.sort([](const Product &a,
                     const Product &b) { return a.getPrice() < b.getPrice(); },
                  true);
    cout << "Products sorted by price (ascending):\n";
    showProducts(products);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortProductsByPriceDesc() {
  try {
    if (products.empty())
      throw runtime_error("No products to sort");
    products.sort([](const Product &a,
                     const Product &b) { return a.getPrice() < b.getPrice(); },
                  false);
    cout << "Products sorted by price (descending):\n";
    showProducts(products);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortProductsByAmountAsc() {
  try {
    if (products.empty())
      throw runtime_error("No products to sort");
    products.sort(
        [](const Product &a, const Product &b) {
          return a.getAmount() < b.getAmount();
        },
        true);
    cout << "Products sorted by amount (ascending):\n";
    showProducts(products);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortProductsByAmountDesc() {
  try {
    if (products.empty())
      throw runtime_error("No products to sort");
    products.sort(
        [](const Product &a, const Product &b) {
          return a.getAmount() < b.getAmount();
        },
        false);
    cout << "Products sorted by amount (descending):\n";
    showProducts(products);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortSuppliersByNameAsc() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to sort");
    suppliers.sort([](const Supplier &a,
                      const Supplier &b) { return a.getName() < b.getName(); },
                   true);
    cout << "Suppliers sorted by name (A-Z):\n";
    showSuppliers(suppliers);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortSuppliersByNameDesc() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to sort");
    suppliers.sort([](const Supplier &a,
                      const Supplier &b) { return a.getName() < b.getName(); },
                   false);
    cout << "Suppliers sorted by name (Z-A):\n";
    showSuppliers(suppliers);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortSuppliersBySurnameAsc() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to sort");
    suppliers.sort(
        [](const Supplier &a, const Supplier &b) {
          return a.getSurname() < b.getSurname();
        },
        true);
    cout << "Suppliers sorted by surname (A-Z):\n";
    showSuppliers(suppliers);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortSuppliersBySurnameDesc() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to sort");
    suppliers.sort(
        [](const Supplier &a, const Supplier &b) {
          return a.getSurname() < b.getSurname();
        },
        false);
    cout << "Suppliers sorted by surname (Z-A):\n";
    showSuppliers(suppliers);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortSuppliersByAgeAsc() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to sort");
    suppliers.sort([](const Supplier &a,
                      const Supplier &b) { return a.getAge() < b.getAge(); },
                   true);
    cout << "Suppliers sorted by age (ascending):\n";
    showSuppliers(suppliers);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortSuppliersByAgeDesc() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to sort");
    suppliers.sort([](const Supplier &a,
                      const Supplier &b) { return a.getAge() < b.getAge(); },
                   false);
    cout << "Suppliers sorted by age (descending):\n";
    showSuppliers(suppliers);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortSuppliersByProductNameAsc() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to sort");
    suppliers.sort(
        [](const Supplier &a, const Supplier &b) {
          string nameA = a.getProduct() ? a.getProduct()->getName() : "";
          string nameB = b.getProduct() ? b.getProduct()->getName() : "";
          return nameA < nameB;
        },
        true);
    cout << "Suppliers sorted by product name (A-Z):\n";
    showSuppliers(suppliers);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortSuppliersByProductNameDesc() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to sort");
    suppliers.sort(
        [](const Supplier &a, const Supplier &b) {
          string nameA = a.getProduct() ? a.getProduct()->getName() : "";
          string nameB = b.getProduct() ? b.getProduct()->getName() : "";
          return nameA < nameB;
        },
        false);
    cout << "Suppliers sorted by product name (Z-A):\n";
    showSuppliers(suppliers);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortEmployeesByNameAsc() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to sort");
    employees.sort([](const Employee &a,
                      const Employee &b) { return a.getName() < b.getName(); },
                   true);
    cout << "Employees sorted by name (A-Z):\n";
    showEmployees(employees);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortEmployeesByNameDesc() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to sort");
    employees.sort([](const Employee &a,
                      const Employee &b) { return a.getName() < b.getName(); },
                   false);
    cout << "Employees sorted by name (Z-A):\n";
    showEmployees(employees);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortEmployeesBySurnameAsc() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to sort");
    employees.sort(
        [](const Employee &a, const Employee &b) {
          return a.getSurname() < b.getSurname();
        },
        true);
    cout << "Employees sorted by surname (A-Z):\n";
    showEmployees(employees);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortEmployeesBySurnameDesc() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to sort");
    employees.sort(
        [](const Employee &a, const Employee &b) {
          return a.getSurname() < b.getSurname();
        },
        false);
    cout << "Employees sorted by surname (Z-A):\n";
    showEmployees(employees);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortEmployeesByAgeAsc() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to sort");
    employees.sort([](const Employee &a,
                      const Employee &b) { return a.getAge() < b.getAge(); },
                   true);
    cout << "Employees sorted by age (ascending):\n";
    showEmployees(employees);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortEmployeesByAgeDesc() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to sort");
    employees.sort([](const Employee &a,
                      const Employee &b) { return a.getAge() < b.getAge(); },
                   false);
    cout << "Employees sorted by age (descending):\n";
    showEmployees(employees);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortEmployeesByJobAsc() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to sort");
    employees.sort([](const Employee &a,
                      const Employee &b) { return a.getJob() < b.getJob(); },
                   true);
    cout << "Employees sorted by job (A-Z):\n";
    showEmployees(employees);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSortEmployeesByJobDesc() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to sort");
    employees.sort([](const Employee &a,
                      const Employee &b) { return a.getJob() < b.getJob(); },
                   false);
    cout << "Employees sorted by job (Z-A):\n";
    showEmployees(employees);
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterProductsByName() {
  try {
    if (products.empty())
      throw runtime_error("No products to filter");
    string name;
    cout << "Enter product name to filter: ";
    cin.ignore();
    getline(cin, name);
    if (name.empty())
      throw invalid_argument("Name cannot be empty!");
    MyVector<Product> filtered = products.filter([&name](const Product &p) {
      return p.getName().find(name) != string::npos;
    });
    if (filtered.empty())
      cout << "No products with name containing '" << name << "'\n";
    else {
      cout << "Filtered products (name contains '" << name << "'):\n";
      showProducts(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterProductsByType() {
  try {
    if (products.empty())
      throw runtime_error("No products to filter");
    string type;
    cout << "Enter product type to filter: ";
    cin >> type;
    if (type.empty())
      throw invalid_argument("Type cannot be empty!");
    MyVector<Product> filtered = products.filter(
        [&type](const Product &p) { return p.getType() == type; });
    if (filtered.empty())
      cout << "No products of type '" << type << "'\n";
    else {
      cout << "Filtered products (type = " << type << "):\n";
      showProducts(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterProductsByPrice() {
  try {
    if (products.empty())
      throw runtime_error("No products to filter");
    int minPrice, maxPrice;
    cout << "Enter minimum price: ";
    cin >> minPrice;
    cout << "Enter maximum price: ";
    cin >> maxPrice;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input!");
    }
    if (minPrice < 0 || maxPrice < 0)
      throw invalid_argument("Price cannot be negative!");
    if (minPrice > maxPrice)
      throw invalid_argument("Min price cannot be greater than max price!");
    MyVector<Product> filtered =
        products.filter([minPrice, maxPrice](const Product &p) {
          return p.getPrice() >= minPrice && p.getPrice() <= maxPrice;
        });
    if (filtered.empty())
      cout << "No products in price range [" << minPrice << ", " << maxPrice
           << "]\n";
    else {
      cout << "Filtered products (price between " << minPrice << " and "
           << maxPrice << "):\n";
      showProducts(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterProductsByAmount() {
  try {
    if (products.empty())
      throw runtime_error("No products to filter");
    int minAmount, maxAmount;
    cout << "Enter minimum amount: ";
    cin >> minAmount;
    cout << "Enter maximum amount: ";
    cin >> maxAmount;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input!");
    }
    if (minAmount < 0 || maxAmount < 0)
      throw invalid_argument("Amount cannot be negative!");
    if (minAmount > maxAmount)
      throw invalid_argument("Min amount cannot be greater than max amount!");
    MyVector<Product> filtered =
        products.filter([minAmount, maxAmount](const Product &p) {
          return p.getAmount() >= minAmount && p.getAmount() <= maxAmount;
        });
    if (filtered.empty())
      cout << "No products with amount in range [" << minAmount << ", "
           << maxAmount << "]\n";
    else {
      cout << "Filtered products (amount between " << minAmount << " and "
           << maxAmount << "):\n";
      showProducts(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterSuppliersByName() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to filter");
    string name;
    cout << "Enter supplier name to filter: ";
    cin >> name;
    if (name.empty())
      throw invalid_argument("Name cannot be empty!");
    MyVector<Supplier> filtered = suppliers.filter([&name](const Supplier &s) {
      return s.getName().find(name) != string::npos;
    });
    if (filtered.empty())
      cout << "No suppliers with name containing '" << name << "'\n";
    else {
      cout << "Filtered suppliers (name contains '" << name << "'):\n";
      showSuppliers(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterSuppliersBySurname() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to filter");
    string surname;
    cout << "Enter supplier surname to filter: ";
    cin >> surname;
    if (surname.empty())
      throw invalid_argument("Surname cannot be empty!");
    MyVector<Supplier> filtered =
        suppliers.filter([&surname](const Supplier &s) {
          return s.getSurname().find(surname) != string::npos;
        });
    if (filtered.empty())
      cout << "No suppliers with surname containing '" << surname << "'\n";
    else {
      cout << "Filtered suppliers (surname contains '" << surname << "'):\n";
      showSuppliers(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterSuppliersByAge() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to filter");
    int minAge, maxAge;
    cout << "Enter minimum age: ";
    cin >> minAge;
    cout << "Enter maximum age: ";
    cin >> maxAge;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input!");
    }
    if (minAge < 0 || maxAge < 0)
      throw invalid_argument("Age cannot be negative!");
    if (minAge > maxAge)
      throw invalid_argument("Min age cannot be greater than max age!");
    MyVector<Supplier> filtered =
        suppliers.filter([minAge, maxAge](const Supplier &s) {
          return s.getAge() >= minAge && s.getAge() <= maxAge;
        });
    if (filtered.empty())
      cout << "No suppliers with age in range [" << minAge << ", " << maxAge
           << "]\n";
    else {
      cout << "Filtered suppliers (age between " << minAge << " and " << maxAge
           << "):\n";
      showSuppliers(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterSuppliersByProductName() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers to filter");
    string prodName;
    cout << "Enter product name to filter suppliers: ";
    cin >> prodName;
    if (prodName.empty())
      throw invalid_argument("Product name cannot be empty!");
    MyVector<Supplier> filtered =
        suppliers.filter([&prodName](const Supplier &s) {
          return s.getProduct() &&
                 s.getProduct()->getName().find(prodName) != string::npos;
        });
    if (filtered.empty())
      cout << "No suppliers for product containing '" << prodName << "'\n";
    else {
      cout << "Filtered suppliers (product contains '" << prodName << "'):\n";
      showSuppliers(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterEmployeesByName() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to filter");
    string name;
    cout << "Enter employee name to filter: ";
    cin >> name;
    if (name.empty())
      throw invalid_argument("Name cannot be empty!");
    MyVector<Employee> filtered = employees.filter([&name](const Employee &e) {
      return e.getName().find(name) != string::npos;
    });
    if (filtered.empty())
      cout << "No employees with name containing '" << name << "'\n";
    else {
      cout << "Filtered employees (name contains '" << name << "'):\n";
      showEmployees(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterEmployeesBySurname() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to filter");
    string surname;
    cout << "Enter employee surname to filter: ";
    cin >> surname;
    if (surname.empty())
      throw invalid_argument("Surname cannot be empty!");
    MyVector<Employee> filtered =
        employees.filter([&surname](const Employee &e) {
          return e.getSurname().find(surname) != string::npos;
        });
    if (filtered.empty())
      cout << "No employees with surname containing '" << surname << "'\n";
    else {
      cout << "Filtered employees (surname contains '" << surname << "'):\n";
      showEmployees(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterEmployeesByAge() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to filter");
    int minAge, maxAge;
    cout << "Enter minimum age: ";
    cin >> minAge;
    cout << "Enter maximum age: ";
    cin >> maxAge;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input!");
    }
    if (minAge < 0 || maxAge < 0)
      throw invalid_argument("Age cannot be negative!");
    if (minAge > maxAge)
      throw invalid_argument("Min age cannot be greater than max age!");
    MyVector<Employee> filtered =
        employees.filter([minAge, maxAge](const Employee &e) {
          return e.getAge() >= minAge && e.getAge() <= maxAge;
        });
    if (filtered.empty())
      cout << "No employees with age in range [" << minAge << ", " << maxAge
           << "]\n";
    else {
      cout << "Filtered employees (age between " << minAge << " and " << maxAge
           << "):\n";
      showEmployees(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleFilterEmployeesByJob() {
  try {
    if (employees.empty())
      throw runtime_error("No employees to filter");
    string job;
    cout << "Enter job title to filter: ";
    cin >> job;
    if (job.empty())
      throw invalid_argument("Job title cannot be empty!");
    MyVector<Employee> filtered = employees.filter([&job](const Employee &e) {
      return e.getJob().find(job) != string::npos;
    });
    if (filtered.empty())
      cout << "No employees with job containing '" << job << "'\n";
    else {
      cout << "Filtered employees (job contains '" << job << "'):\n";
      showEmployees(filtered);
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleAdminProductFilterMenu() {
  CMenuItem filterItems[] = {
      CMenuItem("Filter by name", handleFilterProductsByName),
      CMenuItem("Filter by type", handleFilterProductsByType),
      CMenuItem("Filter by price range", handleFilterProductsByPrice),
      CMenuItem("Filter by amount range", handleFilterProductsByAmount)};
  CMenu filterMenu("===== FILTER PRODUCTS =====", filterItems, 4);
  filterMenu.runCommand();
  return 0;
}

int handleAdminSupplierFilterMenu() {
  CMenuItem filterItems[] = {
      CMenuItem("Filter by name", handleFilterSuppliersByName),
      CMenuItem("Filter by surname", handleFilterSuppliersBySurname),
      CMenuItem("Filter by age range", handleFilterSuppliersByAge),
      CMenuItem("Filter by product name", handleFilterSuppliersByProductName)};
  CMenu filterMenu("===== FILTER SUPPLIERS =====", filterItems, 4);
  filterMenu.runCommand();
  return 0;
}

int handleAdminEmployeeFilterMenu() {
  CMenuItem filterItems[] = {
      CMenuItem("Filter by name", handleFilterEmployeesByName),
      CMenuItem("Filter by surname", handleFilterEmployeesBySurname),
      CMenuItem("Filter by age range", handleFilterEmployeesByAge),
      CMenuItem("Filter by job", handleFilterEmployeesByJob)};
  CMenu filterMenu("===== FILTER EMPLOYEES =====", filterItems, 4);
  filterMenu.runCommand();
  return 0;
}

int handleUserProductFilterMenu() {
  CMenuItem filterItems[] = {
      CMenuItem("Filter by name", handleFilterProductsByName),
      CMenuItem("Filter by type", handleFilterProductsByType),
      CMenuItem("Filter by price range", handleFilterProductsByPrice)};
  CMenu filterMenu("===== FILTER PRODUCTS =====", filterItems, 3);
  filterMenu.runCommand();
  return 0;
}

int handleUserSupplierFilterMenu() {
  CMenuItem filterItems[] = {
      CMenuItem("Filter by name", handleFilterSuppliersByName),
      CMenuItem("Filter by surname", handleFilterSuppliersBySurname),
      CMenuItem("Filter by product name", handleFilterSuppliersByProductName)};
  CMenu filterMenu("===== FILTER SUPPLIERS =====", filterItems, 3);
  filterMenu.runCommand();
  return 0;
}

int handleUserEmployeeFilterMenu() {
  CMenuItem filterItems[] = {
      CMenuItem("Filter by name", handleFilterEmployeesByName),
      CMenuItem("Filter by surname", handleFilterEmployeesBySurname),
      CMenuItem("Filter by job", handleFilterEmployeesByJob)};
  CMenu filterMenu("===== FILTER EMPLOYEES =====", filterItems, 3);
  filterMenu.runCommand();
  return 0;
}

int handleAddProduction() {
  try {
    if (products.empty())
      throw runtime_error("No products available. Add product first.");
    if (employees.empty())
      throw runtime_error("No employees available. Add employee first.");
    showProducts(products);
    int prodIndex;
    cout << "Choose product number: ";
    if (!(cin >> prodIndex)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    prodIndex--;
    if (prodIndex < 0 || prodIndex >= static_cast<int>(products.getSize()))
      throw out_of_range("Wrong product number!");
    showEmployees(employees);
    int empIndex;
    cout << "Choose employee number: ";
    if (!(cin >> empIndex)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    empIndex--;
    if (empIndex < 0 || empIndex >= static_cast<int>(employees.getSize()))
      throw out_of_range("Wrong employee number!");
    int quantity;
    string date;
    cout << "Quantity produced: ";
    if (!(cin >> quantity)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Quantity must be a number.");
    }
    if (quantity <= 0)
      throw invalid_argument("Quantity must be positive!");
    cout << "Date (YYYY-MM-DD): ";
    cin >> date;
    if (!isValidDate(date))
      throw invalid_argument("Invalid date format! Use YYYY-MM-DD");
    Production newProduction(products[prodIndex], quantity, date,
                             &employees[empIndex]);
    productions.push_back(newProduction);
    products[prodIndex].setAmount(products[prodIndex].getAmount() + quantity);
    cout << "Production added successfully!\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleAddSale() {
  try {
    if (products.empty())
      throw runtime_error("No products available. Add product first.");
    if (suppliers.empty())
      throw runtime_error("No suppliers available. Add supplier first.");
    showProducts(products);
    int prodIndex;
    cout << "Choose product number: ";
    if (!(cin >> prodIndex)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    prodIndex--;
    if (prodIndex < 0 || prodIndex >= static_cast<int>(products.getSize()))
      throw out_of_range("Wrong product number!");
    showSuppliers(suppliers);
    int supIndex;
    cout << "Choose supplier number: ";
    if (!(cin >> supIndex)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    supIndex--;
    if (supIndex < 0 || supIndex >= static_cast<int>(suppliers.getSize()))
      throw out_of_range("Wrong supplier number!");
    int quantity;
    string date;
    string buyer;
    cout << "Quantity sold: ";
    if (!(cin >> quantity)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Quantity must be a number.");
    }
    if (quantity <= 0)
      throw invalid_argument("Quantity must be positive!");
    if (quantity > products[prodIndex].getAmount())
      throw runtime_error("Not enough stock! Available: " +
                          to_string(products[prodIndex].getAmount()));
    cout << "Date (YYYY-MM-DD): ";
    cin >> date;
    if (!isValidDate(date))
      throw invalid_argument("Invalid date format! Use YYYY-MM-DD");
    cout << "Buyer name: ";
    cin.ignore();
    getline(cin, buyer);
    if (buyer.empty())
      throw invalid_argument("Buyer name cannot be empty!");
    if (!isOnlyLetters(buyer))
      throw invalid_argument(
          "Buyer name must contain only letters, spaces, and hyphens!");
    int totalPrice = quantity * products[prodIndex].getPrice();
    string supplierFullName =
        suppliers[supIndex].getName() + " " + suppliers[supIndex].getSurname();
    Sale newSale(products[prodIndex], quantity, date, totalPrice, buyer,
                 supplierFullName);
    sales.push_back(newSale);
    products[prodIndex].setAmount(products[prodIndex].getAmount() - quantity);
    cout << "Sale added successfully! Total: " << totalPrice << " rub\n";
    cout << "Supplier: " << supplierFullName << endl;
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleShowProductions() {
  try {
    if (productions.empty())
      throw runtime_error("No productions recorded");
    for (size_t i = 0; i < productions.getSize(); i++) {
      cout << "--- Production " << i + 1 << " ---" << endl;
      productions[i].showInfo();
      cout << endl;
    }
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleShowSales() {
  try {
    if (sales.empty())
      throw runtime_error("No sales recorded");
    int totalRevenue = 0;
    for (size_t i = 0; i < sales.getSize(); i++) {
      cout << "--- Sale " << i + 1 << " ---" << endl;
      sales[i].showInfo();
      totalRevenue += sales[i].getTotalPrice();
      cout << endl;
    }
    cout << "Total revenue: " << totalRevenue << " rub\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleProductionMenu() {
  CMenuItem prodItems[] = {
      CMenuItem("Add production", handleAddProduction),
      CMenuItem("Show productions", handleShowProductions)};
  CMenu prodMenu("===== PRODUCTION MENU =====", prodItems, 2);
  prodMenu.runCommand();
  return 0;
}

int handleSalesMenu() {
  CMenuItem salesItems[] = {CMenuItem("Add sale", handleAddSale),
                            CMenuItem("Show sales", handleShowSales)};
  CMenu salesMenu("===== SALES MENU =====", salesItems, 2);
  salesMenu.runCommand();
  return 0;
}

void saveToFile(const string &filename) {
  try {
    ofstream file(filename);
    if (!file.is_open())
      throw runtime_error("Cannot open file for writing: " + filename);
    file << "=== PRODUCTS ===\n";
    for (size_t i = 0; i < products.getSize(); i++) {
      file << products[i].getName() << "|" << products[i].getType() << "|"
           << products[i].getPrice() << "|" << products[i].getAmount() << endl;
    }
    file << "=== EMPLOYEES ===\n";
    for (size_t i = 0; i < employees.getSize(); i++) {
      file << employees[i].getName() << "|" << employees[i].getSurname() << "|"
           << employees[i].getAge() << "|" << employees[i].getLogin() << "|"
           << employees[i].getPassword() << "|" << employees[i].getJob()
           << endl;
    }
    file << "=== SUPPLIERS ===\n";
    for (size_t i = 0; i < suppliers.getSize(); i++) {
      file << suppliers[i].getName() << "|" << suppliers[i].getSurname() << "|"
           << suppliers[i].getAge() << "|" << suppliers[i].getLogin() << "|"
           << suppliers[i].getPassword() << "|"
           << suppliers[i].getProductIndex() << endl;
    }
    file << "=== PRODUCTIONS ===\n";
    for (size_t i = 0; i < productions.getSize(); i++) {
      file << productions[i].getProduct().getName() << "|"
           << productions[i].getQuantity() << "|" << productions[i].getDate()
           << endl;
    }
    file << "=== SALES ===\n";
    for (size_t i = 0; i < sales.getSize(); i++) {
      file << sales[i].getProduct().getName() << "|" << sales[i].getQuantity()
           << "|" << sales[i].getDate() << "|" << sales[i].getTotalPrice()
           << "|" << sales[i].getBuyer() << "|" << sales[i].getSupplierName()
           << endl;
    }
    file.close();
    cout << "Data saved to " << filename << endl;
  } catch (const runtime_error &e) {
    cerr << "File error: " << e.what() << endl;
  }
}

void loadFromFile(const string &filename) {
  try {
    ifstream file(filename);
    if (!file.is_open())
      throw runtime_error("Cannot open file: " + filename);
    products.clear();
    employees.clear();
    suppliers.clear();
    productions.clear();
    sales.clear();
    string line;
    string section;
    while (getline(file, line)) {
      if (line == "=== PRODUCTS ===") {
        section = "PRODUCTS";
        continue;
      } else if (line == "=== EMPLOYEES ===") {
        section = "EMPLOYEES";
        continue;
      } else if (line == "=== SUPPLIERS ===") {
        section = "SUPPLIERS";
        continue;
      } else if (line == "=== PRODUCTIONS ===") {
        section = "PRODUCTIONS";
        continue;
      } else if (line == "=== SALES ===") {
        section = "SALES";
        continue;
      }
      if (line.empty())
        continue;
      if (section == "PRODUCTS") {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        if (pos1 != string::npos && pos2 != string::npos &&
            pos3 != string::npos) {
          string name = line.substr(0, pos1);
          string type = line.substr(pos1 + 1, pos2 - pos1 - 1);
          int price = safeStoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
          int amount = safeStoi(line.substr(pos3 + 1));
          products.push_back(Product(name, type, price, amount));
        }
      } else if (section == "EMPLOYEES") {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);
        size_t pos5 = line.find('|', pos4 + 1);
        if (pos1 != string::npos && pos2 != string::npos &&
            pos3 != string::npos && pos4 != string::npos &&
            pos5 != string::npos) {
          string name = line.substr(0, pos1);
          string surname = line.substr(pos1 + 1, pos2 - pos1 - 1);
          int age = safeStoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
          string login = line.substr(pos3 + 1, pos4 - pos3 - 1);
          string password = line.substr(pos4 + 1, pos5 - pos4 - 1);
          string job = line.substr(pos5 + 1);
          employees.push_back(
              Employee(name, surname, age, login, password, job));
        }
      } else if (section == "SUPPLIERS") {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);
        size_t pos5 = line.find('|', pos4 + 1);
        if (pos1 != string::npos && pos2 != string::npos &&
            pos3 != string::npos && pos4 != string::npos &&
            pos5 != string::npos) {
          string name = line.substr(0, pos1);
          string surname = line.substr(pos1 + 1, pos2 - pos1 - 1);
          int age = safeStoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
          string login = line.substr(pos3 + 1, pos4 - pos3 - 1);
          string password = line.substr(pos4 + 1, pos5 - pos4 - 1);
          int prodIndex = safeStoi(line.substr(pos5 + 1));
          suppliers.push_back(
              Supplier(name, surname, age, login, password, prodIndex));
        }
      } else if (section == "PRODUCTIONS") {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos) {
          string productName = line.substr(0, pos1);
          int quantity = safeStoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
          string date = line.substr(pos2 + 1);
          for (size_t i = 0; i < products.getSize(); i++) {
            if (products[i].getName() == productName) {
              productions.push_back(
                  Production(products[i], quantity, date, nullptr));
              break;
            }
          }
        }
      } else if (section == "SALES") {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);
        size_t pos5 = line.find('|', pos4 + 1);
        if (pos1 != string::npos && pos2 != string::npos &&
            pos3 != string::npos && pos4 != string::npos &&
            pos5 != string::npos) {
          string productName = line.substr(0, pos1);
          int quantity = safeStoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
          string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
          int totalPrice = safeStoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
          string buyer = line.substr(pos4 + 1, pos5 - pos4 - 1);
          string supplierName = line.substr(pos5 + 1);
          for (size_t i = 0; i < products.getSize(); i++) {
            if (products[i].getName() == productName) {
              sales.push_back(Sale(products[i], quantity, date, totalPrice,
                                   buyer, supplierName));
              break;
            }
          }
        }
      }
    }
    file.close();
    cout << "Data loaded from " << filename << endl;
  } catch (const runtime_error &e) {
    cerr << "File error: " << e.what() << endl;
  }
}

int handleGenerateReport() {
  try {
    string reportName;
    cout << "Enter report name: ";
    cin >> reportName;
    if (reportName.empty())
      throw invalid_argument("Report name cannot be empty!");
    if (reportName.find(".txt") == string::npos)
      reportName += ".txt";
    ofstream report(reportName);
    if (!report.is_open())
      throw runtime_error("Cannot create report file: " + reportName);
    report << "========== FACTORY REPORT ==========\n\n";
    report << "--- PRODUCTS ---\n";
    for (size_t i = 0; i < products.getSize(); i++) {
      report << products[i].getName() << " | " << products[i].getType() << " | "
             << products[i].getPrice() << " rub | " << products[i].getAmount()
             << " in stock\n";
    }
    report << "\n--- EMPLOYEES ---\n";
    for (size_t i = 0; i < employees.getSize(); i++) {
      report << employees[i].getName() << " " << employees[i].getSurname()
             << " | Age: " << employees[i].getAge()
             << " | Job: " << employees[i].getJob() << "\n";
    }
    report << "\n--- SUPPLIERS ---\n";
    for (size_t i = 0; i < suppliers.getSize(); i++) {
      report << suppliers[i].getName() << " " << suppliers[i].getSurname()
             << "\n";
    }
    report << "\n--- PRODUCTIONS ---\n";
    int totalProduced = 0;
    for (size_t i = 0; i < productions.getSize(); i++) {
      report << productions[i].getProduct().getName() << " | "
             << productions[i].getQuantity() << " units | "
             << productions[i].getDate() << "\n";
      totalProduced += productions[i].getQuantity();
    }
    report << "Total produced: " << totalProduced << " units\n";
    report << "\n--- SALES ---\n";
    int totalRevenue = 0;
    for (size_t i = 0; i < sales.getSize(); i++) {
      report << sales[i].getProduct().getName() << " | "
             << sales[i].getQuantity() << " units | "
             << sales[i].getTotalPrice()
             << " rub | Buyer: " << sales[i].getBuyer()
             << " | Supplier: " << sales[i].getSupplierName() << "\n";
      totalRevenue += sales[i].getTotalPrice();
    }
    report << "Total revenue: " << totalRevenue << " rub\n";
    report << "\n==============================\n";
    report.close();
    cout << "Report saved to " << reportName << endl;
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleSaveToCustomFile() {
  try {
    string filename;
    cout << "Enter filename to save: ";
    cin >> filename;
    if (filename.empty())
      throw invalid_argument("Filename cannot be empty!");
    if (filename.find(".txt") == string::npos)
      filename += ".txt";
    saveToFile(filename);
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleLoadFromCustomFile() {
  try {
    string filename;
    cout << "Enter filename to load: ";
    cin >> filename;
    if (filename.empty())
      throw invalid_argument("Filename cannot be empty!");
    if (filename.find(".txt") == string::npos)
      filename += ".txt";
    loadFromFile(filename);
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleReportsMenu() {
  CMenuItem reportItems[] = {
      CMenuItem("Generate report", handleGenerateReport),
      CMenuItem("Save to custom file", handleSaveToCustomFile),
      CMenuItem("Load from custom file", handleLoadFromCustomFile)};
  CMenu reportMenu("===== REPORTS MENU =====", reportItems, 3);
  reportMenu.runCommand();
  return 0;
}

int handleSortMenu() {
  CMenuItem sortItems[] = {
      CMenuItem("Products by name (A-Z)", handleSortProductsByNameAsc),
      CMenuItem("Products by name (Z-A)", handleSortProductsByNameDesc),
      CMenuItem("Products by type (A-Z)", handleSortProductsByTypeAsc),
      CMenuItem("Products by type (Z-A)", handleSortProductsByTypeDesc),
      CMenuItem("Products by price (ascending)", handleSortProductsByPriceAsc),
      CMenuItem("Products by price (descending)",
                handleSortProductsByPriceDesc),
      CMenuItem("Products by amount (ascending)",
                handleSortProductsByAmountAsc),
      CMenuItem("Products by amount (descending)",
                handleSortProductsByAmountDesc),
      CMenuItem("Suppliers by name (A-Z)", handleSortSuppliersByNameAsc),
      CMenuItem("Suppliers by name (Z-A)", handleSortSuppliersByNameDesc),
      CMenuItem("Suppliers by surname (A-Z)", handleSortSuppliersBySurnameAsc),
      CMenuItem("Suppliers by surname (Z-A)", handleSortSuppliersBySurnameDesc),
      CMenuItem("Suppliers by age (ascending)", handleSortSuppliersByAgeAsc),
      CMenuItem("Suppliers by age (descending)", handleSortSuppliersByAgeDesc),
      CMenuItem("Suppliers by product name (A-Z)",
                handleSortSuppliersByProductNameAsc),
      CMenuItem("Suppliers by product name (Z-A)",
                handleSortSuppliersByProductNameDesc),
      CMenuItem("Employees by name (A-Z)", handleSortEmployeesByNameAsc),
      CMenuItem("Employees by name (Z-A)", handleSortEmployeesByNameDesc),
      CMenuItem("Employees by surname (A-Z)", handleSortEmployeesBySurnameAsc),
      CMenuItem("Employees by surname (Z-A)", handleSortEmployeesBySurnameDesc),
      CMenuItem("Employees by age (ascending)", handleSortEmployeesByAgeAsc),
      CMenuItem("Employees by age (descending)", handleSortEmployeesByAgeDesc),
      CMenuItem("Employees by job (A-Z)", handleSortEmployeesByJobAsc),
      CMenuItem("Employees by job (Z-A)", handleSortEmployeesByJobDesc)};
  CMenu sortMenu("===== SORT MENU =====", sortItems, 24);
  sortMenu.runCommand();
  return 0;
}

int handleFilterMenu() {
  CMenuItem filterItems[] = {
      CMenuItem("Filter Products", handleAdminProductFilterMenu),
      CMenuItem("Filter Suppliers", handleAdminSupplierFilterMenu),
      CMenuItem("Filter Employees", handleAdminEmployeeFilterMenu)};
  CMenu filterMenu("===== FILTER MENU =====", filterItems, 3);
  filterMenu.runCommand();
  return 0;
}

int handleAddProduct() {
  try {
    string name, productType;
    int price;
    cout << "Name: ";
    cin >> name;
    if (name.empty())
      throw invalid_argument("Product name cannot be empty!");
    cout << "Type: ";
    cin >> productType;
    if (productType.empty())
      throw invalid_argument("Product type cannot be empty!");
    cout << "Price: ";
    if (!(cin >> price)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Price must be a number.");
    }
    if (price < 0)
      throw invalid_argument("Price cannot be negative!");
    products.push_back(Product(name, productType, price, 0));
    cout << "Product added to catalog. Use 'Production' or 'Restock via "
            "supplier' to add stock.\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleAddSupplier() {
  try {
    if (products.empty())
      throw runtime_error("Add product first");
    showProducts(products);
    int prodIndex;
    cout << "Choose product number for this supplier: ";
    if (!(cin >> prodIndex)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    prodIndex--;
    if (prodIndex < 0 || prodIndex >= static_cast<int>(products.getSize()))
      throw out_of_range("Wrong product number!");
    string name, surname, login2, password2;
    int age;
    cout << "Name: ";
    cin >> name;
    if (name.empty())
      throw invalid_argument("Name cannot be empty!");
    if (!isOnlyLetters(name))
      throw invalid_argument(
          "Name must contain only letters, spaces, and hyphens!");
    cout << "Surname: ";
    cin >> surname;
    if (surname.empty())
      throw invalid_argument("Surname cannot be empty!");
    if (!isOnlyLetters(surname))
      throw invalid_argument(
          "Surname must contain only letters, spaces, and hyphens!");
    cout << "Age: ";
    if (!(cin >> age)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Age must be a number.");
    }
    if (age < 0 || age > 150)
      throw invalid_argument("Age must be between 0 and 150!");
    cout << "Login: ";
    cin >> login2;
    if (login2.empty())
      throw invalid_argument("Login cannot be empty!");
    cout << "Password: ";
    cin >> password2;
    if (password2.empty())
      throw invalid_argument("Password cannot be empty!");
    suppliers.push_back(
        Supplier(name, surname, age, login2, password2, prodIndex));
    cout << "Supplier added (linked to product "
         << products[prodIndex].getName() << ")\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleAddEmployee() {
  try {
    string name, surname, login2, password2, job;
    int age;
    cout << "Name: ";
    cin >> name;
    if (name.empty())
      throw invalid_argument("Name cannot be empty!");
    if (!isOnlyLetters(name))
      throw invalid_argument(
          "Name must contain only letters, spaces, and hyphens!");
    cout << "Surname: ";
    cin >> surname;
    if (surname.empty())
      throw invalid_argument("Surname cannot be empty!");
    if (!isOnlyLetters(surname))
      throw invalid_argument(
          "Surname must contain only letters, spaces, and hyphens!");
    cout << "Age: ";
    if (!(cin >> age)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Age must be a number.");
    }
    if (age < 0 || age > 150)
      throw invalid_argument("Age must be between 0 and 150!");
    cout << "Login: ";
    cin >> login2;
    if (login2.empty())
      throw invalid_argument("Login cannot be empty!");
    cout << "Password: ";
    cin >> password2;
    if (password2.empty())
      throw invalid_argument("Password cannot be empty!");
    cout << "Job: ";
    cin >> job;
    if (job.empty())
      throw invalid_argument("Job cannot be empty!");
    if (!isOnlyLetters(job))
      throw invalid_argument(
          "Job must contain only letters, spaces, and hyphens!");
    employees.push_back(Employee(name, surname, age, login2, password2, job));
    cout << "Employee added\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleEditProduct() {
  try {
    if (products.empty())
      throw runtime_error("No products available to edit");
    showProducts(products);
    int index;
    cout << "Choose product number: ";
    if (!(cin >> index)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    index--;
    if (index < 0 || index >= static_cast<int>(products.getSize()))
      throw out_of_range("Wrong number!");
    string name, productType;
    int price;
    cout << "New name: ";
    cin >> name;
    if (name.empty())
      throw invalid_argument("Name cannot be empty!");
    cout << "New type: ";
    cin >> productType;
    if (productType.empty())
      throw invalid_argument("Type cannot be empty!");
    cout << "New price: ";
    if (!(cin >> price)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Price must be a number.");
    }
    if (price < 0)
      throw invalid_argument("Price cannot be negative!");
    products[index].setName(name);
    products[index].setType(productType);
    products[index].setPrice(price);
    cout << "Product updated (amount remains unchanged: "
         << products[index].getAmount() << ")\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleEditSupplier() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers available to edit");
    showSuppliers(suppliers);
    int index;
    cout << "Choose supplier number: ";
    if (!(cin >> index)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    index--;
    if (index < 0 || index >= static_cast<int>(suppliers.getSize()))
      throw out_of_range("Wrong number!");
    string name, surname, login2, password2;
    int age;
    cout << "New name: ";
    cin >> name;
    if (name.empty())
      throw invalid_argument("Name cannot be empty!");
    if (!isOnlyLetters(name))
      throw invalid_argument(
          "Name must contain only letters, spaces, and hyphens!");
    cout << "New surname: ";
    cin >> surname;
    if (surname.empty())
      throw invalid_argument("Surname cannot be empty!");
    if (!isOnlyLetters(surname))
      throw invalid_argument(
          "Surname must contain only letters, spaces, and hyphens!");
    cout << "New age: ";
    if (!(cin >> age)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Age must be a number.");
    }
    if (age < 0 || age > 150)
      throw invalid_argument("Age must be between 0 and 150!");
    cout << "New login: ";
    cin >> login2;
    if (login2.empty())
      throw invalid_argument("Login cannot be empty!");
    cout << "New password: ";
    cin >> password2;
    if (password2.empty())
      throw invalid_argument("Password cannot be empty!");
    suppliers[index].setName(name);
    suppliers[index].setSurname(surname);
    suppliers[index].setAge(age);
    suppliers[index].setLogin(login2);
    suppliers[index].setPassword(password2);
    cout << "Supplier updated (linked product remains the same)\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleEditEmployee() {
  try {
    if (employees.empty())
      throw runtime_error("No employees available to edit");
    showEmployees(employees);
    int index;
    cout << "Choose employee number: ";
    if (!(cin >> index)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    index--;
    if (index < 0 || index >= static_cast<int>(employees.getSize()))
      throw out_of_range("Wrong number!");
    string name, surname, login2, password2, job;
    int age;
    cout << "New name: ";
    cin >> name;
    if (name.empty())
      throw invalid_argument("Name cannot be empty!");
    if (!isOnlyLetters(name))
      throw invalid_argument(
          "Name must contain only letters, spaces, and hyphens!");
    cout << "New surname: ";
    cin >> surname;
    if (surname.empty())
      throw invalid_argument("Surname cannot be empty!");
    if (!isOnlyLetters(surname))
      throw invalid_argument(
          "Surname must contain only letters, spaces, and hyphens!");
    cout << "New age: ";
    if (!(cin >> age)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Age must be a number.");
    }
    if (age < 0 || age > 150)
      throw invalid_argument("Age must be between 0 and 150!");
    cout << "New login: ";
    cin >> login2;
    if (login2.empty())
      throw invalid_argument("Login cannot be empty!");
    cout << "New password: ";
    cin >> password2;
    if (password2.empty())
      throw invalid_argument("Password cannot be empty!");
    cout << "New job: ";
    cin >> job;
    if (job.empty())
      throw invalid_argument("Job cannot be empty!");
    if (!isOnlyLetters(job))
      throw invalid_argument(
          "Job must contain only letters, spaces, and hyphens!");
    employees[index].setName(name);
    employees[index].setSurname(surname);
    employees[index].setAge(age);
    employees[index].setLogin(login2);
    employees[index].setPassword(password2);
    employees[index].setJob(job);
    cout << "Employee updated\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleDeleteProduct() {
  try {
    if (products.empty())
      throw runtime_error("No products available to delete");
    showProducts(products);
    int index;
    cout << "Choose product number: ";
    if (!(cin >> index)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    index--;
    if (index < 0 || index >= static_cast<int>(products.getSize()))
      throw out_of_range("Wrong number!");
    for (size_t i = 0; i < suppliers.getSize(); ++i) {
      int prodIndex = suppliers[i].getProductIndex();
      if (prodIndex == index)
        suppliers[i].setProductIndex(-1);
      else if (prodIndex > index)
        suppliers[i].setProductIndex(prodIndex - 1);
    }
    products.erase(index);
    cout << "Deleted\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleDeleteSupplier() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers available to delete");
    showSuppliers(suppliers);
    int index;
    cout << "Choose supplier number: ";
    if (!(cin >> index)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    index--;
    if (index < 0 || index >= static_cast<int>(suppliers.getSize()))
      throw out_of_range("Wrong number!");
    suppliers.erase(index);
    cout << "Deleted\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleDeleteEmployee() {
  try {
    if (employees.empty())
      throw runtime_error("No employees available to delete");
    showEmployees(employees);
    int index;
    cout << "Choose employee number: ";
    if (!(cin >> index)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    index--;
    if (index < 0 || index >= static_cast<int>(employees.getSize()))
      throw out_of_range("Wrong number!");
    employees.erase(index);
    cout << "Deleted\n";
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
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
  try {
    if (products.getSize() < 2)
      throw runtime_error("Need at least 2 products to merge");
    showProducts(products);
    int first, second;
    cout << "Choose first product number: ";
    if (!(cin >> first)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    cout << "Choose second product number: ";
    if (!(cin >> second)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    first--;
    second--;
    if (first < 0 || first >= static_cast<int>(products.getSize()) ||
        second < 0 || second >= static_cast<int>(products.getSize()))
      throw out_of_range("Wrong numbers!");
    if (!(products[first] == products[second]))
      throw logic_error("Cannot sum different products!");
    int keepIndex = first;
    int removeIndex = second;
    if (keepIndex > removeIndex) {
      keepIndex = second;
      removeIndex = first;
    }
    for (size_t i = 0; i < suppliers.getSize(); ++i) {
      int prodIndex = suppliers[i].getProductIndex();
      if (prodIndex == removeIndex)
        suppliers[i].setProductIndex(keepIndex);
      else if (prodIndex > removeIndex)
        suppliers[i].setProductIndex(prodIndex - 1);
    }
    products[keepIndex] = products[keepIndex] + products[removeIndex];
    products.erase(removeIndex);
    cout << "Products merged successfully:\n";
    cout << products[keepIndex] << endl;
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const logic_error &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int handleRestockSupplier() {
  try {
    if (suppliers.empty())
      throw runtime_error("No suppliers available");
    showSuppliers(suppliers);
    int supIndex;
    cout << "Choose supplier number: ";
    if (!(cin >> supIndex)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Please enter a number.");
    }
    supIndex--;
    if (supIndex < 0 || supIndex >= static_cast<int>(suppliers.getSize()))
      throw out_of_range("Wrong supplier number!");
    if (!suppliers[supIndex].getProduct())
      throw runtime_error("Supplier has no linked product!");
    int qty;
    cout << "Quantity to add: ";
    if (!(cin >> qty)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      throw runtime_error("Invalid input! Quantity must be a number.");
    }
    if (qty <= 0)
      throw invalid_argument("Quantity must be positive!");
    suppliers[supIndex] += qty;
    cout << "Stock updated. Product now:\n";
    cout << *suppliers[supIndex].getProduct() << endl;
  } catch (const runtime_error &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const out_of_range &e) {
    cerr << "Error: " << e.what() << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
  return 0;
}

int main() {
  while (true) {
    try {
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
        } else
          throw runtime_error("Wrong admin login or password!");
      } else if (roleChoice == 2) {
        if (login == "user" && password == "111") {
          cout << "Logged in as USER\n";
        } else
          throw runtime_error("Wrong user login or password!");
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
              CMenuItem("Production management", handleProductionMenu),
              CMenuItem("Sales management", handleSalesMenu),
              CMenuItem("Reports", handleReportsMenu),
              CMenuItem("Logout", handleAdminLogout),
              CMenuItem("Exit", handleAdminExit)};
          CMenu adminMenu("===== ADMIN MENU =====", adminItems, 13);
          int choice = adminMenu.runCommand();
          if (choice == 12)
            loggedIn = false;
          else if (choice == 13)
            return 0;
        } else {
          CMenuItem userItems[] = {
              CMenuItem("Show", handleUserShow),
              CMenuItem("Sort", handleUserSortMenu),
              CMenuItem("Filter Products", handleUserProductFilterMenu),
              CMenuItem("Filter Suppliers", handleUserSupplierFilterMenu),
              CMenuItem("Filter Employees", handleUserEmployeeFilterMenu),
              CMenuItem("Load file", handleUserLoadFile),
              CMenuItem("Logout", handleUserLogout),
              CMenuItem("Exit", handleUserExit)};
          CMenu userMenu("===== USER MENU =====", userItems, 8);
          int choice = userMenu.runCommand();
          if (choice == 7)
            loggedIn = false;
          else if (choice == 8)
            return 0;
        }
      }
    } catch (const runtime_error &e) {
      cerr << "Authorization error: " << e.what() << endl;
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

int handleUserShow() {
  CMenuItem showItems[] = {CMenuItem("Products", handleShowProducts),
                           CMenuItem("Suppliers", handleShowSuppliers),
                           CMenuItem("Employees", handleShowEmployees)};
  CMenu showMenu("===== SHOW MENU =====", showItems, 3);
  showMenu.runCommand();
  return 0;
}

int handleUserSortMenu() {
  CMenuItem sortItems[] = {
      CMenuItem("Products by name (A-Z)", handleSortProductsByNameAsc),
      CMenuItem("Products by name (Z-A)", handleSortProductsByNameDesc),
      CMenuItem("Products by type (A-Z)", handleSortProductsByTypeAsc),
      CMenuItem("Products by type (Z-A)", handleSortProductsByTypeDesc),
      CMenuItem("Products by price (ascending)", handleSortProductsByPriceAsc),
      CMenuItem("Products by price (descending)",
                handleSortProductsByPriceDesc),
      CMenuItem("Suppliers by name (A-Z)", handleSortSuppliersByNameAsc),
      CMenuItem("Suppliers by name (Z-A)", handleSortSuppliersByNameDesc),
      CMenuItem("Suppliers by surname (A-Z)", handleSortSuppliersBySurnameAsc),
      CMenuItem("Suppliers by surname (Z-A)", handleSortSuppliersBySurnameDesc),
      CMenuItem("Suppliers by product name (A-Z)",
                handleSortSuppliersByProductNameAsc),
      CMenuItem("Suppliers by product name (Z-A)",
                handleSortSuppliersByProductNameDesc),
      CMenuItem("Employees by name (A-Z)", handleSortEmployeesByNameAsc),
      CMenuItem("Employees by name (Z-A)", handleSortEmployeesByNameDesc),
      CMenuItem("Employees by surname (A-Z)", handleSortEmployeesBySurnameAsc),
      CMenuItem("Employees by surname (Z-A)", handleSortEmployeesBySurnameDesc),
      CMenuItem("Employees by job (A-Z)", handleSortEmployeesByJobAsc),
      CMenuItem("Employees by job (Z-A)", handleSortEmployeesByJobDesc)};
  CMenu sortMenu("===== SORT MENU =====", sortItems, 18);
  sortMenu.runCommand();
  return 0;
}

int handleAdminLogout() { return 12; }
int handleAdminExit() { return 13; }
int handleUserLogout() { return 7; }
int handleUserExit() { return 8; }

void showProducts(MyVector<Product> &products) {
  if (products.empty()) {
    cout << "No products available\n";
    return;
  }
  for (size_t i = 0; i < products.getSize(); i++) {
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
  for (size_t i = 0; i < suppliers.getSize(); i++) {
    cout << i + 1 << ". ";
    suppliers[i].showInfo();
    cout << endl;
  }
}

void showEmployees(MyVector<Employee> &employees) {
  if (employees.empty()) {
    cout << "No employees available\n";
    return;
  }
  for (size_t i = 0; i < employees.getSize(); i++) {
    cout << i + 1 << ". ";
    employees[i].showInfo();
    cout << endl;
  }
}

void showAllUsersPolymorphically(MyVector<Employee> &employees,
                                 MyVector<Supplier> &suppliers) {
  if (employees.empty() && suppliers.empty()) {
    cout << "No users available\n";
    return;
  }
  cout << "========== EMPLOYEES ==========\n";
  for (size_t i = 0; i < employees.getSize(); i++) {
    cout << "--- Employee " << i + 1 << " ---" << endl;
    employees[i].showInfo();
    employees[i].performAction();
    cout << endl;
  }
  cout << "========== SUPPLIERS ==========\n";
  for (size_t i = 0; i < suppliers.getSize(); i++) {
    cout << "--- Supplier " << i + 1 << " ---" << endl;
    suppliers[i].showInfo();
    suppliers[i].performAction();
    cout << endl;
  }
}
