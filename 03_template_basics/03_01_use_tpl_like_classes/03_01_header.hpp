// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 18:03:51 EDT
// File:    03_01_header.hpp

#ifndef __03_01_HEADER_HEADER
#define __03_01_HEADER_HEADER

#include <iostream>

class my_class {
public:
    void print();
};

template<typename T>
struct my_template {
    void print();
};

#endif //__03_01_HEADER_HEADER
