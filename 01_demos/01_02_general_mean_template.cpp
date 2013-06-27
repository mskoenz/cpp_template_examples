// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 11:00:18 EDT
// File:    01_02_general_mean_template.cpp

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

//=================== general mean trait ===================
//------------------- helper -------------------
template<int N>
struct char_array {
    char m[N];
};

template<typename T>
struct helper_1 {
    static char_array<1> check(T);
    //leave out 2 since it is U (here equal to T)
    static char_array<3> check(double);
    static char_array<4> check(...);
    
    //why a float instead of double? 
    //float is the "cheapest" floating type and
    //we want float if we put in two floats. For other types 
    //it will go to check(double) since double is "closest" 
    //to float
    enum{value = (sizeof(check((T() + T())/float(1))))
                 /sizeof(char)};
};

template<typename T>
struct helper_U {
    static char_array<1> check(T);
    //leave out 2 since it is U (equal to double)
    static char_array<3> check(double);
    static char_array<4> check(...);
    
    enum{value = (sizeof(check((T() + double())/float(1))))
                 /sizeof(char)};
};

template<typename U>
struct helper_T {
    //leave out 1 since it is T (equal to double)
    static char_array<2> check(U);
    static char_array<3> check(double);
    static char_array<4> check(...);

    enum{value = (sizeof(check((double() + U())/float(1))))
                 /sizeof(char)};
};

template<typename T, typename U>
struct helper_2 {
    template<int N>
    struct char_array {
        char m[N];
    };
    
    static char_array<1> check(T);
    static char_array<2> check(U);
    static char_array<3> check(double);
    static char_array<4> check(...);
    
    enum{value = (sizeof(check((T()+U())/float(1))))
                 /sizeof(char)};
};

template<typename T>
struct helper_2<T, T> {
    enum{value = helper_1<T>::value};
};

//------------------- make sure no double get in the helper_2 -------------------
template<typename T>
struct helper_2<T, double> {
    enum{value = helper_U<T>::value};
};
template<typename U>
struct helper_2<double, U> {
    enum{value = helper_T<U>::value};
};
template<>
struct helper_2<double, double> {
    enum{value = 1}; //anything between 1 and 3 is fine
};

//------------------- chooser -------------------
template<typename T, typename U, int nr>
struct mean_trait_chooser {
    //the default version has no type. if check(...) 
    //is called it will not compile, bc there is no type
};
template<typename T, typename U>
struct mean_trait_chooser<T, U, 1> {
    typedef T type;
};
template<typename T, typename U>
struct mean_trait_chooser<T, U, 2> {
    typedef U type;
};
template<typename T, typename U>
struct mean_trait_chooser<T, U, 3> {
    typedef double type;
};

//------------------- super mean trait -------------------
template<typename T, typename U>
struct super_mean_trait {
    typedef typename mean_trait_chooser<T, U, helper_2<T, U>::value>::type type;
};

//------------------- super mean template -------------------
template<typename T, typename U>
typename super_mean_trait<T, U>::type mean(T const & a, U const & b) {
    typedef typename super_mean_trait<T, U>::type return_type;
    PRINT_BLUE("mean was called with types " << TYPE(T) << " and " << TYPE(U) << ". ")
    PRINT_GREEN("The return type is " << TYPE(return_type))
    return (a + b) / 2.0;
}

//=================== my_type ===================
//------------------- has "asymetic" double addition -------------------
struct my_type {
    my_type(): data(0) {
    }
    my_type(double const & in): data(in) {
    }
    double data;
};

//------------------- double + my_type is not equal to ... -------------------
my_type operator+(double const & d, my_type const & c) {
    return c.data + d;
}
//------------------- my_type + double -------------------
double operator+(my_type const & c, double const & d) {
    return c.data + d;
}
my_type operator/(my_type const & c, double const & d) {
    return c.data/d;
}
std::ostream & operator<<(std::ostream & os, my_type const & c) {
    os << c.data;
    return os;
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
    PRINT_NAMED(mean(1u, 2u))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1.8, 2.0))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1ul, 2u))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1.8l, 2))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1.8, 2.0l))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(1.8f, 2.0f))
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(my_type(1), 2.0))

    WAIT_FOR_INPUT()
    PRINT_NAMED(mean(2.0, my_type(1)))
    
    return 0;
}
