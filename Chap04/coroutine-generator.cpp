//  coroutine-generator.cpp by Bill Weinman [bw.org]
//  as of 2024-07-14

#include <print>
#include <coroutine>
#include <ranges>

namespace views = std::ranges::views;

using std::print;

template<typename T>
class co_gen {
public:
    struct promise_type;    // forward declaration
    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro {};

    co_gen(handle_type h) : coro(h) {}

    ~co_gen() {
        if (coro) coro.destroy();
    }

    operator bool() {
        coro.resume();
        return !coro.done();
    }
    
    T operator ()() {
        return coro.promise().value;
    }

    struct promise_type {
        T value;

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::exit(1); }
        void return_void() {}

        co_gen get_return_object() {
            return {handle_type::from_promise(*this)};
        }

        std::suspend_always yield_value(T v) {
            value = v;
            return {};
        }

    };

     class iterator {
         handle_type coro {};
     public:
         using iterator_concept  = std::forward_iterator_tag;
         using iterator_category = std::forward_iterator_tag;
         using value_type = std::remove_cv_t<T>;
         using difference_type = std::ptrdiff_t;
         using pointer = T*;
         using reference = T&;

         iterator() : coro(nullptr) {}
         iterator(handle_type h) : coro(h) {}

         T& operator*() const {
             return coro.promise().value;
         }

         T* operator->() const {
             return &coro.promise().value;
         }

         iterator& operator++() {
             coro.resume();
             if (coro.done()) coro = nullptr;
             return *this;
         }

         iterator operator++(int) {
             iterator temp = *this;
             ++*this;
             return temp;
         }

         bool operator==(const iterator& other) const {
             return coro == other.coro;
         }

         bool operator!=(const iterator& other) const {
             return !(*this == other);
         }
     };

     iterator begin() {
         if (coro) coro.resume();
         if (coro.done()) return iterator{nullptr};
         return iterator{coro};
     }

     iterator end() {
         return iterator{nullptr};
     }
};

template<typename T>
co_gen<T> gen_fib(T count) {
    T n1 {}, n2 {1};
    auto do_fib = [&n1, &n2] {
        const T prev_n2 = n2;
        n2 += n1;
        n1 = prev_n2;
        return n1;
    };

    for (T i = 0; i < count; ++i) {
        co_yield do_fib();
    }
}

template<typename T>
co_gen<T> gen_seq(T count) {
    for (T i {}; i < count; ++i) {
        co_yield i;
    }
}

int main() {
    using ulong = unsigned long;
    auto gen1 = gen_seq<ulong>(10);
    while (gen1) {
        print("{} ", gen1());
    }
    print("\n");
    
     for (auto i : gen_fib<ulong>(10)) {
         print("{} ", i);
     }
     print("\n");

     print("squared: ");
     auto gen2 = gen_fib<ulong>(10);
     for (auto i : gen2 | views::transform([](unsigned long x){ return x * x; })) {
         print("{} ", i);
     }
     print("\n");
}
 
