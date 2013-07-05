// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.07.2013 21:01:59 EDT
// File:    09_03_dynamic_polymorphism.cpp

#include <iostream>
#include <vector>
#include <typeinfo>
#include <chrono>

class vector_concept {
public:
    typedef int size_type;
    virtual void * operator[](size_type const & pos) = 0;
    virtual std::string type() = 0;
    virtual size_type size() const = 0;
private:
};


class int_vector: public vector_concept {
public:
    int_vector(): vec_(10, 1) {
    }
    int_vector(vector_concept & arg): vec_(arg.size()) {
        for(size_type i = 0; i < arg.size(); ++i) {
            if(arg.type() == "d")
                vec_[i] = *(double*)arg[i];
            else if(arg.type() == "i")
                vec_[i] = *(int*)arg[i];
        }
    }
    void * operator[](size_type const & pos) {
        return &vec_[pos];
    }
    size_type size() const {
        return vec_.size();
    }
    std::string type() {
        return typeid(int).name();
    }
private:
    std::vector<int> vec_;
};

class double_vector: public vector_concept {
public:
    double_vector(): vec_(10, 2.1) {
    }
    double_vector(vector_concept & arg): vec_(arg.size()) {
        for(size_type i = 0; i < arg.size(); ++i) {
            if(arg.type() == "i")
                vec_[i] = *(int*)arg[i];
            else if(arg.type() == "d")
                vec_[i] = *(double*)arg[i];
        }
    }
    //~ double_vector(int_vector & arg): vec_(arg.size()) {
        //~ for(size_type i = 0; i < arg.size(); ++i) {
            //~ vec_[i] = *(int*)arg[i];
        //~ }
    //~ }
    
    void * operator[](size_type const & pos) {
        return &vec_[pos];
    }
    std::string type() {
        return typeid(double).name();
    }
    size_type size() const {
        return vec_.size();
    }
private:
    std::vector<double> vec_;
};


void print(vector_concept & vec) {
    for(vector_concept::size_type i = 0; i < vec.size(); ++i)
        if(vec.type() == "d")
            std::cout << *(double*)vec[i] << std::endl;
        else if(vec.type() == "i")
            std::cout << *(int*)vec[i] << std::endl;
}


int main(int argc, char* argv[]) {
    
    double_vector dv;
    int_vector iv;
    
    print(dv);
    std::cout << "-----" << std::endl;
    print(iv);
    std::cout << "-----" << std::endl;
    
    double_vector dv2(iv);
    print(dv2);
    std::cout << "-----" << std::endl;
    
    int_vector iv2(dv);
    print(iv2);
    std::cout << "-----" << std::endl;
    
    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for(uint i = 0; i < 1000000; ++i) {
        double_vector dv2(iv);
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "It took " << time_span.count() << " seconds";
    
    
    return 0;
}
