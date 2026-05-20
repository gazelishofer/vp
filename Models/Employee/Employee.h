#ifndef LR2_EMPLOYEE_H
#define LR2_EMPLOYEE_H

#include "../User/User.h"
#include <iostream>
#include <string>

using namespace std;

class Employee : public User {
private:
  string job;

public:
  Employee(string n, string s, int a, string l, string p, string j)
      : User(n, s, a, l, p), job(j) {}

  Employee(const Employee &other) : User(other), job(other.job) {}

  Employee &operator=(const Employee &other) {
    if (this != &other) {
      User::operator=(other);
      job = other.job;
    }
    return *this;
  }

  IEntity *copy() const override { return new Employee(*this); }

  void assign(const IEntity &other) override {
    const Employee *e = dynamic_cast<const Employee *>(&other);
    if (e) {
      User::assign(*e);
      job = e->job;
    }
  }

  void destroy() override { delete this; }

  void showInfo() const override {
    cout << "Name: " << name << endl;
    cout << "Surname: " << surname << endl;
    cout << "Age: " << age << endl;
    cout << "Login: " << login << endl;
    cout << "Job: " << job << endl;
  }

  void performAction() override {
    cout << name << " performs employee actions." << endl;
  }

  bool isEqual(const IEntity &other) const override {
    const Employee *e = dynamic_cast<const Employee *>(&other);
    if (!e)
      return false;
    return login == e->login;
  }

  string getJob() const { return job; }
  void setJob(string j) { job = j; }
};

#endif
