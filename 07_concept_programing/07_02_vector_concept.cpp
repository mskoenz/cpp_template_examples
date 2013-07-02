// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 20:10:49 EDT
// File:    07_02_vector_concept.cpp

//========= some macros for nicer presentation (not essential) =========
//use as litte macros as possible in c++ (most stuff can be solved without)
//I just use them here to keep the unimportant stuff away from the main code
#define TYPE(T) typeid(T).name()
#define CLR_SCR() std::cout << "\033[2J\033[100A";
#define NEW_LINE() std::cout << std::endl;
#define WAIT_FOR_INPUT() while(std::cin.gcount() == 0) std::cin.get(); std::cin.get();
#define ASSERT_MSG(cond, msg) if(cond) {PRINT_RED(msg); throw std::runtime_error("error");}
#define PRINT_NAMED(x) std::cout << #x << " = " << x << std::endl; //#x changes the variable name into a string "x"
#define PRINT_CALL(x) std::cout << #x << ": "; x; NEW_LINE()
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
#include <vector>
#include <array>
#include <type_traits>

//=================== vector_class ===================
template<typename T>
class my_vector {
public:
    typedef typename std::vector<T>::size_type size_type;
    //------------------- ctor -------------------
    my_vector(): vec_() {}
    my_vector(size_type const & N): vec_(N) {}
    my_vector(size_type const & N, T const & val): vec_(N, val) {}
    
    //copy ctor
    template<typename U>
    my_vector(U const & arg
            , typename std::enable_if<std::is_same<my_vector, U>::value, int>::type shadow = 1
            ): vec_(arg.vec_) {
    }
    template<typename U> //U needs to fulfil the vector concept
    my_vector(U const & arg
            , typename std::enable_if<!std::is_same<my_vector, U>::value and 
                                      !std::is_same<T, U>::value, int>::type shadow = 1
            ) {
        (*this) = arg;
    }
    //the second is_same<U, T> is needed in order not to conflict with the ctor(size_type, T)
    
    //why not...
    //template<typename U>
    //my_vector(typename boost::enable_if<..., U>::type const & arg)
    //
    //the problem is that the template deduction doesn't work in this case
    //the compiler cannot figure out what U is
    //the so called shadow parameter is just there to do SFINAE...
    //...and by doing SFINAE I mean it is the part that will or will not fail
    //to substitute
    
    //assignment
    template<typename U>
    typename std::enable_if<std::is_same<my_vector, U>::value
                          , my_vector>::type & operator=(U const & rhs) {
        vec_ = rhs.vec_;
    }
    template<typename U> //U needs to fulfil the vector concept
    typename std::enable_if<!std::is_same<my_vector, U>::value
                          , my_vector>::type & operator=(U const & rhs) {
        vec_.resize(rhs.size());
        for(size_type i = 0; i < rhs.size(); ++i) {
            vec_[i] = rhs[i];
        }
        return (*this);
    }
    //------------------- getter -------------------
    T & operator[](size_type const & pos) {
        return vec_[pos];
    }
    T const & operator[](size_type const & pos) const {
        return vec_[pos];
    }
    //------------------- info -------------------
    size_type size() const {
        return vec_.size();
    }
private:
    std::vector<T> vec_;
};
template<typename T>
std::ostream & operator<<(std::ostream & os, my_vector<T> const & arg) {
    os << "[";
    for(typename my_vector<T>::size_type i = 0; i < arg.size(); ++i) {
        os << arg[i];
        if(i != arg.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}



//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //NEEDS -std=c++11 for enable_if
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    std::vector<char> std_vec(5, 'a');
    std::array<double, 20> std_array;
    
    WAIT_FOR_INPUT() //just hit the enter key to continue
    PRINT_CALL(my_vector<int> int_vec(10, 1));
    PRINT_YELLOW(int_vec)
    
    WAIT_FOR_INPUT()
    PRINT_CALL(my_vector<double> double_vec(int_vec));
    PRINT_YELLOW(double_vec)
    
    WAIT_FOR_INPUT()
    PRINT_CALL(my_vector<char> char_vec(std_vec));
    PRINT_YELLOW(char_vec)
    
    WAIT_FOR_INPUT()
    PRINT_CALL(double_vec = char_vec);
    PRINT_YELLOW(double_vec)
    
    WAIT_FOR_INPUT()
    PRINT_CALL(int_vec = std_array);
    PRINT_YELLOW(int_vec)
    
    WAIT_FOR_INPUT()
    PRINT_GREEN("didn't loose any performance bc of enable_if,")
    PRINT_GREEN("but gained alot of functionality")
    PRINT_GREEN("relays only on the vector concept")
    
    return 0;
}
