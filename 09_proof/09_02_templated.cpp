// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.07.2013 20:37:37 EDT
// File:    09_02_templated.cpp

#include <iostream>
#include <typeinfo>

template<typename T, int i>
struct get_type {
    typedef typename get_type<T, i-1>::type type;
};
template<typename T>
struct get_type<T, 0> {
    typedef T type;
};
//~ typename get_type<void, 800>::type print() {

template<typename T>
class custom_class {
public:
    custom_class(): i(1), j(2), k(3) {
    }
    void print() {
        std::cout << i << "/" << j << "/" << k << std::endl;
    }
private:
    T i;
    T j;
    T k;
};

int main(int argc, char* argv[]) {
    custom_class<int> c1;
    c1.print();
    std::cout << typeid(c1).name() << std::endl;
    
    custom_class<double> c2;
    c2.print();
    std::cout << typeid(c2).name() << std::endl;
    
    custom_class<float> c3;
    c3.print();
    std::cout << typeid(c3).name() << std::endl;
    
    return 0;
}
