// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 22:46:04 EDT
// File:    08_04_asserts.cpp

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
#include <assert.h>
#include <stdexcept> //for runtime errors

double read_fct() {
    double res;
    PRINT_GREEN("please enter a number: ")
    std::cin >> res;
    return res;
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    
    //asserts from the <assert.h> header are very useful to make sure 
    //the state of your program is actually the way you think it is
    
    //p could be a probability
    double p = 0;
    
    //do whatever
    p = read_fct();
    
    //since I know p is a probability, it should be between 0 and 1.
    //an assert can check that and you don't loose performance because
    //all asserts vanish if compiled with -DNDEBUG
    assert(p >= 0 and p <= 1);
    
    //change the return in fct to see the fail
    //leave the "fail" and compile with -DNDEBUG to disable the assert
    
    //IMPORTANT: if you turn off the assertion, you have no security anymore
    //for critical checks use if and throw an error like this:
    
    if(p < 0 or p > 1)
        throw std::runtime_error("p must be between 0 and 1");
    
    return 0;
}
