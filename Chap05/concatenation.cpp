//  concatenation.cpp by Bill Weinman [bw.org]
//  as of 2024-07-20

#include <print>
#include <string>
#include <functional>

using std::println;
using std::string;

template <typename T, typename ...Ts>
auto concat(const T t, const Ts ...ts) {
    if constexpr (sizeof...(ts) > 0) {
        return [=](const auto ...parameters) { 
            return t(concat(ts...)(parameters...));
        };
    } else  {
        return t;
    }
}

int main() {
    auto twice = [](const auto i) { return i * 2; };
    auto thrice = [](const auto i) { return i * 3; };

    auto combined = concat(thrice, twice, std::plus<int>{});

    println("{}", combined(2, 3));
}
