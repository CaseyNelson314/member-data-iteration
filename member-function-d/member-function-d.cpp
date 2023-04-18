struct Integer
{

    int value;

    template<typename T>
    constexpr void accessor(T& acc)
    {
        acc(value);
    }

    void accessor()
    {

    }

};

struct Vec2
{

    Integer i;
    double x;
    double y;

    template<typename T>
    constexpr void accessor(T& acc)
    {
        acc(i, x, y);
    }
};

#include <algorithm>
#include <iostream>
#include <type_traits>

#include "HasMember.hpp"


struct Serializer
{
    template<typename T>
    constexpr auto operator()(T rhs) -> std::enable_if_t<std::is_integral_v<T>>
    {
        std::cout << "integer: " << rhs << std::endl;
    }
    template<typename T>
    constexpr auto operator()(T rhs) -> std::enable_if_t<std::is_floating_point_v<T>>
    {
        std::cout << "float point: " << rhs << std::endl;
    }

    template<typename T>
    constexpr void operator()(T& rhs)
    {
        rhs.accessor(*this);
    }

    template<typename Head, typename... Tails>
    constexpr void operator()(Head&& head, Tails&&... tails)
    {
        (*this)(std::forward<Head>(head));
        (*this)(std::forward<Tails>(tails)...);
    }
};

#include <iostream>

struct Hoge
{
    template<typename T>
    void serialize(T&, int)
    {

    }
};

int main()
{

    Serializer serializer;
    Vec2 vec;

    //serializer(vec);

    has_member_serialize<Serializer, Hoge>::value;

}
