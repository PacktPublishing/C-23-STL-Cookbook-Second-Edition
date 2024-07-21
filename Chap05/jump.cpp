//  jump.cpp by Bill Weinman [bw.org]
//  as of 2024-07-20

#include <print>
#include <cstdio>
#include <map>

using std::println;
using std::getchar;

const char prompt(const char * p) {
    constexpr size_t BUFLEN {4};
    constexpr int NL {'\n'};
    char bufin[BUFLEN] {};
    int bufchar {};

    // fold char to uppercase
    auto char_upper = [](char c) ->char {
        if (c >= 'a' && c <= 'z') return c - ('a' - 'A');
        else return c;
    };

    // flush the input buffer
    auto flush_stdin = []{
        int c {};
        while (c != NL && c != EOF) c = getchar();
    };

    std::print("{} > ", p);
    for (size_t i {}; i < BUFLEN && (bufchar = getchar()) != NL; ++i) {
        bufin[i] = (char) bufchar;
    }

    if (bufchar != NL) flush_stdin();
    if (bufchar == EOF) exit(0);

    const char r0 = bufin[0];
    const char r1 = bufin[1];

    if (r0 == 0 || r0 == NL) return 0;
    else if (r1 != 0 && r1 != NL) {
        println("Response too long");
        return 0;
    }
    else return char_upper(r0);
}

const bool jump(const char select) {
    using jumpfunc = void(*)();

    static const std::map<char, jumpfunc> jumpmap {
        { 'A', []{ println("func A"); } },
        { 'B', []{ println("func B"); } },
        { 'C', []{ println("func C"); } },
        { 'D', []{ println("func D"); } },
    };
    
    const auto it = jumpmap.find(select);
    if (it != jumpmap.end()) it->second();
    else {
        println("Invalid response");
        return false;
    }
    return true;
}

int main() {
    const char* pstr {"What to do? (A/B/C/D/X)"};
    for (auto key = prompt(pstr); key != 'X'; key = prompt(pstr)) {
        if (key) jump(key);
    }
    println("Bye!");
}
