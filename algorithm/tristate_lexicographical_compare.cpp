#include <iostream>

#include <sprout/array.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>

#include <testspr/iterator.hpp>

#include "utility.hpp"

template<template<typename> class Reducer, typename C1, typename C2>
void check_reduced(C1 c1, C2 c2, int expect)
{
	int count = 0;
	auto result = sprout::tristate_lexicographical_compare(
		Reducer<typename C1::iterator>(sprout::begin(c1)),
		Reducer<typename C1::iterator>(sprout::end(c1)),
		Reducer<typename C2::iterator>(sprout::begin(c2)),
		Reducer<typename C2::iterator>(sprout::end(c2)),
		less(count)
		);
	print(expect, result, count);
}

template<template<typename> class Reducer, typename C1, typename T1, typename C2, typename T2>
void check_reduced(C1 c1, T1 const& delim1, C2 c2, T2 const& delim2, int expect)
{
	int count = 0;
	auto result = sprout::tristate_lexicographical_compare(
		Reducer<typename C1::iterator>(sprout::begin(c1)),
		Reducer<typename C1::iterator>(sprout::end(c1)),
		delim1,
		Reducer<typename C2::iterator>(sprout::begin(c2)),
		Reducer<typename C2::iterator>(sprout::end(c2)),
		delim2,
		less(count)
		);
	print(expect, result, count);
}

template<typename C1, typename C2>
inline void check(C1 c1, C2 c2, int expect)
{
	check_reduced<identity>(c1, c2, expect);
	check_reduced<forward>(c1, c2, expect);
	check_reduced<random_access>(c1, c2, expect);

	std::cout << std::endl;
}

template<typename C1, typename T1, typename C2, typename T2>
inline void check(C1 c1, T1 const& delim1, C2 c2, T2 const& delim2, int expect)
{
	check_reduced<identity>(c1, delim1, c2, delim2, expect);
	check_reduced<forward>(c1, delim1, c2, delim2, expect);
	check_reduced<random_access>(c1, delim1, c2, delim2, expect);

	std::cout << std::endl;
}

SPROUT_STATIC_CONSTEXPR auto input1 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
SPROUT_STATIC_CONSTEXPR auto input2 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 11, 12, 13);
SPROUT_STATIC_CONSTEXPR auto input3 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7);

int main()
{
	check(input1, input1, 0);
	check(input1, input2, -1);
	check(input2, input1, 1);
	check(input1, input3, 1);
	check(input3, input1, -1);
	check(input2, input3, 1);
	check(input3, input2, -1);
	std::cout << std::endl;
	check(input1, 0, input1, 0, 0);
	check(input1, 0, input2, 0, -1);
	check(input2, 0, input1, 0, 1);
	check(input1, 0, input3, 0, 1);
	check(input3, 0, input1, 0, -1);
	check(input2, 0, input3, 0, 1);
	check(input3, 0, input2, 0, -1);
	std::cout << std::endl;
	check(input1, 8, input2, 11, 0);
	check(input1, 7, input3, 7, 0);
}
