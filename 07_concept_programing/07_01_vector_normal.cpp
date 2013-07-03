// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 20:10:18 EDT
// File:    07_01_vector_normal.cpp

//========= some macros for nicer presentation (not essential) =========
//use as litte macros as possible in c++ (most stuff can be solved without)
//I just use them here to keep the unimportant stuff away from the main code
#define TYPE(T) typeid(T).name()
#define CLR_SCR() std::cout << "\033[2J\033[100A";
#define NEW_LINE() std::cout << std::endl;
#define WAIT_FOR_INPUT() while(std::cin.gcount() == 0) std::cin.get(); std::cin.get();
#define ASSERT_MSG(cond, msg) if(cond) {PRINT_RED(msg); throw std::runtime_error("error");}
#define PRINT_NAMED(x) std::cout << #x << " = " << x << std::endl; //#x changes the variable name into a string "x"
#define PRINT_RED(x) std::cout << "\033[1;31m" << x << "\033[0m" << std::endl; 
#define PRINT_BLUE(x) std::cout << "\033[1;34m" << x << "\033[0m" << std::endl;
#define PRINT_CYAN(x) std::cout << "\033[1;36m" << x << "\033[0m" << std::endl;
#define PRINT_GREEN(x) std::cout << "\033[1;32m" << x << "\033[0m" << std::endl;
#define PRINT_YELLOW(x) std::cout << "\033[1;33m" << x << "\033[0m" << std::endl;
#define PRINT_MAGENTA(x) std::cout << "\033[1;35m" << x << "\033[0m" << std::endl;
//all the \033... cmd are bash specific. See http://www.cplusplus.com/forum/unices/36461/ for details

//=================== includes ===================
#include <iostream>
#include <typeinfo>
#include <vector>
#include <array>

//=================== vector_class ===================
template<typename T>
class my_vector {
public:
    typedef typename std::vector<T>::size_type size_type;
    //------------------- ctor -------------------
    my_vector(): vec_() {}
    my_vector(size_type const & N): vec_(N) {}
    my_vector(size_type const & N, T const & val): vec_(N, val) {}
    
    //copy ctor
    my_vector(my_vector const & arg): vec_(arg.vec_) {}
    
    //assignment
    my_vector & operator=(my_vector const & rhs) {
        vec_ = rhs.vec_;
        return (*this);
    }
    //------------------- getter -------------------
    T & operator[](size_type const & pos) {
        return vec_[pos];
    }
    T const & operator[](size_type const & pos) const {
        return vec_[pos];
    }
    //------------------- info -------------------
    size_type size() const {
        return vec_.size();
    }
private:
    std::vector<T> vec_;
};
//------------------- just the print function -------------------
template<typename T>
std::ostream & operator<<(std::ostream & os, my_vector<T> const & arg) {
    os << "[";
    for(typename my_vector<T>::size_type i = 0; i < arg.size(); ++i) {
        os << arg[i];
        if(i != arg.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}



//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //NEEDS -std=c++11 for std::array
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    std::vector<bool> std_vec(10);
    std::array<double, 10> std_array;
    
    WAIT_FOR_INPUT() //just hit the enter key to continue
    my_vector<int> int_vec(10, 1);
    PRINT_YELLOW(int_vec)
    
    //~ my_vector<double> double_vec(int_vec);
    
    //~ my_vector<bool> bool_vec(std_vec);
    
    //~ double_vector = bool_vec;
    
    //~ int_vec = std_array;
    
    return 0;
}
