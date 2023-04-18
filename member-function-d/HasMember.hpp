#pragma once

#include <type_traits>

// ref
// https://github.com/USCiLab/cereal/blob/master/include/cereal/details/traits.hpp
// https://github.com/USCiLab/cereal/blob/master/include/cereal/access.hpp


#define UDON_HAS_MEMBER_ACSESS_FUNCTION(name)                                                                     \
	namespace detail\
	{\
		template<class A, class T>\
		inline static auto member_serialize(A& ar, T& t) -> void\
		{\
			t.name(ar);\
		}\
	}\
	template <class T, class A>                                                                                                       \
	class has_member_##name##                                                                                     \
	{                                                                                                                                 \
		template <class TT, class AA>                                                                                                   \
		static auto test(int) -> decltype( detail::member_##name( std::declval<AA&>(), std::declval<TT&>() ), std::true_type()); \
		template <class, class>                                                                                                         \
		static std::false_type test(...);                                                                                                            \
	public: \
		static constexpr bool value = std::is_same<decltype(test<T, A>(0)), std::true_type>::value;                                                    \
	}

UDON_HAS_MEMBER_ACSESS_FUNCTION(accessor);
