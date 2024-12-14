#include "BitString.h"
#include <iostream>

int main() {
    BitString bs1("110");
    BitString bs2("100");

    std::cout << "BitString 1: " << bs1 << std::endl;
    std::cout << "BitString 2: " << bs2 << std::endl;

    BitString result = bs1 | bs2;
    std::cout << "AND Result: " << result << std::endl;

    return 0;
}
