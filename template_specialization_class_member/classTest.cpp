#include "classTest.hpp"
#include <iostream>

template<>
void templatedClass<ethDFPort>::read() {
    std::cout << "eth templated func called"<< std::endl;
}

