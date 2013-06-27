// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 11:57:50 EDT
// File:    01_04_runtime_prime.cpp

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

//=================== prime finder ===================
bool is_prime(int nr) {
    for(int i = 2; i < nr; ++i) {//not optimal, I know...sqrt(nr)
        if(nr % i == 0)
            return false;
    }
    return true;
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    //~ int const n = 10;
    int const n = 100;
    
    int res = 0;
    for(int i = n; i > 2; --i) {
        if(is_prime(i)) {
            res = i;
            break;
        }
        WAIT_FOR_INPUT() //just hit the enter button to continue
        PRINT_RED(i << " is not prime")
    }
    WAIT_FOR_INPUT()
    PRINT_GREEN(res << " is the biggest prime <= " << n)
    return 0;
}
