// mdspan.cpp by Bill Weinman [bw.org]
// as of 2024-05-19

#include <print>
#include <mdspan>
#include <vector>

using std::print, std::println;
using std::vector;
using std::mdspan;

int main() {
    vector v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    mdspan mds2(v.data(), 2, 6);
    mdspan mds3(v.data(), 2, 3, 2);

    auto print_v = [](auto v) {
        for (auto n : v) {
            print("{} ", n);
        }
        println("");
    };

    print_v(v);
    println("----------");

    for (size_t i1 {0}; i1 < mds2.extent(0); ++i1) {
        for (size_t i2 {0}; i2 < mds2.extent(1); ++i2) {
            print("[{},{}] {:02d} ", i1, i2, mds2[i1,i2]);
        }
        println("");
    }
    
    println("----------");
    
    for (size_t i1 {0}; i1 < mds3.extent(0); ++i1) {
        for (size_t i2 {0}; i2 < mds3.extent(1); ++i2) {
            for (size_t i3 {0}; i3 < mds3.extent(2); ++i3) {
                print("[{},{},{}] {:03d} ",
                      i1, i2, i3, mds3[i1,i2,i3]);
            }
            println("");
        }
    }
    
    println("----------");
    for (size_t i1 {0}; i1 < mds2.extent(0); ++i1) {
        for (size_t i2 {0}; i2 < mds2.extent(1); ++i2) {
            mds2[i1, i2] = mds2[i1, i2] * 10 + (int)i2;
        }
    }
    print_v(v);
}

