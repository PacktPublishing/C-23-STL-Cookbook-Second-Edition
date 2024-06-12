// initialization.cpp by Bill Weinman [bw.org]
// updated 2024-06-03
#include <print>
#include <initializer_list>
#include <vector>
#include <string>
using std::print;
using std::println;
using std::vector;
using std::string;

// print the elements of the vector
constexpr void pvec(const auto& v) {
    if (v.empty()) {
        println("[empty]");
    } else {
        for (const auto& i : v) print("{} ", i);
        println("");
    }
}

// many constructors
template <typename T>
class thing {
    T v {};
    std::string state {"undef"};
public:
    thing() : v(T{}) {
        print("default constructor\n");
        state = "zero";
    }

    thing(const T& p) : v(p) {
        print("copy constructor\n");
        state = "copied value";
    }

    thing(const std::initializer_list<T>& ilist) {
        print("initializer_list: ");
        for (const auto& e : ilist) print("{} ", e);
        print("\n");
        const auto sz = ilist.size();
        auto pt = ilist.begin();
        if(sz > 1) pt += sz / 2;
        v = *pt;
        state = "list constructed";
    }
    
    thing(const size_t p1, const T& p2) {
        print("specific constructor: {}, {}\n", p1, p2);
        if (p1 < 10) return;
        else v = p2;
        state = "specific value";
    }
    
    void status() const {
        print("status: {}, value {}\n", state, v);
    }
};

void initialize_this() {
    print("t1: ");
    thing<int> t1 {};
    t1.status();
    println("");

    print("t2: ");
    thing<int> t2 {7};
    t2.status();
    println("");

    print("t3: ");
    thing t3(42);
    t3.status();
    println("");

    print("t4: ");
    thing<int> t4 {1, 2, 3, 4, 5};
    t4.status();
    println("");

    print("t5: ");
    thing<int> t5 {1, 2};
    t5.status();
    println("");

    print("t6: ");
    thing<int> t6(1, 2);
    t6.status();
    println("");
}

int main() {
    int x {};
    print("x is {}\n", x);
    
    vector<int> v {1, 2, 3, 4 ,5};
    pvec(v);
    
    initialize_this();
}
