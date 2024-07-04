//  rpn.cpp by Bill Weinman [bw.org]
//  as of 2024-07-03

#include <print>
#include <iostream>
#include <deque>
#include <map>
#include <string>
#include <utility>
#include <cctype>
#include <cmath>
#include <iterator>
#include <limits>

using std::format;
using std::println;
using std::deque;
using std::map;
using std::string;
using std::pair;
using std::istream_iterator;
using std::cin;

class RPN {
    deque<double> stk{};
    constexpr static double zero {0.0};
    constexpr static double inf {std::numeric_limits<double>::infinity()};

public:
    // process an operand/operator
    double op(const string & s) {
        if (is_numeric(s)) {
            double v{stod(s, nullptr)};
            stk.push_front(v);
            return v;
        }
        else return optor(s);
    }

    // empty the stack
    void clear() {
        stk.clear();
    }

    // print the stack
    string get_stack_string() const {
        string s{};
        for (auto v : stk) {
            s += format("{} ", v);
        }
        return s;
    }

private:    // utility functions
    // pop and get two operands
    pair<double, double> pop_get2() {
        if (stk.size() < 2) return {zero, zero};
        double v1{stk.front()};
        stk.pop_front();
        double v2{stk.front()};
        stk.pop_front();
        return {v2, v1};
    }

    bool is_numeric(const string& s) {
        for (const char c : s) {
            if (c != '.' && !std::isdigit(c)) return false;
        }
        return true;
    }

    // operators
    double optor(const string& op) {
        map<string, double (*)(double, double)> opmap {
            {"+", [](double l, double r){ return l + r; }},
            {"-", [](double l, double r){ return l - r; }},
            {"*", [](double l, double r){ return l * r; }},
            {"/", [](double l, double r){ return l / r; }},
            {"^", [](double l, double r){ return pow(l, r); }},
            {"%", [](double l, double r){ return fmod(l, r); }}
        };

        if (opmap.find(op) == opmap.end()) return zero;
        auto [l, r] = pop_get2();

        // don’t divide by zero
        if (op == "/" && r == zero) stk.push_front(inf);
        else stk.push_front(opmap.at(op)(l, r));
        return stk.front();
    }
};

int main() {
    RPN rpn;

    for (string o{}; cin >> o; ) {
        rpn.op(o);
        auto stack_str = rpn.get_stack_string();
        println("{}: {}", o, stack_str);
    }
}
