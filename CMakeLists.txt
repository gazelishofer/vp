cmake_minimum_required(VERSION 4.0)
project(Labb2)

set(CMAKE_CXX_STANDARD 14)

include_directories(TestMenu/menu)

add_executable(TestMenu
        TestMenu/menu/CMenu.cpp
        TestMenu/menu/CMenu.h
        TestMenu/menu/CMenuItem.cpp
        TestMenu/menu/CMenuItem.h
        TestMenu/main.cpp
        Models/Employee/Employee.cpp
        Models/Product/Product.cpp
        Models/Supplier/Supplier.cpp
        Models/User/User.cpp)
