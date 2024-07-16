//  reverse-iterator.cpp by Bill Weinman [bw.org]
//  as of 2024-07-14

#include <print>
#include <string_view>
#include <vector>
#include <iterator>
#include <list>

using std::print;
using std::string_view;
using std::vector;


void printc(const auto & c, const string_view s = "") {
    if(s.size()) print("{}: ", s);
    for(auto e : c) print("{} ", e);
    print("\n");
}

void printr(const auto & c, const string_view s = "") {
    if(s.size()) print("{}: ", s);
    auto it = std::rbegin(c);
    auto end_it = std::rend(c);
    while(it != end_it) {
        print("{} ", *it++);
    }
    print("\n");
}

int main() {
    int array[] {1, 2, 3, 4, 5};
    printc(array, "c-array");
    printr(array, "rev c-array");

    vector<int> v {1, 2, 3, 4, 5};
    printc(v, "vector");
    printr(v, "rev vector");
}
