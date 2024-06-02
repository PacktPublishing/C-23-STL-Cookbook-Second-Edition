// generator.cpp by Bill Weinman [bw.org]
// as of 2024-05-27

#include <generator>
#include <ranges>
#include <print>
using std::print;
namespace views = std::ranges::views;

template<typename T>
std::generator<T> primes() {
    constexpr auto isprime = [](const T& n) {
        for (T i {2}; i < n / 2; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    };
    for (T n : views::iota(2)) {
        if (!isprime(n)) continue;
        co_yield n;
    }
}

int main() {
    for (auto n : primes<uint64_t>() | views::take(25)) {
        print("{} ", n);
    }
    print("\n");
}
