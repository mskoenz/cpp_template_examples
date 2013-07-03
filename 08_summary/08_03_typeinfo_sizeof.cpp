// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 22:34:33 EDT
// File:    08_03_typeinfo_sizeof.cpp

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
#include <typeinfo>

namespace example {
    template<typename T>
    struct my_struct {
        
    };
    
}//end namespace example

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    
    //sizeof() tells you how many bytes a type has. It's a one of a kind
    //function since it transforms types into integers. 
    //But you can also insert actual objects like 1
    //works during compiletime
    //sizeof: types/objects --> int
    PRINT_GREEN( sizeof(int) )
    PRINT_GREEN( sizeof(1) )
    
    //typeid() from the <typeinfo> header works similarly. You can apply 
    //it to a type or object and it will return a type_info-object with information
    //about the type
    
    PRINT_YELLOW( typeid(int).name() )
    PRINT_YELLOW( typeid(1).name() )
    
    //the names are mostly short, but for custom types it will use 
    //scope::class_name as name (+ some numbers and markers)
    PRINT_RED( typeid(example::my_struct<int>).name() )
    
    //you can "store" the type during runtime using typeid()
    
    return 0;
}

