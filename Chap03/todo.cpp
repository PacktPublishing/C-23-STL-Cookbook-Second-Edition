//  todo.cpp by Bill Weinman [bw.org]
//  as of 2024-07-03

#include <print>
#include <string>
#include <map>

using std::println;
using std::string;
using std::multimap;

using todomap = multimap<int, string>;

void rprint(todomap& todo) {
    for (auto it = todo.rbegin(); it != todo.rend(); ++it) {
        println("{}: {}", it->first, it->second);
    }
    println("");
}

int main() {
    todomap todo {
        {1, "wash dishes"},
        {0, "watch teevee"},
        {2, "do homework"},
        {0, "read comics"}
    };
    rprint(todo);
}
