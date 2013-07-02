// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 16:38:14 EDT
// File:    05_04_std_traits.cpp

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
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp> //enable_if is now part c++11

//=================== a fct with enable if ===================
//enable_if<cond, T>::type will be T if cond == true and fail 
//if cond == false. disable_if does the opposite
template<typename T>
typename boost::enable_if<boost::has_plus<T>, void>::type fct(T const & t) {
    PRINT_YELLOW("fct for " << TYPE(T) << " with +")
    t + t;
}
template<typename T>
typename boost::disable_if<boost::has_plus<T>, void>::type fct(T const & t) {
    PRINT_RED("fct for " << TYPE(T) << " without +")
}
//if there is only one parameter, put enable_if on the return type
//=================== some types ===================
struct foo {};

foo operator+(foo const & a, foo const & b){
    return foo();
}

struct bar {
    void operator+(bar const & a) const {
    }
};

struct no_plus {
};

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter key to continue
    fct(foo());
    
    WAIT_FOR_INPUT()
    fct(bar());
    
    WAIT_FOR_INPUT()
    fct(no_plus());
    
    WAIT_FOR_INPUT()
    fct(int());
    
    WAIT_FOR_INPUT()
    PRINT_GREEN("with dis/enable_if ambiguous-errors are no longer a problem");
    
    return 0;
}
