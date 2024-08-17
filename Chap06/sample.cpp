//  sample.cpp by Bill Weinman [bw.org]
//  as of 2024-07-25

#include <print>
#include <array>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>
#include <map>

using std::println;
using std::array;
using std::string;
using std::sample;

// standard library doesn't have
// a version of round that returns int
int iround(const double& d) {
    return static_cast<int>(std::round(d));
}

int main() {
    // constants
    constexpr size_t n_data {200000};
    constexpr size_t n_samples {500};
    constexpr int mean {};
    constexpr size_t dev {3};

    // rng and distribution objects
    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<> dist(mean, dev);

    // array of random int of normal distribution
    array<int, n_data> data {};
    for (auto& e : data) e = iround(dist(rng));

    // sample the array data
    array<int, n_samples> samples {};
    sample(data.begin(), data.end(), samples.begin(), n_samples, rng);

    // create histogram
    std::map<int, size_t> hist {};
    for (const int i : samples) ++hist[i];

    // display histogram
    constexpr size_t scale {3};
    println("{:>3} {:>5} {:<}/{}", "n", "count", "graph", scale);
    for (const auto& [value, count] : hist) {
        println("{:>3} ({:>3}) {}", value, count, string(count / scale, '*'));
    }
}
