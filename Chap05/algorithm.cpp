//  algorithm.cpp by Bill Weinman [bw.org]
//  as of 2024-07-18

#include <print>
#include <string>
#include <vector>
#include <algorithm>

using std::print, std::println;
using std::string;
using std::vector;
using std::count_if;

auto is_div_by(const int& divisor) {
    return [&divisor] (const int i) { return i % divisor == 0; };
}

int main() {
    const vector<int> v {1, 7, 4, 9, 4, 8, 12, 10, 20};

    for (int i : { 3, 4, 5 }) {
        auto pred = is_div_by(i);
        auto count = count_if(v.begin(), v.end(), pred);
        println("numbers divisible by {}: {}", i, count);
    }
}
