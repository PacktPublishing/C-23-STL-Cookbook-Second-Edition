//  zip-iterator.cpp by Bill Weinman [bw.org]
//  as of 2024-07-15

#include <print>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using std::print;
using std::string;
using std::vector;
using std::map;
using std::pair;

template<typename T>
class zip_iterator {
    using val_t = typename T::value_type;
    using ret_t = std::pair<val_t, val_t>;
    using it_t = typename T::iterator;

    it_t ita{};
    it_t itb{};

    // for begin() and end() objects
    it_t ita_begin{};
    it_t itb_begin{};
    it_t ita_end{};
    it_t itb_end{};

    // private constructor for begin() and end() objects
    zip_iterator(it_t ita, it_t itb) : ita {ita}, itb {itb} {}

public:
    using iterator_concept  = std::forward_iterator_tag;
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::pair<val_t, val_t>;
    using difference_type   = long int;
    using pointer           = const val_t*;
    using reference         = const val_t&;

    zip_iterator(T& a, T& b) :
        ita {a.begin()},
        itb {b.begin()},
        ita_begin {ita},
        itb_begin {itb},
        ita_end {a.end()},
        itb_end {b.end()}
    {}

    zip_iterator& operator++() {
        ++ita;
        ++itb;
        return *this;
    }

    bool operator==(const zip_iterator& o) const {
        return ita == o.ita || itb == o.itb;
    }

    bool operator!=(const zip_iterator& o) const {
        return !operator==(o);
    }

    ret_t operator*() const {
        return { *ita, *itb };
    }

    zip_iterator begin() const { return zip_iterator(ita_begin, itb_begin); }
    zip_iterator end() const { return zip_iterator(ita_end, itb_end); }
};

int main() {
    vector<std::string> vec_a {"Bob", "John", "Joni"};
    vector<std::string> vec_b {"Dylan", "Williams", "Mitchell"};

    print("vec_a: ");
    for(auto e : vec_a) print("{} ", e);
    print("\n");

    print("vec_b: ");
    for(auto e : vec_b) print("{} ", e);
    print("\n");

    print("zipped: ");
    for(auto [a, b] : zip_iterator(vec_a, vec_b)) {
        print("[{}, {}] ", a, b);
    }
    print("\n");

    map<string, string> name_map{};

    for(auto [a, b] : zip_iterator(vec_a, vec_b)) {
        name_map.try_emplace(a, b);
    }

    print("name_map: ");
    for(auto [a, b] : name_map) {
        print("[{}, {}] ", a, b);
    }
    print("\n");
}
