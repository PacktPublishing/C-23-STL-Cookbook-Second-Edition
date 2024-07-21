//  function.cpp by Bill Weinman [bw.org]
//  as of 2024-07-19

#include <print>
#include <string>
#include <deque>
#include <list>
#include <vector>
#include <functional>

using std::print, std::println;
using std::string;
using std::deque;
using std::list;
using std::vector;
using std::function;

struct hello {
    void greeting() const { println("Hello Human"); }
    void operator()() { greeting(); }
};

int main() {
    deque<int> d;
    list<int> l;
    vector<int> v;

    auto print_c = [] (const auto& c) {
        for (const auto i : c) print("{} ", i);
        print("\n");
    };

    auto push_c = [] (auto& container) {
        return [&container] (const auto value) {
            container.push_back(value);
        };
    };

    const vector<function<void(int)>>
        consumers {push_c(d), push_c(l), push_c(v)};

    for (auto& c : consumers) {
        for (int i{0}; i < 10; ++i) {
            c(i);
        }
    }

    print_c(d);
    print_c(l);
    print_c(v);

    hello human{};
    const function<void(const hello&)> h1 = &hello::greeting;
    const function<void(void)> h2 = std::bind(&hello::greeting, &human);
    const function<void(void)> h3 = hello();    // functor
    h1(human);
    h2();
    h3();
}
