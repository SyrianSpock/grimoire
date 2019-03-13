#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <variant>
#include <vector>

using var_t = std::variant<int, long, double, std::string>;

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main() {
    std::vector<var_t> vec = {10, 15l, 1.5, "hello"};

    for (auto& v: vec) {
        std::visit(overloaded {
            [](int arg) { std::cout << "this is a int: " << arg << '\n'; },
            [](long arg) { std::cout << "this is a long: " << arg << '\n'; },
            [](double arg) { std::cout << "this is a double: " << std::fixed << arg << '\n'; },
            [](const std::string& arg) { std::cout << "this is a string: " << std::quoted(arg) << '\n'; },
        }, v);
    }

    double sum = std::accumulate(vec.begin(), vec.end(), 0.0, [](double a, auto v) {
        return a + std::visit(overloaded {
            [](int arg) -> double { return arg; },
            [](long arg) -> double { return arg; },
            [](double arg) -> double { return arg; },
            [](const std::string& arg) -> double { return 0; },
        }, v);
    });
    std::cout << "Computed sum: " << sum << std::endl;
}
