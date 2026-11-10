#include "DynamicArray.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>

int main() {
    std::cout << "Task 1" << std::endl;
    DynamicArray<int> a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);
    try {
        a.set(0, 500);
    } catch (const std::invalid_argument& e) {
        std::cout << "int: " << e.what() << std::endl;
    }

    DynamicArray<double> d(2);
    d.set(0, 500.5);
    d.set(1, -1000.25);

    DynamicArray<std::string> s(0);
    s.push_back("hello");
    s.push_back("world");

    std::cout << std::endl << "Task 2" << std::endl;
    std::cout << "int: " << a << std::endl;
    std::cout << "double: " << d << std::endl;
    std::cout << "string: " << s << std::endl;

    std::cout << std::endl << "Task 3" << std::endl;
    DynamicArray<int> p(2);
    DynamicArray<int> q(2);
    q.set(0, 3);
    q.set(1, 4);
    std::cout << "distance(" << p << ", " << q << ") = " << p.distance(q) << std::endl;

    try {
        a.distance(p);
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << std::endl;
    }

    try {
        s.distance(s);
    } catch (const std::bad_typeid& e) {
        std::cout << "bad_typeid: " << e.what() << std::endl;
    }

    return 0;
}