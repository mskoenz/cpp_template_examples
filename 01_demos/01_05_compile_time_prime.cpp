// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 11:00:26 EDT
// File:    01_05_compile_time_prime.cpp

//=================== no macros ===================
//=================== no includes ===================

//=================== meta templates ===================
//------------------- int wrap -------------------
template<int v>
struct m_int {
    enum{value = v};
};
//------------------- add/increment -------------------
template<typename T, typename U>
struct add {
};
template<int v, int w>
struct add<m_int<v>, m_int<w> > {
    typedef m_int<v+w> type;
};
struct increment {
    template<typename T>
    struct apply {
        typedef typename add<T, m_int<1> >::type type;
    };
};
//------------------- mod -------------------
template<typename T, typename U>
struct mod {
};
template<int v, int w>
struct mod<m_int<v>, m_int<w> > {
    typedef m_int<v%w> type;
};
//------------------- compare -------------------
template<typename T, typename U>
struct greater {
};
template<int v, int w>
struct greater<m_int<v>, m_int<w> > {
    enum{value = (v < w)};
};

template<bool Cond, typename IfTrue, typename IfFalse>
struct m_if {
    typedef IfTrue type;
};
template<typename IfTrue, typename IfFalse>
struct m_if<false, IfTrue, IfFalse> {
    typedef IfFalse type;
};

//------------------- for-recursion -------------------
template< typename Index
        , typename Max
        , bool Cond
        , typename Incr
        , typename Body
        , typename ResSoFar>
struct m_for_rec {
    typedef typename m_for_rec<typename Incr::template apply<Index>::type
                                , Max
                                , greater<typename Incr::template apply<Index>::type, Max>::value
                                , Incr
                                , Body
                                , typename m_if<
                                                  Body::template apply<Index>::value
                                                , Index
                                                , ResSoFar
                                                >::type
                    >::type type;
};

template< typename Index
        , typename Max
        , typename Incr
        , typename Body
        , typename ResSoFar>
struct m_for_rec<Index, Max, false, Incr, Body, ResSoFar> {
    typedef ResSoFar type;
};

template< typename Init
        , typename Max
        , typename Incr
        , typename Body>
struct m_for {
    typedef typename m_for_rec<Init, Max, greater<Init, Max>::value, Incr, Body, Init>::type type;
};
//=================== prime finder ===================
template<typename T>
struct divisible {
    template<typename U>
    struct apply{
        enum{value = !bool(mod<T, U>::type::value)};
    };
};

struct m_is_prime {
    template<typename T>
    struct apply {
        typedef typename m_for<m_int<2>, T, increment, divisible<T> >::type type;
        enum{value = (2 == type::value)};
    };
};
//  +---------------------------------------------------+
//  |                   "main"                          |
//  +---------------------------------------------------+
void no_main() { //;-) 
    //~ int const n = 10;
    int const n = 100;
    
    //not optimal since it goes from 2 to n instead of going from n to 0
    typedef typename m_for<m_int<2>
                         , m_int<n>
                         , increment
                         , m_is_prime>::type result_type;
    
    result_type::foo; //for a compiletime error
}
