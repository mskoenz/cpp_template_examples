// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 14:55:13 EDT
// File:    04_04_concept_trait.cpp

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

//=================== mean_trait_chooser ===================
template<typename T, bool use_double>
struct mean_trait_chooser {
    typedef T type;
};
//------------------- partial specialsiation for nr == 1 -------------------
template<typename T>
struct mean_trait_chooser<T, true> {
    typedef double type;
};
//=================== mean_type_identifier ===================
template<typename T>
struct mean_type_identifier {
    static T t;
    
    static char check(T);
    static double check(double);
    
    enum {value = (sizeof(check((t+t)/double(1))) == sizeof(double))};
};
//------------------- full specialisation -------------------
template<>
struct mean_type_identifier<double> {
    enum {value = false}; //doesn't matter if true or false
};

//=================== better_mean_trait ===================
template<typename T>
struct better_mean_trait {
    typedef 
        typename 
            mean_trait_chooser<T, mean_type_identifier<T>::value>::type
    type;
};
//=================== mean template attempt 3 ===================
template<typename T>
typename better_mean_trait<T>::type mean(T const & a, T const & b) {
    PRINT_YELLOW
    ("mean fct version " << TYPE(T) << " with arg " << a << " and " << b);
    return (a + b) / 2.0;
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter button to continue
    PRINT_NAMED(mean(1, 2))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1.8, 2.0))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1.8l, 2.0l))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1u, 2u))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1lu, 2lu))
    
    WAIT_FOR_INPUT()
    PRINT_GREEN("works for all types! \nrelays on the concept and not on actual names")
    
    return 0;
}
