// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 17:14:37 EDT
// File:    05_03_has_method.cpp

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

//============ trait to figure out if T::print() exists ============
template<typename T>
struct has_print_method {
    
    template<void(T::*)(void)> //specify the exact signature here
    struct helper {
        typedef int type;
    };
    
    template<typename U>
    static char check(typename helper<&U::print>::type); //name of method
    template<typename U>
    static double check(...);
    
    enum { value = (sizeof(char) == sizeof(check<T>(0))) };
};

//=================== some types ===================
struct foo {
    void print() {
    }
};
struct bar {
    void print(int a) {
    }
};
struct baz {
    void no_print() {
    }
};

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter key to continue
    PRINT_NAMED(has_print_method<foo>::value);
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(has_print_method<bar>::value);
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(has_print_method<baz>::value);
    
    WAIT_FOR_INPUT()
    PRINT_GREEN("every method (with exact signature) can be found");
    
    //~ PRINT_NAMED(has_method<int>::value);
    //doesn't work because &int:: is illegal and illegal code shouldn't be
    //in a struct-"body"
    //one would first to check if it is a class 
    //after checking for method (enable_if(is_class<...>)) see 05_04
    
    return 0;
}
