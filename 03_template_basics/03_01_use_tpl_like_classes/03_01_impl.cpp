#include <03_01_header.hpp>

void my_class::print() {
    std::cout << "my_class::print()" << std::endl;
}

template<typename T>
void my_template<T>::print() {
    std::cout << "my_template<" << TYPE(T) << ">::print()" << std::endl;
}

//explicit instantiation
template class my_template<int>;
template class my_template<double>;
