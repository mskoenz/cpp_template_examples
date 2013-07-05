// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.07.2013 21:31:16 EDT
// File:    09_04_static_polymorphism.cpp

#include <iostream>
#include <vector>
#include <typeinfo>
#include <chrono>

template<typename T>
class vector {
public:
    typedef int size_type;
    vector(): vec_(10, 1) {
    }
    //copy ctor
    template<typename U>
    vector(U const & arg
            , typename std::enable_if<std::is_same<vector, U>::value, int>::type shadow = 1
            ): vec_(arg.vec_) {
    }
    template<typename U> //U needs to fulfil the vector concept
    vector(U const & arg
            , typename std::enable_if<!std::is_same<vector, U>::value and 
                                      !std::is_same<T, U>::value, int>::type shadow = 1
            ): vec_(arg.size()) {
        for(size_type i = 0; i < arg.size(); ++i) {
            vec_[i] = arg[i];
        }
    }
    
    T & operator[](size_type const & pos) {
        return vec_[pos];
    }
    T const & operator[](size_type const & pos) const {
        return vec_[pos];
    }
    size_type size() const {
        return vec_.size();
    }
private:
    std::vector<T> vec_;
};

template<typename T>
void print(vector<T> & vec) {
    for(typename vector<T>::size_type i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << std::endl;
}


int main(int argc, char* argv[]) {
    
    vector<double> dv;
    vector<int> iv;
    
    print(dv);
    std::cout << "-----" << std::endl;
    print(iv);
    std::cout << "-----" << std::endl;
    
    vector<double> dv2(iv);
    print(dv2);
    std::cout << "-----" << std::endl;
    
    vector<int> iv2(dv);
    print(iv2);
    std::cout << "-----" << std::endl;
    
    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for(uint i = 0; i < 1000000; ++i) {
        vector<double> dv2(iv);
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "It took " << time_span.count() << " seconds";
    
    
    return 0;
}
