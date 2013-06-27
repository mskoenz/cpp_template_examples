// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 12:53:13 EDT
// File:    02_03_template_way.cpp

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
#include <assert.h> //use asserts! It will make your debugging way easier
                    //and it doesn't cut into the performance (-DNDEBUG)

//=================== template class ===================
template<typename T, int N>
class template_class {
public:
    typedef int size_type; //use typedefs to make later changes easy
    T & operator[](size_type const & index) {
        assert(index >= 0 and index < N);
        return array_[index];
    }
    size_type size() const { //can also be done as a static, but is inlined anyway
        return N;
    }
private:
    T array_[N];
};
//=================== template function ===================
template<typename T>
void init_and_print(T & t) {
    //typename is needed, since the compiler cannot know that T::size_type is a type
    //it could just as well be a static variable.
    //typename tells the compiler to treat the next expression as a type
    for(typename T::size_type i = 0; i < t.size(); ++i)
        t[i] = i + 0.1;
    for(typename T::size_type i = 0; i < t.size(); ++i)
        PRINT_MAGENTA("t[" << i << "] = " << t[i])
    //this may look less nice than...
    //  for(uint i = 0; i < t.size(); ++i)...
    //...but it is generic. If size_type is changed to double this will still work
}


//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //needs c++0x bc of uint
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    WAIT_FOR_INPUT() //just hit the enter button to continue
    //double_5_class d5;
    template_class<double, 5> d5;
    init_and_print(d5);
    
    
    
    WAIT_FOR_INPUT()
    //double_10_class d10;
    template_class<double, 10> d10;
    init_and_print(d10);
    
    
    
    WAIT_FOR_INPUT()
    //int_10_class i10;
    template_class<int, 10> i10;
    init_and_print(i10);
    
    return 0;
}
