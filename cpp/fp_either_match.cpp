#include <iostream>
#include <variant>
#include <iomanip>
#include <vector>
#include <cmath>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <typename E, typename T> class Either
{
private:
    std::variant<E, T> m_data;

public:
    Either(std::variant<E, T> data) : m_data(data) {}

    template<typename ApplyLeft, typename ApplyRight>
    decltype(auto) match(ApplyLeft&& left, ApplyRight&& right) const
    {
        return std::visit(overloaded {
            std::forward<ApplyLeft>(left),
            std::forward<ApplyRight>(right)
        }, m_data);
    }

    bool isLeft() const {
        return std::holds_alternative<E>(m_data);
    }

    bool isRight() const {
        return std::holds_alternative<T>(m_data);
    }

    E fromLeft() const {
        return std::get<E>(m_data);
    }

    T fromRight() const {
        return std::get<T>(m_data);
    }
};

template <typename E, typename T> auto Left(E left)
{
    return Either<E, T>(left);
}

template <typename E, typename T> auto Right(T right)
{
    return Either<E, T>(right);
}

template <typename E, typename T, typename funcType>
decltype(auto) operator>>=(funcType &&f, const Either<E, T>& x)
{
    return x.match(
        [&](const E& e){ return x; },
        [&](const T& t){ return f(t); }
    );
}

template <typename E, typename T> inline std::ostream& operator<<(std::ostream& os, const Either<E, T>& x)
{
    x.match(
        [&](const E& e){ os << "Value '" << e << "' is left" << std::endl; },
        [&](const T& t){ os << "Value '" << t << "' is right" << std::endl; }
    );
    return os;
}

Either<std::string, double> squareRoot(double x)
{
    if (x >= 0) { return Right<std::string, double>(sqrt(x)); }
    else        { return Left<std::string, double>("Undefined square root of negative number"); }
}

Either<std::string, double> divide(double x, double y)
{
    if (y != 0) { return Right<std::string, double>(x / y); }
    else        { return Left<std::string, double>("Division by zero"); }
}

int main(int, char **)
{
    std::cout << Right<std::string, int>(10);
    std::cout << Left<std::string, int>("failed");

    std::cout << squareRoot(10);
    std::cout << squareRoot(-10);

    std::cout << divide(10, 5);
    std::cout << divide(10, 0);

    std::cout << (squareRoot >>= Right<std::string, double>(16.));
    std::cout << (squareRoot >>= Right<std::string, double>(-16.));
    std::cout << (squareRoot >>= Left<std::string, double>("Input error"));

    auto one_over = [](auto x){ return divide(1, x); };
    std::cout << (one_over >>= Right<std::string, double>(10.));
    std::cout << (one_over >>= Right<std::string, double>(0.));

    std::cout << (squareRoot >>= (one_over >>= Right<std::string, double>(-5.)));
    std::cout << (one_over >>= (squareRoot >>= Right<std::string, double>(0.)));

    return 0;
}
