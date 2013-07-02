// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.07.2013 15:31:01 EDT
// File:    08_09_partial_specialisation.cpp

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

//-------------- partial specialisation for T == int ---------------
template<typename U>
void print_pair(std::pair<int, U> const & p) {
    PRINT_RED("pairs with an integer in the first place cannot be printed")
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    PRINT_CYAN("press enter to continue")
    
     
    WAIT_FOR_INPUT()//just hit the enter key to continue
    std::pair<int   , int   > p1(1  , 2  );
    print_pair(p1); //the specialisation is used
    
    WAIT_FOR_INPUT()
    std::pair<double, int   > p2(3.1, 4  );
    print_pair(p2);
    
    WAIT_FOR_INPUT()
    std::pair<int   , double> p3(5  , 6.1);
    print_pair(p3); //the specialisation is used
    
    WAIT_FOR_INPUT()
    std::pair<double, double> p4(7.1, 8.1);
    print_pair(p4);
    
    return 0;
}

