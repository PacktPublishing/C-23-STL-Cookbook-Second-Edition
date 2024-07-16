//  iterator-adapters.cpp by Bill Weinman [bw.org]
//  as of 2024-07-06

#include <print>
#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>

using std::print, std::println;
using std::cin, std::cout;
using std::vector;
using std::deque;
using std::string_view;
using std::string;
using std::ostream_iterator;
using std::istream_iterator;

void printc(const auto & v, const string_view s = "") {
    if(!s.empty()) print("{}: ", s);
    for(auto e : v) print("{} ", e);
    print("\n");
}

int main() {
    deque<int> d1 {1, 2, 3, 4, 5};
    deque<int> d2(d1.size());

    copy(d1.begin(), d1.end(), d2.begin());
    printc(d1);
    printc(d2, "d2 after copy");

    copy(d1.begin(), d1.end(), std::back_inserter(d2));
    printc(d2, "d2 after back_inserter");

    deque<int> d3 {47, 73, 114, 138, 54};
    copy(d3.begin(), d3.end(), std::front_inserter(d2));
    printc(d2, "d2 after front_inserter");

    auto it2 = d2.begin() + 2;
    copy(d1.begin(), d1.end(), std::inserter(d2, it2));
    printc(d2, "d2 after middle insert");

    print("ostream_iterator: ");
    std::copy(d1.begin(), d1.end(), ostream_iterator<int>(cout));
    print("\n");

    vector<string> vs{};
    copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(vs));
    printc(vs, "vs from istream");

    print("Reverse iterator: ");
    for(auto it = d1.rbegin(); it != d1.rend(); ++it) {
        print("{} ", *it);
    }
    print("\n");
}
