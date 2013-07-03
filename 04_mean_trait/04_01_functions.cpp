// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 13:54:24 EDT
// File:    04_01_functions.cpp

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

//=================== mean function ===================
inline double mean(int const & a, int const & b) {
    PRINT_RED("mean fct version int with arg " << a << " and " << b);
    return (a + b) / 2.0;
}


//~ inline double mean(double const & a, double const & b) {
    //~ PRINT_GREEN("mean fct version double with arg " << a << " and " << b);
    //~ return (a + b) / 2.0;
//~ }


//~ inline long double mean(long double const & a, long double const & b) {
    //~ PRINT_MAGENTA("mean fct version long double with arg " << a << " and " << b);
    //~ return (a + b) / 2.0;
//~ }


//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter key to continue
    PRINT_NAMED( mean(1, 2) )
    
    WAIT_FOR_INPUT()
    //~ PRINT_NAMED( mean(1.8, 2.0) )
    
    WAIT_FOR_INPUT()
    //~ PRINT_NAMED( mean(1.8l, 2.0l) )
    
    WAIT_FOR_INPUT()
    //~ PRINT_RED("        sizeof(int) =  " << sizeof(int) << " bytes")
    //~ PRINT_GREEN("     sizeof(double) =  " << sizeof(double) << " bytes")
    //~ PRINT_MAGENTA("sizeof(long double) = " << sizeof(long double) << " bytes")
    //we cannot just use the mean version double for all types since it 
    //is not efficient for smaller types and not accurate for larger types
    
    return 0;
}
