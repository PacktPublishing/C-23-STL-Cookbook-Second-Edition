//  container-iterator.cpp by Bill Weinman [bw.org]]
//  as of 2024-07-04

#include <print>
#include <string>
#include <initializer_list>
#include <compare>
#include <iterator>
#include <stdexcept>
#include <memory>
#include <ranges>
#include <algorithm>

using std::print, std::println;
using std::string;
using std::initializer_list;

namespace ranges = std::ranges;
namespace views = std::ranges::views;

template<typename T>
class Container {
    std::unique_ptr<T[]> c_ptr {};
    size_t n_elements{};

public:
    Container(initializer_list<T> i_lst) : n_elements {i_lst.size()} {
        c_ptr = std::make_unique<T[]>(n_elements);
        size_t index {0};
        for (T el : i_lst) {
            c_ptr[index++] = el;
        }
    }
    
    Container(size_t sz) : n_elements{sz} {
        c_ptr = std::make_unique<T[]>(n_elements);
    }
    
    size_t size() const {
        return n_elements;
    }

    const T& operator[](const size_t index) const {
        return c_ptr[index];
    }

    T& at(const size_t index) const {
        if (index > n_elements - 1) {
            throw std::out_of_range("Container::at(): index out of range");
        }
        return c_ptr[index];
    }

    bool empty() const {
        return (n_elements == 0);
    }

    class iterator {
        T* ptr;

    public:
        // iterator traits
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::contiguous_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        // iterator constructor with default
        iterator(T* pptr = nullptr) : ptr{pptr} {}

        // iterator operators
        iterator& operator++() {
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            auto ret = *this;
            ++ptr;
            return ret;
        }

        iterator& operator--() {
            --ptr;
            return *this;
        }

        iterator operator--(int) {
            auto ret = *this;
            --ptr;
            return ret;
        }

        T& operator[](const size_t index) const {
            return *(ptr + index);
        }

        // default comparison operator (C++20)
        const auto operator<=>(const iterator& o) const {
            return ptr <=> o.ptr;
        }

        const bool operator==(const iterator& o) const {
            return ptr == o.ptr;
        }

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        iterator operator+(const size_t n) const {
            return iterator(ptr + n);
        }

        // non-member operator (n + it)
        friend const iterator operator+(const size_t n, const iterator& o) {
            return iterator(o.ptr + n);
        }

        const iterator operator-(const size_t n) {
         return iterator(ptr - n);
        }
        
        const size_t operator-(const iterator& o) {
         return ptr - o.ptr;
        }

        iterator& operator+=(const size_t n) {
            ptr += n;
            return *this;
        }

        iterator& operator-=(const size_t n) {
            ptr -= n;
            return *this;
        }

    };

    // begin/end call iterator contsructor
    iterator begin() const { return iterator(c_ptr.get()); }
    iterator end() const { return iterator(c_ptr.get() + n_elements); }
};

void unit_tests(Container<string>& x) {
    println("\nunit tests =============================");

    auto a = x.begin();
    auto b = x.begin() + 5;
    auto n = b - a;
    bool r {};

    println("*a: {}", *a);
    println("*b: {}", *b);
    println("n: {}", n);
    
    r = (a += n) == b;
    println("{}: (a += n) == b", r);

    a = x.begin();
    r = std::addressof(a += n) == std::addressof(a);
    println("{}: std::addressof(a += n) == std::addressof(a)", r);

    a = x.begin();
    auto it1 = (a + n);
    auto it2 = (a += n);
    r = it1 == it2;
    println("{}: (a + n) == (a += n)", r);

    a = x.begin();
    r = (a + n) == (n + a);
    println("{}: (a + n) == (n + a)", r);
    
    int i {1};
    int j {2};
    r = a + (i + j) == (a + i) + j;
    println("{}: a + (i + j) == (a + i) + j", r);

    r = a + 0 == a;
    println("{}: a + 0 == a", r);

    b = x.begin() + n;
    r = --b == (a + (n - 1));
    println("{}: --b == (a + (n - 1))", r);

    // the following may give a warning about unary minus on unsigned
    // type -- n is unsigned but this is part of the standard test 
    b = x.begin() + n;
    it1 = b += -n;
    b = x.begin() + n;
    it2 = b -= n;
    r = it1 == a && it2 == a;
    println("{}: (b += -n) == a && (b -= n) == a", r);

    b = x.begin() + n;
    r = std::addressof(b -= n) == std::addressof(b);
    println("{}: std::addressof(b -= n) == std::addressof(b)", r);

    b = x.begin() + n;
    it1 = b - n;
    b = x.begin() + n;
    it2 = b -= n;
    r = it1 == a && it2 == a;
    println("{}: (b - n) == (b -= n)", r);

    b = x.begin() + n;
    r = a[n] == *b;
    println("{}: a[n] == *b", r);

    r = (a <= b);
    println("{}: (a <= b)", r);
}

int main() {
    Container<string> x{"one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine", "ten" };
    println("Container x size: {}", x.size());

    println("Container x:");
    for (auto e : x) {
        print("{} ", e);
    }
    print("\n");

    println("direct access elements:");
    println("element at(5): {}", x.at(5));
    println("element [5]: {}", x[5]);
    println("element begin + 5: {}", *(x.begin() + 5));
    println("element 5 + begin: {}", *(5 + x.begin()));
    println("element begin += 5: {}", *(x.begin() += 5));

    println("views pipe reverse:");
    auto result = x | views::reverse;
    for (auto v : result) print("{} ", v);
    print("\n");

    Container<string> y(x.size());
    println("Container y size: {}\n", y.size());
    for (auto e : y) {
        print("[{}] ", e);
    }
    print("\n");

    unit_tests(x);
}
