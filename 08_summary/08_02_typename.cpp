// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 22:15:37 EDT
// File:    08_02_typename.cpp

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

//typename is used for two purposes:

//first: it's used when declearing templates and just says that whatever 
//follows (T) is a type.
template<typename T>
struct my_template {
    typedef int int_type;
};

//second: to extract types that are inside a template struct/class and 
//depend somehow on the template parameter (dependent scope)
//basically the following pattern ....<T>...::some_type
template<typename T>
struct my_second_template {
    typedef typename my_template<T>::int_type second_int_type;
    //i need typename here because int_type is inside a struct that depends
    //on the template parameter T. Just remove typename to see the error
};

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    
    //no need for typename here, since there is no unknown T-dependency
    //T==int an all is good :-)
    my_template<int>::int_type nr1 = 0;
    
    //same here
    my_second_template<int>::second_int_type nr2 = 0;
    
    PRINT_GREEN(nr1)
    PRINT_GREEN(nr2)
    
    return 0;
}

