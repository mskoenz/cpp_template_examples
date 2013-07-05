// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 22:23:09 EDT
// File:    introduction.cpp

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

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    WAIT_FOR_INPUT() //just hit the enter button to continue
    
    //~ PRINT_GREEN("  name:           Mario Könz")
    //~ WAIT_FOR_INPUT()
    //~ PRINT_GREEN("  study:          interdisciplinary science ETH Zuerich")
    //~ WAIT_FOR_INPUT()
    //~ PRINT_GREEN("  main subject:   physics and computational science")
    //~ WAIT_FOR_INPUT()
    //~ PRINT_GREEN("  c++ experience: 3 semesters programming techniques with Matthias Troyer")
    //~ PRINT_GREEN("                  worked 2 years on the ALPS library")
    //~ WAIT_FOR_INPUT()
    //~ PRINT_GREEN("  why am I here:  writing my master-thesis with Roger Melko")
    //~ WAIT_FOR_INPUT()
    CLR_SCR()
    //~ WAIT_FOR_INPUT()
    PRINT_YELLOW("  content")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  1: demonstration/polymorphism")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  2: template motivation")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  3: template basics")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  4: mean trait")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  5: central mechanism: SFINAE")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  6: pitfalls")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  7: concept programming")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  8: summary")
    WAIT_FOR_INPUT()
    CLR_SCR()
    //~ WAIT_FOR_INPUT()
    //~ PRINT_YELLOW("  majority of the examples works without c++0x")
    //~ WAIT_FOR_INPUT()
    //~ PRINT_YELLOW("  those few examples that need c++0x can also be realised with just boost")
    WAIT_FOR_INPUT()
    PRINT_YELLOW("  all examples are available on GitHub")
    PRINT_YELLOW("  https://github.com/mskoenz/cpp_template_examples")
    WAIT_FOR_INPUT()
    PRINT_RED("  ask questions if you don't get something!")
    
    return 42;
}
