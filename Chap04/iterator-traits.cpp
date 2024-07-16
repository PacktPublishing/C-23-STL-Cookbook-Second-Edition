//  iterator-traits.cpp by Bill Weinman [bw.org]
//  as of 2024-07-07

#include <print>
#include <algorithm>
#include <iterator>
#include <ranges>

using std::print;

namespace ranges = std::ranges;

template<typename T>
class Seq {
    T seq_start{};
    T seq_end{};

public:
    Seq(T start, T end) : seq_start{ start }, seq_end{ end } {}

    class iterator {
        T it_value{};
    public:
        using iterator_concept  = std::forward_iterator_tag;
        using iterator_category = std::forward_iterator_tag;
        using value_type        = std::remove_cv_t<T>;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        explicit iterator(T position = 0) : it_value{position} {}

        T operator*() const { return it_value; }

        iterator& operator++() {
            ++it_value;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++*this;
            return temp;
        }

        bool operator!=(const iterator& other) const noexcept {
            return it_value != other.it_value;
        }

        bool operator==(const iterator& other) const noexcept {
            return it_value == other.it_value;
        }
    };

    iterator begin() const { return iterator{seq_start}; }
    iterator end() const { return iterator{seq_end}; }
};

template<typename T>
requires std::forward_iterator<typename T::iterator>
void printc(const T & c) {
    for(auto v : c) {
        print("{} ", v);
    }
    print("\n");
}

int main() {
    Seq<int> r(100, 110);

    auto [min_it, max_it] = ranges::minmax_element(r);
    print("{} - {}\n", *min_it, *max_it);

    printc(r);
    
    static_assert(ranges::forward_range<Seq<int>>);
}
