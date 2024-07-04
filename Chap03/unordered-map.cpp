//  unordered-map.cpp by Bill Weinman [bw.org]
//  as of 2024-07-01

#include <print>
#include <unordered_map>
#include <string>

using std::print;
using std::unordered_map;

struct Coord {
    int x {};
    int y {};
};

using Coordmap = unordered_map<Coord, int>;

bool operator==(const Coord& lhs, const Coord& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

namespace std {
    template<>
    struct hash<Coord> {
        size_t operator()(const Coord& c) const {
            return static_cast<size_t>(c.x)
                 + static_cast<size_t>(c.y);
        }
    };
}

void print_Coordmap(const Coordmap& m) {
    for (const auto& [key, value] : m) {
        print("{{ ({}, {}): {} }} ",
            key.x, key.y, value);
    }
    print("\n");
}

int main() {
    Coordmap m {
        { {0, 0}, 1 },
        { {0, 1}, 2 },
        { {2, 1}, 3 }
    };
    print_Coordmap(m);

    Coord k{ 0, 1 };
    print("{{ ({}, {}): {} }}\n",
        k.x, k.y, m.at(k));
}
