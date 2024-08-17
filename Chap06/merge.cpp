//  merge.cpp by Bill Weinman [bw.org]
//  as of 2024-08-17

#include <print>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

using std::print;
using std::vector;
using std::sort;
using std::merge;
using std::back_inserter;
using std::string;
using std::string_view;

void printc(const auto& c, string_view s = "") {
    if (s.size()) print("{}: ", s);
    for (const auto& e : c) print("{} ", e);
    print("\n");
}

int main() {
    vector<string> vs1 {"dog", "cat", "velociraptor"};
    vector<string> vs2 {"kirk", "sulu", "spock"};
    vector<string> dest {};
    printc(vs1, "vs1");
    printc(vs2, "vs2");

    sort(vs1.begin(), vs1.end());
    sort(vs2.begin(), vs2.end());

    printc(vs1, "vs1 sorted");
    printc(vs2, "vs2 sorted");

    merge(vs1.begin(), vs1.end(), vs2.begin(), vs2.end(), back_inserter(dest));
    printc(dest, "dest");
}
