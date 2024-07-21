//  braces.cpp by Bill Weinman [bw.org]
//  as of 2024-07-20

#include <print>
#include <string>

using std::print;

auto braces (const char a, const char b) {
    return [a, b](const auto v) {
        print("{}{}{} ", a, v, b);
    };
}

int main() {
    auto a = braces('(', ')');
    auto b = braces('[', ']');
    auto c = braces('{', '}');
    auto d = braces('|', '|');

    for (int i : {1, 2, 3, 4, 5}) {
        for (auto x : {a, b, c, d}) x(i);
        print("\n");
    }
}
