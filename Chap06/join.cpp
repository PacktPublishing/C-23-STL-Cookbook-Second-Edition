//  join.cpp by Bill Weinman [bw.org]
//  as of 2024-07-22

#include <print>
#include <string>
#include <string_view>
#include <vector>
#include <list>
#include <ranges>
#include <numbers>

using std::print, std::println;
using std::format;
using std::string;
using std::string_view;
using std::vector;
using std::list;

namespace ranges = std::ranges;
namespace views = ranges::views;

namespace bw {
    template<typename I>
    string join(I it, I end_it, const string_view sep = "") {
        string ostr {};
        if (it != end_it) ostr = format("{}", *it++);
        while (it != end_it) ostr = format("{}{}{}", ostr, sep, *it++);
        return ostr;
    }

    string join(const auto& c, const string_view sep = "") {
        return join(c.begin(), c.end(), sep);
    }
}

int main() {
    vector<string> lads {"john", "paul", "george", "ringo", "billy"};

    print("views::join: ");
    auto lads_view = views::join(lads);
    for(const char c : lads_view) print("{} ", c);
    print("\n");

    print("bw::join (string): ");
    println("{}", bw::join(lads, ", "));

    namespace num = std::numbers;
    print("bw::join (constants): ");
    list<double> constants {num::pi, num::e, num::sqrt2};
    println("{}", bw::join(constants, ", "));

    print("bw::join (lads_view): ");
    println("{}", bw::join(lads_view, ":"));
}
