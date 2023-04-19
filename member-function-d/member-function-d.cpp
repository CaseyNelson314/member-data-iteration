//////////////////////////////////////////////////////////////
// 
//	Iterate member variables.
// 
//  Copyright (c) 2023 CaseyNelson314sd
// 
//	Licensed under the MIT License.
//
//////////////////////////////////////////////////////////////

#include <iostream>

#include "HasMember.hpp"


UDON_HAS_MEMBER_ACSESS_FUNCTION(accessor); // has_member_accessor<A, T>


// SFINAE を使用して T がスカラ型になるまで再帰的に呼び出す。
// そのためT型がスカラ型でないメンバ変数を持っていたとしても、accessor メンバ関数を持つ型であれば呼び出しが可能である。
// T 型に accessor メンバ関数が定義されておらず、スカラでない場合にはコンパイルエラーとなる。

struct MemberIteratePrinter
{

	std::ostream& ostream;

	/// @brief
	/// @tparam T 整数型
	/// @param rhs 
	/// @return 
	template<typename T>
	auto operator()(const T& rhs) -> std::enable_if_t<std::is_integral_v<T>>
	{
		ostream << "integer: " << rhs << std::endl;
	}

	/// @brief 
	/// @tparam T 浮動小数点型
	/// @param rhs 
	/// @return 
	template<typename T>
	auto operator()(const T& rhs) -> std::enable_if_t<std::is_floating_point_v<T>>
	{
		ostream << "floating point: " << rhs << std::endl;
	}

	/// @brief
	/// @tparam T 配列
	/// @param rhs 
	/// @return 
	template<typename T>
	auto operator()(const T& rhs) -> std::enable_if_t<std::is_array_v<T>>
	{
		for (auto&& it : rhs)
		{
			operator()(it);
		}
	}

	/// @brief
	/// @tparam T メンバにaccessorを持つ型
	/// @param rhs 
	/// @return 
	template<typename T>
	auto operator()(const T& rhs) -> std::enable_if_t<has_member_accessor<MemberIteratePrinter, T>::value>
	{
		// T::accessor が const なメンバ関数でない場合に const rhs から呼び出せないため、const_cast によって const を除去
		const_cast<T&>(rhs).accessor(*this);
	}
		
	/// @brief 可変長テンプレート引数再帰展開
	/// @tparam Head 
	/// @tparam ...Tails 
	/// @param head 
	/// @param ...tails 
	template<typename Head, typename... Tails>
	void operator()(const Head& head, const Tails&... tails)
	{
		operator()(head);
		operator()(tails...);
	}

};


struct Floatpoint
{

	double value;

	template<typename T>
	void accessor(T& acc)
	{
		acc(value);
	}

};

struct Vec2
{

	Floatpoint x;
	Floatpoint y;

	template<typename T>
	void accessor(T& acc)
	{
		acc(x, y);
	}

};

int main()
{
	{
		// 二次元ベクトル型走査
		Vec2 vec = { 100, 200 };
		MemberIteratePrinter{ std::cout }(vec);
	}

	{
		// 配列走査
		Floatpoint array[3][3]
		{
			{ 1, 2, 3 },
			{ 4, 5, 6 },
			{ 7, 8, 9 },
		};
		MemberIteratePrinter{ std::cout }(array);
	}

}
