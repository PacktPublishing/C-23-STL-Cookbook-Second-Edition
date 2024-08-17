//  permutations.cpp by Bill Weinman [bw.org]
//  as of 2024-08-17

#include <print>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

using std::print;
using std::vector;
using std::sort;
using std::string;
using std::string_view;
using std::next_permutation;

void printc(const auto& c, string_view s = "") {
    if (s.size()) print("{}: ", s);
    for (const auto& e : c) print("{} ", e);
    print("\n");
}

string numstr(const long i) {
    string ns {std::to_string(i)};
    auto it = ns.end();
    while (it > ns.begin()) {
        it -= 3;
        if (it > ns.begin()) ns.insert(it, ',');
    }
    return ns;
}

int main() {
    vector<string> vs {"dog", "cat", "velociraptor"};
    sort(vs.begin(), vs.end());

    do {
        printc(vs);
    } while (next_permutation(vs.begin(), vs.end()));

    vector<int> vi {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    sort(vi.begin(), vi.end());
    printc(vi, "vi sorted");
    long count {};
    do {
        ++count;
    } while (next_permutation(vi.begin(), vi.end()));
    print("number of permutations: {}\n", numstr(count));
}
