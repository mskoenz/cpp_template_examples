// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 11:00:12 EDT
// File:    01_01_chameleon_type.cpp

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
#include <sstream>      //for istringstream;
#include <typeinfo>     //for TYPE
#include <stdexcept>    //throw errors! helps debuging. See ASSERT_MSG
#include <memory>       //for the shared_ptr

//=================== the chamelion-type ===================
//------------------- something similar to boost any -------------------
class any_base {
public:
    virtual void * get() = 0;
};
template<typename T>
class any_der: public any_base {
public:
    any_der(T const & t): t_(t) {}
    void * get() {
        return (void *)(&t_);
    }
private:
    T t_;
};

//------------------- runtime checks -------------------
template<typename T>
bool convertable_to(const std::string& str) {
    std::istringstream iss(str);
    T obj;
    iss >> std::ws >> obj >> std::ws;

    if(!iss.eof())
        return false;

    return true; 
}
template< typename T >
inline T convert(const std::string& str) {
    std::istringstream iss(str);
    T obj;

    iss >> std::ws >> obj >> std::ws;

    ASSERT_MSG(!iss.eof(), "not convertable!");

    return obj; 
}
//------------------- compiletime checks -------------------
template<typename T, typename U>
struct is_convertable {
    static char check(U const &);
    static double check(...);
    static T t;
    enum{value = (sizeof(char) == sizeof(check(t)))};
};
//------------------- chameleon type -------------------
class chameleon_type {
    //------------------- init -------------------
    template<typename T, typename U, bool convertable>
    struct init {
        init<T, U, convertable>(T const & t, chameleon_type * b) {
            b->type = TYPE(U);
            b->any = std::shared_ptr<any_base>(new any_der<U>(t));
        }
    };
    template<typename T, typename U>
    struct init<T, U, false> {
        init<T, U, false>(T const & t, chameleon_type * b) {
        }
    };
    template<typename T>
    void set(T const & t) {
        any.reset();
        
        init<T, double, is_convertable<T, double>::value>(t, this);
        init<T, std::string, is_convertable<T, std::string>::value>(t, this);
        
        ASSERT_MSG(!any, "cannot convert type " << TYPE(T) << " to double or std::string")
    }
public:
    //------------------- ctors -------------------
    template<typename T>
    chameleon_type(T const & t) {
        set(t);
    }
    //use new only in the constructor of a shared_pointer!
    //The shared_pointer will manage the lifetime of the object
    //no memory leaks / deletes needed
    chameleon_type(): any(new any_der<double>(0)), type(TYPE(double)) {
    }
    chameleon_type(chameleon_type const & c): any(c.any), type(c.type) {
    }
    template<typename T>
    void operator=(T const & t) {
        set(t);
    }
    //------------------- cast-ops -------------------
    operator double() const {
        ASSERT_MSG(TYPE(double) != type, "wrong conversion to double")
        return *(double const *)(any->get());
    } 
    operator std::string() const {
        ASSERT_MSG(TYPE(std::string) != type, "wrong conversion to std::string")
        return *(std::string const *)(any->get());
    } 
    //------------------- print -------------------
    void print(std::ostream & os = std::cout) const {
        if(type == TYPE(double))
            os << double(*this);
        else if(type == TYPE(std::string))
            os << std::string(*this);
        else
            os<< "chameleon is empty";
    };
private:
    std::shared_ptr<any_base> any;
    std::string type;
};
std::ostream & operator<<(std::ostream & os, chameleon_type const & b) {
    b.print(os);
    return os;
}

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //NEEDS -std=c++0x for shared_ptr
    CLR_SCR()
    PRINT_CYAN("press enter to continue")
    
    chameleon_type foo, bar;
    
    foo = 3.14;
    bar = "some_text";
    
    WAIT_FOR_INPUT() //just hit the enter button to continue
    PRINT_NAMED(foo)
    PRINT_NAMED(bar)
    
    double number = foo;
    std::string string(bar);
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(number)
    PRINT_NAMED(string)
    
    foo = "changed_to_string";
    bar = 42;
    
    WAIT_FOR_INPUT()
    PRINT_NAMED(foo)
    PRINT_NAMED(bar)
    
    return 0;
}
