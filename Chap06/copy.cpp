//  copy.cpp by Bill Weinman [bw.org]
//  as of 2024-07-21

#include <print>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <iterator>
#include <algorithm>

using std::print;
using std::cout;
using std::string;
using std::string_view;
using std::vector;
using std::ostream_iterator;

namespace ranges = std::ranges;

void printc(auto& c, string_view s = "") {
    if (s.size()) print("{}: ", s);
    for (auto e : c) print("[{}] ", e);
    print("\n");
}

int main() {
    vector<string> v1 {"alpha", "bravo", "charlie", "delta", "echo"};
    printc(v1, "v1");
    
    vector<string> v2 {};
    ranges::copy(v1, back_inserter(v2));
    printc(v2, "v2");
    
    vector<string> v3 {};
    std::copy_n(v1.begin(), 3, back_inserter(v3));
    printc(v3, "v3");
    
    vector<string> v4 {};
    ranges::copy_if(v1, back_inserter(v4), [](string& s){ return s.size() > 4; });
    printc(v4, "v4");
    
    ostream_iterator<string> out_it(cout, " ");
    ranges::copy(v1, out_it);
    print("\n");
    
    std::move(v1.begin(), v1.end(), v2.begin());
    printc(v1, "after move1: v1");
    printc(v2, "after move1: v2");
    
    ranges::move(v2, v1.begin());
    printc(v1, "after move2: v1");
    printc(v2, "after move2: v2");
}
