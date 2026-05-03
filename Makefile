CXX      := g++
CXXFLAGS := -std=c++14 -Wall
BIN      := /tmp/testmenu

SRCS := TestMenu/main.cpp \
        Models/Employee/Employee.cpp \
        Models/Product/Product.cpp \
        Models/Supplier/Supplier.cpp \
        Models/User/User.cpp \
        TestMenu/menu/CMenu.cpp \
        TestMenu/menu/CMenuItem.cpp

.PHONY: all build run clean

all: run

build:
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRCS)

run: build
	$(BIN)

clean:
	rm -f $(BIN)
