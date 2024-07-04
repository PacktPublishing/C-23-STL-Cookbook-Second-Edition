//  set-words.cpp by Bill Weinman [bw.org]
//  as of 2024-07-02

#include <print>
#include <iostream>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>

using std::print;
using std::set;
using std::string;
using std::istream_iterator;
using std::cin;
using std::copy;
using std::inserter;

using input_it = istream_iterator<string>;

int main() {
    set<string> words;

    input_it it {cin};
    input_it end{};

    copy(it, end, inserter(words, words.end()));
    
    for (const string & w : words) {
        print("{} ", w);
    }
    print("\n");
}
