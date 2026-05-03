#ifndef LR2_PRODUCT_H
#define LR2_PRODUCT_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Product
{
private:
    string name;
    string type;
    int price;
    int amount;

public:
    virtual ~Product() = default;

    Product(string n, string t, int p, int a)
    {
        name = n;
        type = t;
        price = p;
        amount = a;
    }

    Product operator+(Product other)
    {
        if (*this == other)
        {
            return Product(
                name,
                type,
                price,
                amount + other.amount
            );
        }

        throw logic_error("Different products cannot be summed");
    }

    bool operator==(Product other)
    {
        return name == other.name &&
               type == other.type &&
               price == other.price;
    }

    friend ostream& operator<<(ostream& out, Product p)
    {
        out << p.getName() << " "
            << p.getType() << " "
            << p.getPrice() << " "
            << p.getAmount();

        return out;
    }

    void setName(string n)
    {
        name = n;
    }

    void setType(string t)
    {
        type = t;
    }

    void setPrice(int p)
    {
        price = p;
    }

    void setAmount(int a)
    {
        amount = a;
    }

    string getName()
    {
        return name;
    }

    string getType()
    {
        return type;
    }

    int getPrice()
    {
        return price;
    }

    int getAmount()
    {
        return amount;
    }
};

#endif