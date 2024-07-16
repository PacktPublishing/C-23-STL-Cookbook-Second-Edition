//  sentinel.cpp by Bill Weinman [bw.org]
//  as of 2024-07-14

#include <print>
#include <string_view>

using std::print;
using std::string_view;
using std::vector;

using sentinel_t = const char;
constexpr sentinel_t nullchar {'\0'};

class cstr_it {
    const char *s {};

public:
    explicit cstr_it(const char *str) : s {str} {}

    char operator*() const { return *s; }

    cstr_it& operator++() {
        ++s;
        return *this;
    }

    bool operator!=(sentinel_t) const {
        return s != nullptr && *s != nullchar;
    }

    cstr_it begin() const { return *this; }
    sentinel_t end() const { return nullchar; }
};

void print_cstr(const char * s) {
    print("{}: ", s);
    for (char c : cstr_it(s)) {
        print("{:02x} ", c);
    }
    print("\n");
}

int main() {
    const char carray[] {"array"};
    print_cstr(carray);

    const char * cstr {"c-string"};
    print_cstr(cstr);
}
