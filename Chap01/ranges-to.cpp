// ranges-to.cpp by Bill Weinman [bw.org]
// as of 2024-05-27

#include <ranges>
#include <vector>
#include <list>
#include <print>
using std::print;
using std::vector;
using std::list;
namespace ranges = std::ranges;
namespace views = ranges::views;

int main() {
    auto vec = views::iota(1, 11) 
        | views::transform([](const auto n){ return n * 5; }) 
        | ranges::to<vector>();
    for (auto n : vec) print("{} ", n);
    print("\n");

    auto lst = vec | views::reverse
        | ranges::to<list<double>>();
    for (auto d : lst) print("{} ", d);
    print("\n");
}
