#pragma once

#include <string>
#include <cstddef>
#include "CMenuItem.h"

using namespace std;


namespace XXX {
    class CMenu {
    public:
        CMenu(string, CMenuItem *, size_t);
        int getSelect() const;
        bool isRun() const;
        string getTitle();
        size_t getCount() const;
        CMenuItem *getItems();
        void print();
        int runCommand();
    private:
        int select{-1};
        size_t count{};
        bool running{};
        string title{};
        CMenuItem *items{};
    };
}