//  sort.cpp by Bill Weinman [bw.org]
//  as of 2024-07-22

#include <print>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>

using std::print, std::println;
using std::string;
using std::vector;

void randomize(auto& c) {
    static std::random_device rd;
    static std::default_random_engine rng(rd());
    std::shuffle(c.begin(), c.end(), rng);
}

void check_sorted(const auto &c) {
    if (!is_sorted(c.begin(), c.end())) print("un");
    print("sorted: ");
}

void printc(const auto &c) {
    check_sorted(c);
    for (auto& e : c) print("{} ", e);
    print("\n");
}

void print_things(const auto& c) {
    for (auto& v : c) print("{} ", v.str());
    print("\n");
}

struct things {
    string s;
    int i;

    string str() const {
        return format("({}, {})", s, i);
    }
};

int main() {
    vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printc(v);

vector<things> vthings { {"button", 40}, {"hamburger", 20},
    {"blog", 1000}, {"page", 100}, {"science", 60} };

    for (int i{3}; i; --i) {
        randomize(v);
        printc(v);
    }

    println("sort:");
    std::sort(v.begin(), v.end());
    printc(v);

    println("partial_sort:");
    randomize(v);
    auto middle {v.begin() + (v.size() / 2)};
    std::partial_sort(v.begin(), middle, v.end());
    printc(v);

    println("partition:");
    randomize(v);
    printc(v);
    std::partition(v.begin(), v.end(), [](int i) { return i > 5; });
    printc(v);

    println("things:");
    std::sort(vthings.begin(), vthings.end(),
            [](const things &lhs, const things &rhs) {
        return lhs.i < rhs.i;
    });
    print_things(vthings);

    std::sort(vthings.begin(), vthings.end(),
            [](const things &lhs, const things &rhs) {
        return lhs.s < rhs.s;
    });
    print_things(vthings);
}
