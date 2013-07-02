// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 22:11:46 EDT
// File:    08_01_typedef.cpp

#include <iostream>

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    
    //use typedef to call types by another name like a reference
    
    typedef int i; //int is way to long, we need an abreviation
    
    //now you can use the new name like an int
    
    i nr1 = 1;
    i nr2 = 1;
    
    //everything you can do with int, you can now also do with my_shorter_name_for_int
    
    std::cout << nr1 << std::endl;
    std::cout << nr2 << std::endl;
    
    //typedefs are normaly done inside a class/struct not in a function
    //some compilers will warn you about typedefs outside a class/struct
    
    return 0;
}
