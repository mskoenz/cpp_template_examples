// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 18:03:51 EDT
// File:    03_01_header.hpp

#ifndef __03_01_HEADER_HEADER
#define __03_01_HEADER_HEADER

#define TYPE(T) typeid(T).name()
#include <typeinfo>
#include <iostream>

class my_class {
public:
    void print() {
        std::cout << "my_class::print()" << std::endl;
    }
};

template<typename T>
struct my_template {
    void print() {
        std::cout << "my_template<" << TYPE(T) << ">::print()" << std::endl;
    }
};

#endif //__03_01_HEADER_HEADER
