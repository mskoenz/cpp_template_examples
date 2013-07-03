// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 22:11:46 EDT
// File:    08_01_typedef.cpp

#include <iostream>
#include <vector>
//=================== typedefs ===================

//use typedef to call types by another name like a reference

//int is way to long, we need an abreviation
typedef int I;

//shorter name
typedef std::vector<std::vector<int>> int_array_type;
//use boost::multi_array instead of vector<vector<T>> for critical code
//vector<vector<T>> can have bad locality

//c++11
template<typename T>
using array_type = std::vector<std::vector<T>>; //new style "typedef"

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //now you can use the new name like an the old, long compicated one
    
    I nr1 = 1;
    I nr2 = 1;
    int_array_type m1;
    array_type<I> m2;
    
    //everything you can do with int, you can now also do with I
    
    std::cout << nr1 << std::endl;
    std::cout << nr2 << std::endl;
    
    //typedefs are normaly done inside a class/struct not in a function
    //some compilers will warn you about typedefs outside a class/struct
    
    //make code more flexible and readable
    typedef int spin_type;
    
    //could be anything
    int a1;
    
    //long names are cumbersome
    int spin_a1;
    
    //now the name doesn't need to explain what the var does
    spin_type a2;
    
    //better having a longer type than name since you need the type normally less often
    
    return 0;
}
