//  uniform-erasure.cpp by Bill Weinman [bw.org]
//  as of 2024-06-30

#include <print>
#include <string>
#include <vector>
#include <map>
#include <list>

using std::print, std::println;
using std::string, std::vector, std::map, std::list;
using std::erase, std::erase_if;

void printc(auto& r) {
    print("size: {}: ", r.size());
    for (auto& e : r) print("{} ", e);
    print("\n");
}

void print_assoc(auto& r) {
    print("size: {}: ", r.size());
    for (auto& [k, v] : r) print("{}:{} ", k, v);
    print("\n");
}

int main() {

    {
        println("initialize vector:");
        vector v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        printc(v);
        println("erase 5:");
        erase(v, 5);
        printc(v);
    }

    {
        println("initialize list:");
        list v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        printc(v);
        println("erase 5:");
        erase(v, 5);
        printc(v);
    }

    {
        println("initialize vector:");
        vector v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        printc(v);
        println("erase_if even:");
        erase_if(v, [](auto x) { return x % 2 == 0; });
        printc(v);
    }

    println("initialize map:");
    map<int, string> m{ {1, "uno"}, {2, "dos"}, {3, "tres"}, {4, "quatro"}, {5, "cinco"} };
    print_assoc(m);
    println("erase_if even:");
    erase_if(m, [](auto& p) { auto& [k, v] = p; return k % 2 == 0; });
    print_assoc(m);
}
