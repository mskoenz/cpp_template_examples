// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.07.2013 20:37:41 EDT
// File:    09_01_handwritten.cpp

#include <iostream>
#include <typeinfo>

class custom_classIiE {
public:
    custom_classIiE(): i(1), j(2), k(3) {
    }
    void print() {
        std::cout << i << "/" << j << "/" << k << std::endl;
    }
private:
    int i;
    int j;
    int k;
};

class custom_classIdE {
public:
    custom_classIdE(): i(1), j(2), k(3) {
    }
    void print() {
        std::cout << i << "/" << j << "/" << k << std::endl;
    }
private:
    double i;
    double j;
    double k;
};

class custom_classIfE {
public:
    custom_classIfE(): i(1), j(2), k(3) {
    }
    void print() {
        std::cout << i << "/" << j << "/" << k << std::endl;
    }
private:
    float i;
    float j;
    float k;
};

int main(int argc, char* argv[]) {
    custom_classIiE c1;
    c1.print();
    std::cout << typeid(c1).name() << std::endl;
    
    custom_classIdE c2;
    c2.print();
    std::cout << typeid(c2).name() << std::endl;
    
    custom_classIfE c3;
    c3.print();
    std::cout << typeid(c3).name() << std::endl;
    
    
    return 0;
}
