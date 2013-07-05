// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.07.2013 20:01:05 EDT
// File:    01_05_runtime_style.cpp

#include <iostream>

//this code does the prime calculation the exact same way as 
//01_05_compile_time_prime but all is in runtime. If you understand this, 
//compare it to the compile:time_version to learn the syntax difference

int increment(int i) {
    return ++i;
}

//------------------- for-recursion -------------------
int m_for_rec(int index, int max, bool cond, int(*incr)(int), bool(*check)(int), int res_so_far) {
    if(cond)
        return m_for_rec( incr(index)
                        , max
                        , incr(index) < max
                        , incr
                        , check
                        , check(index) ? index : res_so_far); 
                        //changes res_so_far to the current index if check is true
    else //ends the recursion
        return res_so_far;
    
}

//just a nicer way to start the recursion
int m_for(int init, int max, int(*incr)(int), bool(*check)(int)) {
    return m_for_rec( init
                    , max
                    , init < max
                    , incr
                    , check
                    , init);
}

//=================== prime finder ===================
//to be exact I had to use a function object here but the whole pointer casting 
//is ugly (I had to cast a functor to a function pointer)
int number = 2;
bool divisible(int i) {
    return ((number % i) == 0);
}

bool is_prime(int nr) {
    number = nr;
    return (m_for(2, nr, increment, divisible) == 2);
    //~ return (m_for(2, nr, increment, divisible(nr)) == 2); //version with functor
}


int main(int argc, char* argv[]) {
    //~ int const n = 10;
    int const n = 100;
    
    std::cout << m_for(2, n, increment, is_prime) << std::endl;
    
    return 0;
}
