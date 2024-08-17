//  clamp.cpp by Bill Weinman [bw.org]
//  as of 2024-07-25

#include <print>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using std::print, std::println;
using std::string;
using std::string_view;
using std::vector;
using std::list;
using std::transform;
using std::clamp;

void printc(auto& c, string_view s = "") {
    if (s.size()) print("{}: ", s);
    for (auto e : c) print("{:>5} ", e);
    print("\n");
}

int main() {
    const auto il = {0, -12, 2001, 4, 5, -14, 100, 200, 30000};
    constexpr int ilow {0};
    constexpr int ihigh {500};

    vector<int> voi {il};
    println("vector voi before:");
    printc(voi);

    println("vector voi after:");
    for(auto& e : voi) e = clamp(e, ilow, ihigh);
    printc(voi);

    list<int> loi {il};
    println("list loi before:");
    printc(loi);

    transform(loi.begin(), loi.end(), loi.begin(),
        [=](auto e){ return clamp(e, ilow, ihigh); });
    println("list loi after:");
    printc(loi);
}
