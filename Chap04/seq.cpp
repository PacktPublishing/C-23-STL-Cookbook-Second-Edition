//  seq.cpp by Bill Weinman [bw.org]
//  as of 2024-07-05

#include <print>

using std::print;

template<typename T>
class Seq {
    T seq_start{};
    T seq_end{};

public:
    Seq(T start, T end) : seq_start {start}, seq_end {end} {}

    class iterator {
        T it_value{};
    public:
        explicit iterator(T position = 0) : it_value {position} {}

        T operator*() const { return it_value; }

        iterator& operator++() {
            ++it_value;
            return *this;
        }

        bool operator!=(const Seq::iterator& other) const {
            return it_value != other.it_value;
        }
    };

    iterator begin() const { return iterator {seq_start}; }
    iterator end() const { return iterator {seq_end}; }
};

int main() {
    Seq<int> r(100, 110);

    for (auto v : r) {
        print("{} ", v);
    }
    print("\n");
}
