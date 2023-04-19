//////////////////////////////////////////////////////////////
// 
//  Iterate member variables.
// 
//  Copyright (c) 2023 CaseyNelson314
// 
//  Licensed under the MIT License.
//
//////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

#define UDON_HAS_MEMBER_ACSESS_FUNCTION(name)                                                                                                   \
    namespace detail_##name##_impl                                                                                                              \
    {                                                                                                                                           \
        template<class A, class T>                                                                                                              \
        inline auto member_##name##(A& ar, T& t) -> decltype(t.##name##(ar))                                                                    \
        {                                                                                                                                       \
            return t.##name##(ar);                                                                                                              \
        }                                                                                                                                       \
    }                                                                                                                                           \
    template <class A, class T>                                                                                                                 \
    class has_member_##name##                                                                                                                   \
    {                                                                                                                                           \
        template <class TT, class AA>                                                                                                           \
        static auto test(int) -> decltype( detail_##name##_impl::member_##name( std::declval<AA&>(), std::declval<TT&>() ), std::true_type{});  \
        template <class, class>                                                                                                                 \
        static auto test(...) -> std::false_type;                                                                                               \
    public:                                                                                                                                     \
        static const bool value = std::is_same<decltype(test<T, A>(0)), std::true_type>::value;                                                 \
    }
