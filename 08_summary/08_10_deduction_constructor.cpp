// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.07.2013 15:46:13 EDT
// File:    08_10_deduction_constructor.cpp

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

//------------------- print pair -------------------
//it's no problem to deduce T and U "through" the pair
template<typename T, typename U>
void print_pair(std::pair<T, U> const & p) {
    PRINT_GREEN("(" << p.first << "/" << p.second << ")")
}

//------------------- custom make_pair -------------------
template<typename T, typename U>
inline std::pair<T, U> make_pair(T const & t, U const & u) {
    PRINT_YELLOW("created a pair")
    return std::pair<T, U>(t, u);
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //NEEDS c++11 for auto at the bottom
    PRINT_CYAN("press enter to continue")
    
     
    std::pair<int, int> p1(1, 2);
    
    WAIT_FOR_INPUT()//just hit the enter key to continue
    print_pair(p1); //deduction is no problem
    
    WAIT_FOR_INPUT()
    print_pair(std::pair<int, int>(3, 4)); //quite cumbersome...
    
    WAIT_FOR_INPUT()
    print_pair(make_pair(5, 6)); //deduction via function
    
    WAIT_FOR_INPUT()
    //the std already has make_pair
    print_pair(std::make_pair(7, 8)); //deduction via function
    
    //the reason for not having constructor deduction:
    //The C++ Programming Language, Third Edition by Bjarne Stroustr
    /*
    
    Note that class template parameters are never deduced. The reason is 
    that the flexibility provided by several constructors for a class 
    would make such deduction impossible in many cases and obscure in 
    many more. Specialization provides a mechanism for implicitly 
    choosing between different implementations of a class (§13.5). 
    If we need to create an object of a deduced type, we can often do 
    that by calling a function to do the creation; see make_pair()
    
    */
    
    WAIT_FOR_INPUT()
    //Why you want c++11:
    
    //auto deduced the type that return from a function
    //we never have to write std::pair<double ,std::string>
    auto p2 = std::make_pair(1.2, "text");
    print_pair(p2);
    
    return 0;
}
