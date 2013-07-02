// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 22:46:00 EDT
// File:    08_05_static_asserts.cpp

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
//=================== includes ===================
#include <iostream>

template<int N>
struct accept_even_number_template {
    //it doesn't matter where you put the static assert
    //can be in the sturct, in a method/constructor of the struct
    //anywhere inside the struct is fine
    static_assert(N%2 == 0, "only even numbers!");
};



//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //NEEDS: c++11
    
    //works like an assert but during compiletime / no performance loss
    //at runtime ever
    static_assert(true, "Error: some nice message");
    //change true to false to see the error
    
    //effective in combination with templates
    accept_even_number_template<2> a;
    accept_even_number_template<4> b;
    
    //you can only insert constant stuff in the static assert since
    //it has to be known at compiletime
    //following won't work
    
    // bool b;
    // std::cin >> b;
    // static_assert(b, "Error: ");
    
    return 0;
}
