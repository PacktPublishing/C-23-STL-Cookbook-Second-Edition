//  structured-binding.cpp
//  as of 2024-06-05 bw [bw.org]
#include <print>
#include <string>
#include <array>
#include <map>

using std::string;
using std::array;
using std::map;
using std::println;

// datum -----

struct things {
    int i{};
    char c{};
    long l{};
    string s{};
};

struct div_result {
    long quo;
    long rem;
};

// can't use size_t on MSVC b/c it's 32-bits
map<string, uint64_t> inhabitants {
    { "humans",   7000000001 },
    { "pokemon", 17863376 },
    { "klingons",   24246291 },
    { "cats",    1086881528 }
};

// workers -----

div_result int_div(const long & num, const long & denom) {
    struct div_result r{};
    r.quo = num / denom;
    r.rem = num % denom;
    return r;
}

// I like commas
string make_commas(const uint64_t& num) {
    auto s = std::to_string(num);
    for (auto l = static_cast<int>(s.length()) - 3; l > 0; l -= 3) {
        s.insert(l, ",");
    }
    return s;
}

// main -----

int main() {
    int nums[] {1, 2, 3, 4, 5};
    auto [ a, b, c, d, e ] = nums;
    println("{} {} {} {} {}", a, b, c, d, e);

    auto [quo, rem] = int_div(47, 5);
    println("quotient: {}, remainder {}", quo, rem);

    println("we got creatures --");
    for( const auto & [creature, pop] : inhabitants ) {
        println("there are {} {}",
            make_commas(pop), creature);
    }
}
