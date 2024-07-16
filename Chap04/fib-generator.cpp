//  fib-generator.cpp by Bill Weinman [bw.org]
//  as of 2024-07-09

#include <print>
#include <string_view>
#include <algorithm>
#include <ranges>

using std::print;
using std::string_view;

namespace ranges = std::ranges;

void printc(const auto & v, const string_view s = "") {
    if (!s.empty()) print("{}: ", s);
    for (auto e : v) print("{} ", e);
    print("\n");
}

template<typename T>
class fib_generator {
    T stop {};
    T count {};
    T n1 {0};
    T n2 {1};

    constexpr void do_fib() {
        const T prev_n2 = n2;
        n2 += n1;
        n1 = prev_n2;
    }

public:
    using iterator_concept  = std::forward_iterator_tag;
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::remove_cv_t<T>;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const T*;
    using reference         = const T&;

    explicit fib_generator(T fib_stop = 0) : stop {fib_stop} {}

    T operator*() const { return n2; }

    constexpr fib_generator& operator++() {
        do_fib();
        ++count;
        return *this;
    }

    fib_generator operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }

    bool operator!=(const fib_generator& o) const {
        return count != o.count;
    }

    bool operator==(const fib_generator& o) const {
        return count == o.count;
    }

    const fib_generator& begin() const { return *this; }

    const fib_generator end() const {
        auto sentinel = fib_generator();
        sentinel.count = stop;
        return sentinel;
    }

    T size() { return stop; }

};

int main() {
    using ulong = unsigned long;
    printc(fib_generator<ulong>(10));

    fib_generator<ulong> fib(10);
    auto x = fib | ranges::views::transform([](unsigned long x){ return x * x; });
    printc(x, "squared:");
}
