#include "Employee.h"
#include <iostream>
using namespace ::std;

void Employee::showInfo() {
    cout << "[Employee]" << endl;
    cout << "Name: " << getName() << endl;
    cout << "Surname: " << getSurname() << endl;
    cout << "Age: " << getAge() << endl;
    cout << "Login: " << getLogin() << endl;
    cout << "Job: " << getJob() << endl;
}

void Employee::performAction() {
    cout << "Employee performs action..." << endl;
}
