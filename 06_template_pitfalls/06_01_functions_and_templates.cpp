// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 18:55:23 EDT
// File:    06_01_functions_and_templates.cpp

//=================== good detailed explanation ===================
//http://www.gotw.ca/publications/mill17.htm

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

//=================== normal functions ===================
void print(int i, bool b) {
    PRINT_RED("normal function")
}
//=================== full template function ===================
template<typename T, typename U>
void print(T i, U b) {
    PRINT_MAGENTA("base template normal")
}
//full specialisation of template normal
template<>
void print<>(int * i, bool b) {
    PRINT_MAGENTA("spec template normal")
}
template<typename T, typename U>
void print(T * i, U b) {
    PRINT_CYAN("base template pointer")
}
//full specialisation of template pointer
template<>
void print<>(int * i, bool b) {
    PRINT_CYAN("spec template pointer")
}
//=================== partial template function ===================
//because of function overloading there is no partial specialisation
//for functions. The following function can be seen as a partial
//specialised one for T == int
template<typename U>
void print(int i, U b) {
    PRINT_YELLOW("partial template function")
}


//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    int * i_ptr = NULL;
    
    WAIT_FOR_INPUT() //just hit the enter button to continue
    PRINT_CALL(print(1, true))
    PRINT_GREEN("if there is a matching normal function it is always prefered")
    
    WAIT_FOR_INPUT()
    PRINT_CALL(print(1, 1))
    PRINT_GREEN("if no matching normal function is found the best")
    PRINT_GREEN("least-templated function is choosen")
    
    WAIT_FOR_INPUT()
    PRINT_CALL(print(1.0, true))
    PRINT_GREEN("in any other case the best base template is choosen")
    
    WAIT_FOR_INPUT()
    PRINT_CALL(print(i_ptr, true))
    PRINT_GREEN("...only after finding the best base template")
    PRINT_GREEN("its specialisations are considered")
    //That's why the fully spec-version of base template normal is never choosen here
    //base template pointer is the better fit, and after that decision specs are
    //searched (doen't matter if there are any)
    
    return 0;
}
