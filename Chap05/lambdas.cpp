//  lambdas.cpp by Bill Weinman [bw.org]
//  as of 2024-07-18

#include <print>
#include <string>

using std::print, std::println;
using std::string;

int main() {
    auto one = [] -> const char * { return "one"; };
    auto two = []{ return "two"; };

    println("one and two:");
    println("{}", one());
    println("{}", two());
    
    auto p = [](auto v){ println("{}", v()); };
    p([]{ return "lambda call lambda"; });

    print("anonymous lambda: ");
    println("{}", [](auto l, auto r){ return l + r; }(47, 73));
    
    print("capture by reference: ");
    int num {};
    auto inc = [&num]{ return ++num; };
    for (size_t i {}; i < 5; ++i) {
        print("{} ", inc());
    }
    print("\n");

    print("counter: ");
    auto counter = [n = 0] mutable { return ++n; };
    for (size_t i {}; i < 5; ++i) {
        print("{} ", counter());
    }
    print("\n");

    int a {47};
    int b {73};
    auto l1 = [=]{ return a + b; };
    print("default capture: {}\n", l1());
}
