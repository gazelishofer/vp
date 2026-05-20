#!/bin/bash
set -e

cd "$(dirname "$0")"

case "$(uname -s)" in
    MINGW*|MSYS*|CYGWIN*) BIN=program.exe ;;
    *)                    BIN=program ;;
esac

g++ -std=c++14 -o "$BIN" \
    main.cpp \
    menu/CMenu.cpp \
    menu/CMenuItem.cpp \
    ../Models/Employee/Employee.cpp \
    ../Models/Product/Product.cpp \
    ../Models/Supplier/Supplier.cpp \
    ../Models/User/User.cpp \
    -I. -I../Models

echo "Compiled: $BIN"
echo "Running $BIN..."
"./$BIN"
