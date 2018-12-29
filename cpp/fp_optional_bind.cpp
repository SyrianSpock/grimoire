#include <iostream>
#include <optional>
#include <cmath>

using std::optional;

template <typename T, typename funcType> auto operator>>=(funcType &&f, const optional<T>& x)
{
    if (x)  { return f(x.value()); }
    else    { return decltype(f(std::declval<T>())){}; }
}

inline std::ostream& operator<<(std::ostream& os, const optional<double>& x)
{
    if (x) { os << "Value: " << x.value() << std::endl; }
    else   { os << "No value" << std::endl; }
    return os;
}

optional<double> squareRoot(double x)
{
    if (x >= 0) { return sqrt(x); }
    else        { return {}; }
}

optional<double> divide(double x, double y)
{
    if (y != 0) { return x / y; }
    else        { return {}; }
}

int main(int, char **)
{
    std::cout << (squareRoot >>= optional<double>(16.));
    std::cout << (squareRoot >>= optional<double>(-10.));
    std::cout << (squareRoot >>= optional<double>());

    std::cout << ([](auto x){return divide(x, 2.);} >>= optional<double>(10.));

    return 0;
}
