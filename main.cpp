#include "Generator.hpp"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    
//создание обьекта 
    Generator gen;
    
    std::cin >> gen;
    gen.generate();
    std::cout << gen;
    
    return 0;
}

