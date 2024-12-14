#include <iostream>
#include "max_multiple.h"
#include <Windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    int divider, bound;
    std::cin >> divider >> bound;
    std::cout << "MAX_Number: " << maxMultiple(divider, bound) << std::endl;

    return 0;
}