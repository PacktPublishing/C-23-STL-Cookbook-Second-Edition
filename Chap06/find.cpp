//  find.cpp by Bill Weinman [bw.org]
//  as of 2024-07-24

#include <print>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>

using std::println;
using std::string;
using std::string_view;
using std::vector;
using std::back_inserter;
using std::find;
using std::find_if;

namespace views = std::ranges::views;

struct City {
    string name {};
    unsigned pop {};
    bool operator==(const City& o) const {
        return name == o.name;
    }
    bool operator==(const char* cstr) const {
        return name == cstr;
    }
    string str() const {
        return format("[{}, {}]", name, pop);
    }
};

int main() {
    const vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    println("find 7:");
    auto it1 = find(v.begin(), v.end(), 7);
    if (it1 != v.end()) println("found: {}", *it1);
    else println("not found");

    const vector<City> c{
        { "London", 9425622 },
        { "Berlin", 3566791 },
        { "Tokyo",  37435191 },
        { "Cairo",  20485965 }
    };

    println("find Berlin:");
    auto it2 = find(c.begin(), c.end(), City({"Berlin", {}}));
    if (it2 != c.end()) println("found: {}", it2->str());
    else println("not found");

    println("find Berlin (c-string):");
    auto it3 = find(c.begin(), c.end(), "Berlin");
    if (it3 != c.end()) println("found: {}", it3->str());
    else println("not found");

    println("find pop > 20000000:");
    auto it4 = find_if(begin(c), end(c),
        [](const City& item) { return item.pop > 20000000; });
    if (it4 != c.end()) println("found: {}", it4->str());
    else println("not found");;

    println("views::filter pop > 20000000:");
    auto vw1 = views::filter(c, 
        [](const City& c){ return c.pop > 20000000; });
    for (const City& e : vw1) println("{}", e.str());
}
