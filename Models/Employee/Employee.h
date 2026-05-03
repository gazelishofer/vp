#ifndef LR2_CLASS2_H
#define LR2_CLASS2_H
#include "../User/User.h"


class Employee : public User {

private:

    string job;


public:


    Employee(string n, string s, int a, string l, string p, string j)
        : User(n, s, a, l, p), job(j) {}


    void showInfo() override;
    void performAction() override;

    string getJob() {
        return job;
    }

    void setJob(string j) {
        job = j;
    }


};




#endif //LR2_CLASS2_H