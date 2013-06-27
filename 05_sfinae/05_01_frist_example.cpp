// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 15:43:02 EDT
// File:    05_01_frist_example.cpp

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

//=================== template functions ===================
//doesn't work for int since int doesn't have size_type
template<typename T>
void fct(typename T::size_type t) {
    PRINT_YELLOW(TYPE(T) << " has size_type")
}
//doesn't work for foo bc the argument given is 10 and not convertable to foo
template<typename T>
void fct(T t) {
    PRINT_RED(TYPE(T) << " has no size_type")
}
//============== a type that has a typedef size_type ==============
struct foo {
    typedef int size_type;
};


//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter button to continue
    fct<foo>(10);
    
    WAIT_FOR_INPUT()
    fct<int>(10);
    
    WAIT_FOR_INPUT()
    PRINT_GREEN("SFINAE")
    PRINT_GREEN("Substitution Failure Is Not An Error")
    
    return 0;
}
