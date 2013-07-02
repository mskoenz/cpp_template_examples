// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.07.2013 15:30:57 EDT
// File:    08_08_full_specialisation.cpp

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

//note: I use functions here, but this is a template effect
//      It has nothing todo with overloading

//------------------- templated print fct -------------------
template<typename T>
void print(T const & t) {
    PRINT_GREEN(t);
}

//------------------- full specialisation for int -------------------
template<>
void print<int>(int const & t) {
    PRINT_RED("integers cannot be printed")
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    PRINT_CYAN("press enter to continue")
    
    int i = 10;
    double d = 3.14;
    std::string s = "hello world";
     
    WAIT_FOR_INPUT()//just hit the enter key to continue
    print(i); //the specialisation is used
    
    WAIT_FOR_INPUT()
    print(s);
    
    WAIT_FOR_INPUT()
    print(d);
    
    return 0;
}

