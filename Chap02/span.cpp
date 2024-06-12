//  span.cpp
//  as of 2024-06-04 [bw.org]
#include <print>
#include <span>

using std::print;
using std::span;

template<typename T>
void pspan(span<T> s) {
    print("number of elements: {}\n", s.size());
    print("size of span: {}\n", s.size_bytes());
    for(auto e : s) print("{} ", e);
    print("\n");
}

int main() {
    int ca1[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    pspan<int>(ca1);
}
