// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 12:34:29 EDT
// File:    02_01_wrong_way.cpp

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
#include <assert.h> //use asserts! It will make your debugging way easier
                    //and it doesn't cut into the performance (-DNDEBUG)

//=================== double_5_class ===================
class double_5_class {
public:
    double & operator[](int const & index) {
        assert(index >= 0 and index < 5);
        return array_[index];
    }
private:
    double array_[5];
};

//=================== double_10_class ===================
class double_10_class {
public:
    double & operator[](int const & index) {
        assert(index >= 0 and index < 10);
        return array_[index];
    }
private:
    double array_[10];
};

//=================== int_10_class ===================
class int_10_class {
public:
    int & operator[](int const & index) {
        assert(index >= 0 and index < 10);
        return array_[index];
    }
private:
    int array_[10];
};

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //NEEDS -std=c++0x for uint
    //just typedef unsigned int uint; to get rid of it
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter button to continue
    double_5_class d5;
    
    for(uint i = 0; i < 5; ++i)
        d5[i] = i + 0.1;
    
    for(uint i = 0; i < 5; ++i)
        PRINT_RED("d5[" << i << "] = " << d5[i])
    
    
    
    WAIT_FOR_INPUT()
    double_10_class d10;
    
    for(uint i = 0; i < 10; ++i)
        d10[i] = i + 0.1;
    
    for(uint i = 0; i < 10; ++i)
        PRINT_YELLOW("d10[" << i << "] = " << d10[i])
    
    
    
    WAIT_FOR_INPUT()
    int_10_class i10;
    
    for(uint i = 0; i < 10; ++i)
        i10[i] = i + 0.1;
    
    for(uint i = 0; i < 10; ++i)
        PRINT_GREEN("i10[" << i << "] = " << i10[i])
    
    return 0;
}
