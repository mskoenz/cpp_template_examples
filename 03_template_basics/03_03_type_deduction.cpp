// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 20:39:46 EDT
// File:    03_03_type_deduction.cpp

//========= some macros for nicer presentation (not essential) =========
//use as litte macros as possible in c++ (most stuff can be solved without)
//I just use them here to keep the unimportant stuff away from the main code
#define TYPE(T) typeid(T).name()
#define CLR_SCR() std::cout << "\033[2J\033[100A";
#define NEW_LINE() std::cout << std::endl;
#define WAIT_FOR_INPUT() while(std::cin.gcount() == 0) std::cin.get(); std::cin.get();
#define ASSERT_MSG(cond, msg) if(cond) {PRINT_RED(msg); throw std::runtime_error("error");}
#define PRINT_NAMED(x) std::cout << #x << " = " << x << std::endl; //#x changes the variable name into a string "x"
#define PRINT_CALL(x) std::cout << #x << ": "; x;
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

//=================== template struct ===================
template<typename T>
struct my_template {
    template<typename U>
    void print(U const & t) {
        PRINT_RED("T = " << TYPE(T) << ", U = " << TYPE(U) << ", val = " << t)
    }
};

//=================== template function ===================
template<typename T>
void print_deduce(T const & t) {
    PRINT_YELLOW("T = " << TYPE(T) << ", val = " << t)
}

template<typename T>
void print_no_deduce(int const & t) {
    PRINT_GREEN("T = " << TYPE(T) << ", val = " << t)
}
//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    my_template<int> t; //<int> is mandatory. the compiler has no chance guess the type
    
    WAIT_FOR_INPUT() //just hit the enter button to continue
    PRINT_CALL(print_deduce(1.5)) //type deduction works 1.5 is int -> T = double
    
    WAIT_FOR_INPUT()
    PRINT_CALL(print_deduce<int>(1.5)); //is also fine, but 1.5 will be converted to int
    
    //~ PRINT_CALL(print_no_deduce(1.5)) //doesn't work since the compiler cannot do type deduction
    WAIT_FOR_INPUT()
    PRINT_CALL(print_no_deduce<double>(1.5))
    
    WAIT_FOR_INPUT()
    PRINT_CALL(t.print(1.5))
    
    WAIT_FOR_INPUT()
    PRINT_CALL(t.print(1))
    
    WAIT_FOR_INPUT()
    PRINT_CALL(t.print<float>(1))
    
    return 0;
}
