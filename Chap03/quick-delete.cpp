//  quick-delete.cpp by Bill Weinman [bw.org]
//  as of 2024-06-30

#include <print>
#include <vector>
#include <algorithm>

using std::print, std::println;
using std::vector;
using std::move;
using std::ranges::find;

void printc(auto & r) {
    print("size({}) ", r.size());
    for (auto & e : r) print("{} ", e);
    print("\n");
}

template<typename T>
void quick_delete(T& v, size_t idx) {
    if (idx < v.size()) {
        v[idx] = move(v.back());
        v.pop_back();
    }
}

template<typename T>
void quick_delete(T& v, typename T::iterator it) {
    if (it < v.end()) {
        *it = move(v.back());
        v.pop_back();
    }
}

int main() {
    vector v {12, 196, 47, 38, 19};
    printc(v);
    auto it = find(v, 47);
    quick_delete(v, it);
    printc(v);
    quick_delete(v, 1);
    printc(v);
}
