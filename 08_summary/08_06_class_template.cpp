// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 22:59:19 EDT
// File:    08_06_class_template.cpp

#include <iostream>
#include <assert.h>

//same as in example 02_03_template_way.cpp
template<typename T, uint32_t N>
class template_class {
public:
    typedef uint32_t size_type; //use typedefs to make later changes easy
    T & operator[](size_type const & index) {
        assert(index >= 0 and index < N);
        return array_[index];
    }
    T const & operator[](size_type const & index) const { 
    //you almost ever need two access operators, one const and the other normal
        assert(index >= 0 and index < N);
        return array_[index];
    }
    size_type size() const { //can also be done as a static, but is inlined anyway
        return N;
    }
private:
    T array_[N];
};

//demonstration of default arguments
template< typename T = int
        , typename U = int
        , bool     b = false>
struct default_template {
    //does nothing...
};

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //the template parameters are placed in the <> brakets right after
    //the name
    template_class<int, 5> a; //right
    //~ template_class a<int, 5>; //wrong
    
    //you can use default args for templates, but you still need <>
    default_template<> all_default; //works
    //~ default_template all_default_wrong; //doesn't
    
    default_template<void> partial_default; //void is usable as a type
    
    default_template<void, bool, true> no_default;
    
    return 0;
}
