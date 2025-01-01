#include <iostream>

std::string test = "/squeeze:ownId,tags";

int main() {
    test.erase(0, 9);
    std::cout << test;
}