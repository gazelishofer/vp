#ifndef LR2_USER_H
#define LR2_USER_H

#include "../IEntity/IEntity.h"
#include <string>

using namespace std;

class User : public IEntity {
protected:
  string name;
  string surname;
  int age;
  string login;
  string password;

public:
  User(string n, string s, int a, string l, string p) {
    name = n;
    surname = s;
    age = a;
    login = l;
    password = p;
  }

  User(const User &other) {
    name = other.name;
    surname = other.surname;
    age = other.age;
    login = other.login;
    password = other.password;
  }

  User &operator=(const User &other) {
    if (this != &other) {
      name = other.name;
      surname = other.surname;
      age = other.age;
      login = other.login;
      password = other.password;
    }
    return *this;
  }

  IEntity *copy() const override { return nullptr; }

  void assign(const IEntity &other) override {
    const User *u = dynamic_cast<const User *>(&other);
    if (u) {
      name = u->name;
      surname = u->surname;
      age = u->age;
      login = u->login;
      password = u->password;
    }
  }

  void destroy() override { delete this; }

  virtual void showInfo() const override = 0;
  virtual void performAction() = 0;

  bool isEqual(const IEntity &other) const override {
    const User *u = dynamic_cast<const User *>(&other);
    if (!u)
      return false;
    return login == u->login;
  }

  void setName(string n) { name = n; }
  void setSurname(string s) { surname = s; }
  void setAge(int a) { age = a; }
  void setLogin(string l) { login = l; }
  void setPassword(string p) { password = p; }

  int getAge() const { return age; }
  string getName() const { return name; }
  string getSurname() const { return surname; }
  string getLogin() const { return login; }
  string getPassword() const { return password; }
};

#endif
