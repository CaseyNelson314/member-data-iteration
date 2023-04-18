struct Integer
{
    int value;

    template<typename T>
    void archive(T& ar)
    {
        ar(value);
    }
};

struct Vec2
{
    Integer i;
    double x;
    double y;

    template<typename T>
    void archive(T& ar)
    {
        ar(i, x, y);
    }
};

#include <algorithm>

void Serialize()
{

}

struct Serializer
{

    void operator()(double)
    {
    }

    template<typename T>
    void operator()(T& rhs)
    {
        rhs.archive(*this);
    }

    template<typename Head, typename... Tails>
    void operator()(Head&& head, Tails&&... tails)
    {
        //this->operator(head);
        (*this)(head);
        (*this)(tails...);
        //this->operator(tails)...;
    }
};

#include <iostream>

int main()
{

    Serializer serializer;
    Vec2 vec;

    serializer(vec);

}
