#include <iostream>
#include <string>
#include "menu/CMenu.h"
#include <vector>
using namespace std;
#include "menu/CMenuItem.h"
#include <iostream>
using namespace XXX;

#include "../Models/Employee/Employee.h"
#include "../Models/Product/Product.h"
#include "../Models/Supplier/Supplier.h"



void showProducts(vector<Product>& products);
void showSuppliers(vector<Supplier>& suppliers);
void showEmployees(vector<Employee>& employees);
void showAllUsersPolymorphically(vector<Employee>& employees, vector<Supplier>& suppliers);

void handleAddMenu(vector<Product>& products,
                   vector<Supplier>& suppliers,
                   vector<Employee>& employees);

void handleEditMenu(vector<Product>& products,
                    vector<Supplier>& suppliers,
                    vector<Employee>& employees);

void handleDeleteMenu(vector<Product>& products,
                      vector<Supplier>& suppliers,
                      vector<Employee>& employees);

void handleShowMenu(vector<Product>& products,
                    vector<Supplier>& suppliers,
                    vector<Employee>& employees);

void handleAddMenu(vector<Product>& products,
                   vector<Supplier>& suppliers,
                   vector<Employee>& employees)
{
    int type;

    cout << "\n1. Product\n";
    cout << "2. Supplier\n";
    cout << "3. Employee\n";
    cout << "Choose: ";
    cin >> type;

    switch (type)
    {
        case 1:
        {
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
            break;
        }

        case 2:
        {
            if (products.empty())
            {
                cout << "Add product first\n";
                break;
            }

            showProducts(products);

            int prodIndex;
            cout << "Choose product number for this supplier: ";
            cin >> prodIndex;
            prodIndex--;

            if (prodIndex < 0 || prodIndex >= static_cast<int>(products.size()))
            {
                cout << "Wrong product number\n";
                break;
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
                Supplier(name, surname, age, login2, password2, &products[prodIndex])
            );

            cout << "Supplier added (linked to product " << products[prodIndex].getName() << ")\n";
            break;
        }

        case 3:
        {
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

            employees.push_back(
                Employee(name, surname, age, login2, password2, job)
            );

            cout << "Employee added\n";
            break;
        }

        default:
            cout << "Wrong choice\n";
    }
}

void handleEditMenu(vector<Product>& products,
                    vector<Supplier>& suppliers,
                    vector<Employee>& employees)
{
    int type, index;

    cout << "\n1. Product\n";
    cout << "2. Supplier\n";
    cout << "3. Employee\n";
    cout << "Choose: ";
    cin >> type;

    switch (type)
    {
        case 1:
        {
            showProducts(products);

            cout << "Choose product number: ";
            cin >> index;
            index--;

            if (index < 0 || index >= static_cast<int>(products.size()))
            {
                cout << "Wrong number\n";
                break;
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
            break;
        }

        case 2:
        {
            showSuppliers(suppliers);

            cout << "Choose supplier number: ";
            cin >> index;
            index--;

            if (index < 0 || index >= static_cast<int>(suppliers.size()))
            {
                cout << "Wrong number\n";
                break;
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
            break;
        }

        case 3:
        {
            showEmployees(employees);

            cout << "Choose employee number: ";
            cin >> index;
            index--;

            if (index < 0 || index >= static_cast<int>(employees.size()))
            {
                cout << "Wrong number\n";
                break;
            }

            string job;

            cout << "New job: ";
            cin >> job;

            employees[index].setJob(job);

            cout << "Updated\n";
            break;
        }

        default:
            cout << "Wrong choice\n";
    }
}

void handleDeleteMenu(vector<Product>& products,
                      vector<Supplier>& suppliers,
                      vector<Employee>& employees)
{
    int type, index;

    cout << "\n1. Product\n";
    cout << "2. Supplier\n";
    cout << "3. Employee\n";
    cout << "Choose: ";
    cin >> type;

    switch (type)
    {
        case 1:
        {
            showProducts(products);

            cout << "Choose product number: ";
            cin >> index;
            index--;

            if (index >= 0 && index < static_cast<int>(products.size()))
            {
                Product* base = products.data();
                vector<int> oldIdx(suppliers.size(), -1);
                for (size_t i = 0; i < suppliers.size(); ++i) {
                    Product* p = suppliers[i].getProduct();
                    if (p) oldIdx[i] = static_cast<int>(p - base);
                }

                products.erase(products.begin() + index);

                for (size_t i = 0; i < suppliers.size(); ++i) {
                    int idx = oldIdx[i];
                    if (idx < 0) continue;
                    if (idx == index) {
                        suppliers[i].setProduct(nullptr);
                    } else if (idx > index) {
                        suppliers[i].setProduct(&products[idx - 1]);
                    }
                }
                cout << "Deleted\n";
            }
            break;
        }

        case 2:
        {
            showSuppliers(suppliers);

            cout << "Choose supplier number: ";
            cin >> index;
            index--;

            if (index >= 0 && index < static_cast<int>(suppliers.size()))
            {
                suppliers.erase(suppliers.begin() + index);
                cout << "Deleted\n";
            }
            break;
        }

        case 3:
        {
            showEmployees(employees);

            cout << "Choose employee number: ";
            cin >> index;
            index--;

            if (index >= 0 && index < static_cast<int>(employees.size()))
            {
                employees.erase(employees.begin() + index);
                cout << "Deleted\n";
            }
            break;
        }

        default:
            cout << "Wrong choice\n";
    }
}

void handleShowMenu(vector<Product>& products,
                    vector<Supplier>& suppliers,
                    vector<Employee>& employees)
{
    int type;

    cout << "\n1. Products\n";
    cout << "2. Suppliers\n";
    cout << "3. Employees\n";
    cout << "4. All users polymorphically\n";
    cout << "Choose: ";
    cin >> type;

    switch (type)
    {
        case 1: showProducts(products); break;
        case 2: showSuppliers(suppliers); break;
        case 3: showEmployees(employees); break;
        case 4: showAllUsersPolymorphically(employees, suppliers); break;
        default: cout << "Wrong choice\n";
    }
}

void showProducts(vector<Product>& products)
{
    if (products.empty())
    {
        cout << "No products available\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(products.size()); i++)
    {
        cout << i + 1<< ". "
             << products[i].getName() << " "
             << products[i].getType() << " "
             << products[i].getPrice() << " "
             << products[i].getAmount() << endl;
    }
}

void showSuppliers(vector<Supplier>& suppliers)
{
    if (suppliers.empty())
    {
        cout << "No suppliers available\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(suppliers.size()); i++)
    {
        cout << i + 1 << ". ";
        suppliers[i].showInfo();
    }
}

void showEmployees(vector<Employee>& employees)
{
    if (employees.empty())
    {
        cout << "No employees available\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(employees.size()); i++)
    {
        cout << i + 1 << ". ";
        employees[i].showInfo();
    }
}

void showAllUsersPolymorphically(vector<Employee>& employees, vector<Supplier>& suppliers)
{
    vector<User*> users;

    for (auto& employee : employees)
    {
        users.push_back(&employee);
    }

    for (auto& supplier : suppliers)
    {
        users.push_back(&supplier);
    }

    if (users.empty())
    {
        cout << "No users available\n";
        return;
    }

    for (auto item : users)
    {
        item->showInfo();
        item->performAction();
        cout << endl;
    }
}

int main()
{
    vector<Product> products;
    vector<Supplier> suppliers;
    vector<Employee> employees;

    products.reserve(1000);

    while (true)
    {
        int roleChoice;

        cout << "\n===== AUTHORIZATION =====\n";
        cout << "1. Login as admin\n";
        cout << "2. Login as user\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> roleChoice;

        if (roleChoice == 3)
            return 0;

        string login, password;

        cout << "Login: ";
        cin >> login;

        cout << "Password: ";
        cin >> password;

        bool isAdmin = false;

        if (roleChoice == 1)
        {
            if (login == "admin" && password == "123")
            {
                isAdmin = true;
                cout << "Logged in as ADMIN\n";
            }
            else
            {
                cout << "Wrong admin login or password\n";
                continue;
            }
        }
        else if (roleChoice == 2)
        {
            if (login == "user" && password == "111")
            {
                cout << "Logged in as USER\n";
            }
            else
            {
                cout << "Wrong user login or password\n";
                continue;
            }
        }
        else
        {
            cout << "Wrong choice\n";
            continue;
        }

        bool loggedIn = true;

        while (loggedIn)
        {
            int choice;

            if (isAdmin)
            {
                cout << "\n===== ADMIN MENU =====\n";
                cout << "1. Add\n";
                cout << "2. Edit\n";
                cout << "3. Delete\n";
                cout << "4. Show\n";
                cout << "5. Merge products (operator+)\n";
                cout << "6. Restock via supplier (operator+)\n";
                cout << "7. Logout\n";
                cout << "8. Exit\n";
                cout << "Choose: ";
                cin >> choice;

                switch (choice)
                {
                    case 1: handleAddMenu(products, suppliers, employees); break;
                    case 2: handleEditMenu(products, suppliers, employees); break;
                    case 3: handleDeleteMenu(products, suppliers, employees); break;
                    case 4: handleShowMenu(products, suppliers, employees); break;

                    case 5:
                    {
                        if (products.size() < 2)
                        {
                            cout << "Need at least 2 products\n";
                            break;
                        }

                        showProducts(products);

                        int first, second;

                        cout << "Choose first product number: ";
                        cin >> first;

                        cout << "Choose second product number: ";
                        cin >> second;

                        first--;
                        second--;

                        if (first < 0 || first >= static_cast<int>(products.size()) ||
                            second < 0 || second >= static_cast<int>(products.size()))
                        {
                            cout << "Wrong numbers\n";
                            break;
                        }

                        if (!(products[first] == products[second]))
                        {
                            cout << "Cannot sum different products\n";
                            break;
                        }

                        Product* base = products.data();
                        vector<int> oldIdx(suppliers.size(), -1);
                        for (size_t i = 0; i < suppliers.size(); ++i) {
                            Product* p = suppliers[i].getProduct();
                            if (p) oldIdx[i] = static_cast<int>(p - base);
                        }

                        products[first] = products[first] + products[second];
                        products.erase(products.begin() + second);

                        int newFirstIdx = (first > second) ? first - 1 : first;

                        for (size_t i = 0; i < suppliers.size(); ++i) {
                            int idx = oldIdx[i];
                            if (idx < 0) continue;
                            if (idx == second) {
                                suppliers[i].setProduct(&products[newFirstIdx]);
                            } else if (idx > second) {
                                suppliers[i].setProduct(&products[idx - 1]);
                            }
                        }

                        cout << "Products merged successfully:\n";
                        cout << products[newFirstIdx] << endl;

                        break;
                    }

                    case 6:
                    {
                        if (suppliers.empty())
                        {
                            cout << "No suppliers available\n";
                            break;
                        }

                        showSuppliers(suppliers);

                        int supIndex, qty;

                        cout << "Choose supplier number: ";
                        cin >> supIndex;
                        supIndex--;

                        if (supIndex < 0 || supIndex >= static_cast<int>(suppliers.size()))
                        {
                            cout << "Wrong supplier number\n";
                            break;
                        }

                        if (!suppliers[supIndex].getProduct())
                        {
                            cout << "Supplier has no linked product\n";
                            break;
                        }

                        cout << "Quantity to add: ";
                        cin >> qty;

                        suppliers[supIndex] = suppliers[supIndex] + qty;

                        cout << "Stock updated. Product now:\n";
                        cout << *suppliers[supIndex].getProduct() << endl;
                        break;
                    }

                    case 7:
                        loggedIn = false;
                        break;

                    case 8:
                        return 0;

                    default:
                        cout << "Wrong choice\n";
                }
            }
            else
            {
                cout << "\n===== USER MENU =====\n";
                cout << "1. Show\n";
                cout << "2. Logout\n";
                cout << "3. Exit\n";
                cout << "Choose: ";
                cin >> choice;

                switch (choice)
                {
                    case 1:
                        handleShowMenu(products, suppliers, employees);
                        break;

                    case 2:
                        loggedIn = false;
                        break;

                    case 3:
                        return 0;

                    default:
                        cout << "Wrong choice\n";
                }
            }
        }
    }
}