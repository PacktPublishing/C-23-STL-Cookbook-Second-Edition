// ranges.cpp by Bill Weinman [bw.org]
// updated 2024-08-15

#include <print>
#include <vector>
#include <random>
#include <numeric>
#include <ranges>

using std::print;
using std::vector;

namespace ranges = std::ranges;
namespace views = ranges::views;


void p_range(auto r) {
    for (const auto& v : r) print("{} ", v);
    print("\n");
}

auto rng() {
    std::random_device rd {};
    return std::mt19937(rd());
}

int main() {
    auto even = [](auto i) { return 0 == i % 2; };
    auto square = [](auto i) { return i * i; };

    const auto r = views::iota(0, 10);
    p_range(r);
    
    vector<int> v1 (r.size());
    ranges::copy(r, v1.begin());
    p_range(v1);
    
    vector<int> v2 {};
    ranges::copy(r, std::back_inserter(v2));
    p_range(v2);
    
    vector<int> v3 = r | views::transform(square) | ranges::to<vector<int>>();
    p_range(v3);

    for (int i {}; i < 5; ++i) {
        ranges::shuffle(v1, rng());
        p_range(v1);
    }

    ranges::sort(v1);
    p_range(v1);

    p_range(views::iota(0) | views::take(10));

    p_range(r | views::filter(even) | views::transform(square) | views::reverse);

}
