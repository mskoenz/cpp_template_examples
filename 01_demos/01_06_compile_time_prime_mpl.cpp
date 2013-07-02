// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    27.06.2013 12:19:19 EDT
// File:    01_06_compile_time_prime_mpl.cpp

//=================== no macros ===================




//=================== includes ===================
#include <iostream>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/comparison.hpp>

//=================== using namespaces ===================
using namespace boost::mpl;

//=================== prime finder ===================
template<typename seq, bool cond, typename index, typename end>
struct remove_non_prim {
    // int incr = index + 1
    typedef typename plus<index, int_<1> >::type incr;
    typedef typename remove_non_prim<
                      typename remove_if< seq
                                        , and_< greater<_1, index>
                                              , equal_to<modulus<_1, index>, int_<0> > 
                                              >
                                         >::type
                    , greater<end, incr>::value
                    , incr
                    , end
                    >::type type;
};
template<typename seq, typename index, typename end>
struct remove_non_prim<seq, false, index, end> {
    typedef seq type;
};
//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    //~ int const n = 10;
    int const n = 100;
    
    typedef vector_c<int> v0;
    typedef typename insert_range<v0, end<v0>::type, range_c<int, 2, n> >::type range;
    typedef typename remove_non_prim<range, true, int_<2>, int_<n> >::type prime_vec;
    typedef int_<back<prime_vec>::type::value> result_type;
    
    result_type::foo; //for a compiletime error
    return 0;
}
