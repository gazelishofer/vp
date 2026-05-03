
#ifndef LR2_USER_H
#define LR2_USER_H
#include <string>
using namespace::std;


class User {

private:
    string name;
    string surname;
    int age;
    string login;
    string password;

public:

    virtual ~User() = default;


    User(string n, string s, int a, string l, string p) {
        name = n;
        surname = s;
        age = a;
        login = l;
        password = p;
    }

    virtual void showInfo() = 0;
    virtual void performAction() = 0;

    void setName(string n) {
        name = n;
    }
    void setSurname(string s) {
        surname = s;
    }
    void setAge(int a) {
        age = a;
    }
    void setLogin(string l) {
        login = l;
    }
    void setPassword(string p) {
        password = p;
    }


    string getName() {
        return name;
    }
    string getSurname() {
        return surname;
    }
    int getAge() {
        return age;
    }
    string getLogin() {
        return login;
    }
    string getPassword() {
        return password;
    }


};


#endif //LR2_USER_H