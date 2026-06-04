#include "CMenu.h"
#include "CMenuItem.h"
#include <iostream>
#include <limits>

using namespace std;

namespace XXX {

CMenu::CMenu(string title, CMenuItem *items, size_t count)
    : title(title), items(items), count(count) {}

void CMenu::print() {
  cout << "\n===== " << title << " =====\n";
  for (size_t i = 0; i < count; ++i) {
    cout << i + 1 << ". ";
    items[i].print();
    cout << endl;
  }
}

int CMenu::runCommand() {
  int select;
  while (true) {
    print();
    cout << "\n   Select >> ";

    if (cin >> select) {
      if (select >= 1 && select <= static_cast<int>(count)) {
        return items[select - 1].run();
      } else {
        cout << "Invalid choice! Please enter 1-" << count << endl;
      }
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input! Please enter a number." << endl;
    }
  }
}

} // namespace XXX
