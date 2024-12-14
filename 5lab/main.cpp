#include <iostream>
#include "linked_list.h"

int main() {
    FixedMemoryResource memory_resource(64, 1024);
    DoublyLinkedList<int> int_list(&memory_resource);
    int_list.push_back(10);
    int_list.push_back(20);
    int_list.push_back(30);
    std::cout << "2 int";
    for (const auto& elem : int_list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    struct ComplexType {
        int id;
        std::string name;
    };

    return 0;
}
