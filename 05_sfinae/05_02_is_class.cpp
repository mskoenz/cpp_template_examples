// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 16:15:26 EDT
// File:    05_02_is_class.cpp

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

//=================== is_class trait ===================
template<typename T> 
struct is_class {
    //second templates is needed since U::* is illegal for non class types
    //SFINAE prevents illegal code from being instantiated
    //U::* is sufficient to identify classes and structs since they have a
    //destructor that isn't allowed to take paremeter hence void(U::*)(void)
    //and NULL is convertable to the method-pointer
    template<typename U>
    static char check(void(U::*)());
    template<typename U>
    static double check(...); //just catch anything else (variadic function)
    
    enum { value = (sizeof(char) == sizeof(check<T>(NULL))) };
};
//=================== some classes ===================
struct foo_struct {
};

class bar_class {
};

enum baz_enum {
};

template<typename T>
void class_check(T const & t) {
    if(is_class<T>::value)
        PRINT_YELLOW(TYPE(T) << " is a class-type")
    else
        PRINT_RED(TYPE(T) << " is no class-type")
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter key to continue
    class_check(foo_struct());
    
    WAIT_FOR_INPUT()
    class_check(bar_class());
    
    WAIT_FOR_INPUT()
    class_check(baz_enum());
    
    WAIT_FOR_INPUT()
    class_check(10.0);
    
    WAIT_FOR_INPUT()
    class_check(10);
    
    WAIT_FOR_INPUT()
    PRINT_GREEN("everything you can know about an object is also known to the compiler")
    
    return 0;
}
