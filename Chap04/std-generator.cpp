//  std-generator.cpp by Bill Weinman [bw.org]
//  as of 2024-07-08

#include <print>
#include <generator>

using std::print;

std::generator<long> gen_seq(long count) {
    for (long i {}; i < count; ++i) {
        co_yield i;
    }
}

int main() {
    for (auto i : gen_seq(10)) {
        print("{} ", i);
    }
    print("\n");
}
