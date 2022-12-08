#include <iostream>
#include "sum.h"
#include "divide.h"

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << sum(a, b) << "\n" << divide(a, b) << "\n";
    return 0;
}