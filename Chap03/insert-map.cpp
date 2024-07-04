//  insert-map.cpp by Bill Weinman [bw.org]
//  as of 2024-07-01 

#include <print>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

using std::print, std::println;
using std::map;
using std::unordered_map;
using std::string;

struct BigThing {
    string value;
    BigThing(const char * v) : value(v) {
        println("BigThing constructed {}", value);
    }
};

using Mymap = map<string, BigThing>;   // convenience alias

void printm(Mymap& m) {
    for(auto& [k, v] : m) {
        print("[{}:{}] ", k, v.value);
    }
    print("\n");
}

int main() {
    Mymap m;

    m.try_emplace("Miles", "Trumpet");
    m.try_emplace("Hendrix", "Guitar");
    m.try_emplace("Krupa", "Drums");
    m.try_emplace("Zappa", "Guitar");
    m.try_emplace("Liszt", "Piano");
    printm(m);

    print("\n");
    println("emplace(Hendrix)");
    m.emplace("Hendrix", "Singer");
    println("try_emplace(Zappa)");
    m.try_emplace("Zappa", "Composer");
    printm(m);

    const char * key{"Zappa"};
    const char * payload{"Composer"};
    if(auto [it, success] = m.try_emplace(key, payload); !success) {
        println("update");
        it->second = payload;
    }
    printm(m);
}
