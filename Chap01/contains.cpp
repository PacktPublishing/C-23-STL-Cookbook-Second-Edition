// contains.cpp by Bill Weinman [bw.org]
// as of 2024-05-30
#include <string>
#include <string_view>
#include <vector>
#include <ranges>
#include <algorithm>
#include <print>

using std::println;
using std::string;
using std::string_view;
using std::vector;

namespace ranges = std::ranges;
namespace views = ranges::views;

int main() {
    const string s {"Big Light In Sky Slated To Appear In East"};
    if (s.contains("Sky")) {
        println("found");
    } else {
        println("not found");
    }
    
    const string_view sv {"Why is abbreviated such a long word?"};
    if (sv.contains("word")) {
        println("found");
    } else {
        println("not found");
    }
    
    const string s2 {"abcdefg"};
    if (s2.contains('f')) {
        println("found");
    } else {
        println("not found");
    }
    
    const auto r = views::iota(1,11);
    if (ranges::contains(r, 7)) {
        println("found");
    } else {
        println("not found");
    }

    if (ranges::contains(r, 14, [](const auto& n){return n * 2;})) {
        println("found");
    } else {
        println("not found");
    }

    const vector<int> v1 {1, 2, 3, 4, 5};
    const vector<int> v2 {2, 3, 4};
    if (ranges::contains_subrange(v1, v2)) {
        println("found");
    } else {
        println("not found");
    }

    const vector<int> v3 {10, 20, 30, 40, 50};
    const vector<int> v4 {2, 3, 4};
    if (ranges::contains_subrange(v3, v4, {},
            [](const auto& n){return n / 5;},
            [](const auto& n){return n * 2;})) {
        println("found");
    } else {
        println("not found");
    }
}
