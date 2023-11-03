#include <iostream>
struct serialClass {
    void serialfunc() {
        std::cout << "serialClass func called"<< std::endl;
    }
};

// to make default read()get called
struct otherClass {
    void serialfunc() {
        std::cout << "otherClass func called"<< std::endl;
    }
};

struct ethPort : public serialClass {
    void ethFunc() {
        std::cout << "eth func called"<< std::endl;
    }
};

struct normalDFPort : serialClass {
    void read() {
        std::cout << "child serial version called"<< std::endl;
    }
};

struct ethDFPort : public ethPort{
    void read() {
        std::cout << "child eth version called"<< std::endl;
    }
};

// check that an interface that doesn't inherit the other parent classes allows child classes to call that
struct Interface  {
    virtual void read() = 0;
    virtual void serialfunc() = 0;
};

//struct templatedClass : public T {
template <typename T>
struct templatedClass : public T, Interface {
    // function works if defined in class. see below for the default outside of class
    //void read() override {
    //    std::cout << "child default version called"<< std::endl;
    //}
    void read() override;

    // explicit override to force calling inherited function works when this class is passed in place of Interface class
    // Will otherwise error because of the ambiguity
    void serialfunc() override {
        T::serialfunc();
    }
};
//Note default specializaiton here, but declaration in class still.Inline def outside of class works. in cpp file has issues?
template<typename T>
inline void templatedClass<T>::read() {
    std::cout << "child default version called"<< std::endl;
}

template<>
inline void templatedClass<serialClass>::read() {
    std::cout << "serial templated func called"<< std::endl;
}
// if in cpp no inline needed RECOMMENDED
template<>
void templatedClass<ethDFPort>::read();
