//  raii.cpp
//  as of 2021-06-09 bw [bw.org]
#include <print>
#include <memory>

using std::println;

class C {
    int i {};
public:
    C() { println("default constructor"); }
    ~C() { println("destructor"); }
};

template <typename T>
class uptr {
    T* m{};
public:
    uptr() {
        println("uptr constructor");
        m = new T;
    }
    uptr(const T& v) {
        println("uptr(value) constructor");
        m = new T;
        *m = v;
    }
    ~uptr() {
        println("uptr destructor");
        delete m;
    }
    T& operator*() const {
        return *m;
    }
    T& operator*(const T& v) {
        *m = v;
        return *m;
    }
};

void f1() {
    C a {};
    println("this is function f()");
}

void f2() {
    uptr<int> p {};
    *p = 42;
    println("(f2) *p is {}", *p);
}

int main() {
    println("calling f1()");
    f1();
    println("returned from f1()");
    println("calling f2()");
    f2();
    println("returned from f2()");

    uptr p2(73);
    println("*p2 is {}", *p2);
}
