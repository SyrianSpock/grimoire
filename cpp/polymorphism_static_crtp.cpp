#include <iostream>

template<class Self>
class Base
{
public:
    Self* self() { return static_cast<Self*>(this); }

    int dostuff(int x)
    {
        return self()->op(x);
    }

    int op(int x)
    {
        return x * 2;
    }
};

class Derived : public Base<Derived>
{
public:
    Derived(int x) : m_x(x) {}

    int op(int x)
    {
        return x * m_x;
    }

private:
    int m_x;
};

int main()
{
    Derived d(5);
    std::cout << d.dostuff(2) << std::endl;
}
