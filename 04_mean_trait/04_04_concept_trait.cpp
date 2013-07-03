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

//=================== mean_type_identifier ===================
template<typename T>
struct use_double_identifier {
    static T t;
    
    static char check(T);
    static double check(double);
    
    enum {value = (sizeof(check((t+t)/double(1))) == sizeof(double))};
};
//------------------- full specialisation -------------------
template<>
struct use_double_identifier<double> {
    enum {value = true}; //doesn't matter if true or false
};

//=================== meta_if ===================
template<bool cond, typename T, typename F> //default true
struct meta_if {
    typedef T type;
};
//------------------- partial specialsiation for true -------------------
template<typename T, typename F>
struct meta_if<false, T, F> {
    typedef F type;
};

//=================== better_mean_trait ===================
template<typename T>
struct better_mean_trait {
    typedef 
        typename 
            meta_if<use_double_identifier<T>::value
                  , double
                  , T
        >::type
    type;
};
//=================== mean template attempt 3 ===================
template<typename T>
inline typename better_mean_trait<T>::type mean(T const & a, T const & b) {
    PRINT_YELLOW("mean fct version " << TYPE(T) << 
                 " with arg " << a << " and " << b);
    return (a + b) / 2.0;
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter key to continue
    PRINT_NAMED(use_double_identifier<int>::value)
    WAIT_FOR_INPUT()
    PRINT_NAMED(use_double_identifier<double>::value)
    WAIT_FOR_INPUT()
    PRINT_NAMED(use_double_identifier<uint>::value)
    WAIT_FOR_INPUT()
    PRINT_NAMED(use_double_identifier<long double>::value)
    
    WAIT_FOR_INPUT()
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
    PRINT_GREEN("works for all types!")
    PRINT_GREEN("relays on the concept and not on actual names")
    
    return 0;
}
