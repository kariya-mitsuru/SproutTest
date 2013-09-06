/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <sprout/algorithm/search_n.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>
#include <algorithm>
#include <sprout/iterator.hpp>

#include "utility.hpp"

template<template<typename> class Reducer, typename C, typename Size, typename T>
//inline void check_reduced(Reducer<typename C::iterator> (*search_n)(Reducer<typename C::iterator>, Reducer<typename C::iterator>, Size, T, equal_to), typename C::difference_type expect, C c, Size size, T const& value, int len)
inline void check_reduced(typename C::difference_type expect, C c, Size size, T const& value, int len)
{
	int count = 0;
	auto result = sprout::search_n(
		Reducer<typename C::iterator>(sprout::begin(c)),
		Reducer<typename C::iterator>(len == 0 ? sprout::end(c) : sprout::begin(c) + len),
		size,
		value,
		equal_to(count)
		);
	print(expect, sprout::distance(Reducer<typename C::iterator>(sprout::begin(c)), result), count);
}

template<template<typename> class Reducer, typename C, typename Size, typename T>
//inline void check_reduced(Reducer<typename C::iterator> (*search_n)(Reducer<typename C::iterator>, Reducer<typename C::iterator>, Size, T, equal_to), typename C::difference_type expect, C c, Size size, T const& value, int len)
inline void check_reduced_std(typename C::difference_type expect, C c, Size size, T const& value, int len)
{
	int count = 0;
	auto result = std::search_n(
		Reducer<typename C::iterator>(sprout::begin(c)),
		Reducer<typename C::iterator>(len == 0 ? sprout::end(c) : sprout::begin(c) + len),
		size,
		value,
		equal_to(count)
		);
	print(expect, sprout::distance(Reducer<typename C::iterator>(sprout::begin(c)), result), count);
}

template<typename C, typename T, typename Size>
inline void check(typename C::difference_type expect, C c, Size size, T const& value, int len = 0)
{
	std::cout << std::boolalpha;

	check_reduced<identity>(expect, c, size, value, len);
	check_reduced<forward>(expect, c, size, value, len);
	check_reduced<random_access>(expect, c, size, value, len);
	//check_reduced<identity, C, Size, T>(sprout::search_n, expect, c, size, value, len);
	//check_reduced<forward, C, Size, T>(sprout::search_n, expect, c, size, value, len);
	//check_reduced<random_access, C, Size, T>(sprout::search_n, expect, c, size, value, len);
	check_reduced_std<identity>(expect, c, size, value, len);
	check_reduced_std<forward>(expect, c, size, value, len);
	check_reduced_std<random_access>(expect, c, size, value, len);
	//check_reduced<identity, C, Size, T>(std::search_n, expect, c, size, value, len);
	//check_reduced<forward, C, Size, T>(std::search_n, expect, c, size, value, len);
	//check_reduced<random_access, C, Size, T>(std::search_n, expect, c, size, value, len);

	std::cout << std::endl;
}

SPROUT_STATIC_CONSTEXPR auto arr1 = sprout::make_common_array(1, 2, 1, 4, 1, 6, 1, 8, 1, 10, 1, 2, 1, 4, 1, 6, 1, 8, 1, 10);
SPROUT_STATIC_CONSTEXPR auto arr2 = sprout::make_common_array(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1);

int main()
{
	check(20, arr1, 2, 1);
	check(20, arr2, 11, 1);
}
