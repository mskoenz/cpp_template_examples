// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    05.07.2013 14:43:55 EDT
// File:    05_02_has_type.cpp

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

//=================== sidenote ===================
template<typename T, typename S = typename T::size_type> //is legal
struct my_template {
};
//=================== has_size_type ===================
template<typename T>
struct has_size_type {
    
    template<typename U>
    static char check(typename U::size_type * i);
    
    template<typename U>
    static double check(...);
    
    enum {value = (sizeof(check<T>(NULL)) == sizeof(char))};
};
//============== a type that has a typedef size_type ==============
struct foo {
    typedef int size_type;
};

struct bar {
    
};

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter key to continue
    PRINT_NAMED(has_size_type<bar>::value)
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(has_size_type<foo>::value)
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(has_size_type<int>::value)
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(has_size_type<std::vector<int>>::value)
    
    WAIT_FOR_INPUT()
    PRINT_GREEN("we can find out if a type contains a typedef")
    
    return 0;
}
