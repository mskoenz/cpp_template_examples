// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.06.2013 11:00:21 EDT
// File:    01_03_random_generator.cpp

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
#include <boost/random.hpp> //for the random generators
#include <time.h>           //for time(NULL)

//+-------------------------------------------------+
//|                 flags for choose                |
//+-------------------------------------------------+
///  \brief option for random_class
///  
///  uses the mersenne twister boost::mt19937
struct mersenne {
    typedef boost::mt19937 type;
};
///  \brief option for random_class
///  
///  uses the mersenne twister boost::mt11213b (fastes according to boost)
struct mersenne_fast {
    typedef boost::mt11213b type;
};
///  \brief option for random_class
///  
///  uses the lagged fibonacci boost::lagged_fibonacci44497
struct fibonacci {
    typedef boost::lagged_fibonacci44497 type;
};
namespace detail {
    uint64_t prevent_correlations = 0;   ///< needed for multiple same-type-rngs
}
///  \brief handy rng class
///  
///  @tparam T is int or double, dependig on what rng you need
///  @tparam RNG is the option for the rng. it has to be a struct that has a typename type that is a valid rng.
///  
///  This class is basically a compiletime wrapper. it allows for an easy change of the rng. it also remaps
///  the native rng output (fibonacci: double [0-1), mersenne uint64_t [whole range]) to the desired range.
///  for optimality it uses a const int called shift that is defined via the constructor. with this variable
///  it's possible to avoid rescaling if it's not needed.
template<typename T, typename RNG>
class random_class {
    public:
        ///  \brief range [0, 1)
        ///  
        ///  doesn't make much sense for int-rng, since it will always be 0
        random_class(): shift(0) {
            init();
        }
        ///  \brief range [0-end)
        ///  
        ///  remaps the native rng output to [0, end). requires an additional multiplication.
        random_class(T const & end): scale(end), offset(0), shift(1) {
            init();
        }
        ///  \brief range [start, end)
        ///  
        ///  remaps the native rng output to [start, end). requires an additional multiplication and addition.
        random_class(T const & start, T const & end): scale(end-start), offset(start), shift(2) {
            init();
        }
        ///  \brief returns a random number
        ///  
        ///  here the const shift variable makes sure, that the minimal amount of operations needed is executed
        inline T operator()() {
            if (shift == 0) {
                return impl_picker<RNG, int>()(rng());
            }
            if (shift == 1) {
                return scale*impl_picker<RNG, int>()(rng());
            }
            return offset + scale*impl_picker<RNG, int>()(rng());
        }
        ///  \brief rescale
        ///  
        ///  one can change the scale during runtime. so the range [0, end) changes to [0, scale)
        inline void set_scale(T const & scaleIn) {
            scale = scaleIn;
        }
        ///  \brief set seed
        ///  
        ///  one can set an own seed.
        void seed(long int const & sd) {
            rng.seed(sd);
            seed_ = sd;
        }
        ///  \brief get seed
        ///  
        ///  you can get the automatic seed and store it, in case something strange/nice happens
        inline unsigned long int seed() {
            return seed_;
        }
        
    private:
        ///  \brief initializes rng
        ///  
        ///  first it sets the seed to time(NULL) + prevent_correlations. the second static term is increased, 
        ///  every time init is called. this is neccesary b.c. two rngs of the same type (mersenne) created in
        ///  the same second will have the same seed, thus identical.
        ///  it also burns the first 100 numbers. since it should be a chaotic system the a small difference in the seed
        ///  doesn't matter anymore after 100 calls
        inline void init() {
            seed_ = time(NULL) + detail::prevent_correlations;
            ++detail::prevent_correlations;
            rng.seed(seed_);
            for(uint i = 0; i < 100; ++i) {
                rng(); //warming up the rng
                //fibbonaci has for several seconds the same first number even though the seed changes every second
            }
        }
        ///  \brief rescale native
        ///  
        ///  the different rngs have different outputs depending on the type.
        ///  this impl_picker needs to be specialized for every rng that doesn't output a double in [0,1)
        template<typename RNG2, typename U>
        struct impl_picker {
            inline double operator()(double const r) {
                return r;
            }
        };
        ///  \brief spec fo mersenne
        ///  
        ///  remaps the native random uint32_t to a double in [0, 1)
        template<typename U>
        struct impl_picker<mersenne, U> {
            inline double operator()(double  const r) {
                return r/double(uint32_t(-1) + double(1)); //+ 1!!! otherwise 1 can be reached
            }
        };
        ///  \brief spec fo fast_mersenne
        ///  
        ///  remaps the native random uint32_t to a double in [0, 1)
        template<typename U>
        struct impl_picker<mersenne_fast, U> {
            inline double operator()(double const r) {
                return r/double(uint32_t(-1) + double(1)); //+ 1!!! otherwise 1 can be reached
            }
        };
        
        typename RNG::type rng; ///< the native rng
        T scale;    ///< length of the range
        T offset;   ///< start of the range
        const short int shift;  ///< shows, what operations are needed (for speedup. Tested!)
        uint64_t seed_; ///< the used seed
};
//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main(int argc, char* argv[]) {
    CLR_SCR()
    
    random_class<double           , fibonacci>     rng1(0, 1);
    random_class<int              , mersenne>      rng2(1, 6);
    random_class<unsigned long int, mersenne_fast> rng3(0, 1000000l);
    
    for(uint i = 0; i < 3; ++i)
        PRINT_RED(rng1())
    for(uint i = 0; i < 3; ++i)
        PRINT_YELLOW(rng2())
    for(uint i = 0; i < 3; ++i)
        PRINT_GREEN(rng3())
    
    return 0;
}
