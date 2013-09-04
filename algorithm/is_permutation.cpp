/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <sprout/algorithm/is_permutation_new.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>
#include <algorithm>

int count;

struct eq {
	template<typename T, typename U>
	bool operator()(T const& t, U const& u) const { ++count; return t == u; }
};

template<typename C1, typename C2>
void check3(bool expect, C1 c1, C2 c2, int len = 0)
{
	std::cout << std::boolalpha;
	{
		count = 0;
		auto result = sprout::is_permutation(
			sprout::begin(c1),
			len == 0 ? sprout::end(c1) : sprout::begin(c1) + len,
			sprout::begin(c2),
			eq()
			);
		if (expect == result) {
			std::cout << "Count: " << count << std::endl;
		} else {
			std::cout << "Expect: " << expect << ", Result: " << result << ", count: " << count << std::endl;
		}
	}

	{
		count = 0;
		auto result = sprout::is_permutation(
			testspr::reduct_forward(sprout::begin(c1)),
			testspr::reduct_forward(len == 0 ? sprout::end(c1) : sprout::begin(c1) + len),
			testspr::reduct_forward(sprout::begin(c2)),
			eq()
			);
		if (expect == result) {
			std::cout << "Count: " << count << std::endl;
		} else {
			std::cout << "Expect: " << expect << ", Result: " << result << ", count: " << count << std::endl;
		}
	}

	{
		count = 0;
		auto result = sprout::is_permutation(
			testspr::reduct_random_access(sprout::begin(c1)),
			testspr::reduct_random_access(len == 0 ? sprout::end(c1) : sprout::begin(c1) + len),
			testspr::reduct_random_access(sprout::begin(c2)),
			eq()
			);
		if (expect == result) {
			std::cout << "Count: " << count << std::endl;
		} else {
			std::cout << "Expect: " << expect << ", Result: " << result << ", count: " << count << std::endl;
		}
	}

	{
		count = 0;
		auto result = std::is_permutation(
			sprout::begin(c1),
			len == 0 ? sprout::end(c1) : sprout::begin(c1) + len,
			sprout::begin(c2),
			eq()
			);
		if (expect == result) {
			std::cout << "Count: " << count << std::endl;
		} else {
			std::cout << "Expect: " << expect << ", Result: " << result << ", count: " << count << std::endl;
		}
	}
#if 0
	{
		count = 0;
		auto result = std::is_permutation(
			testspr::reduct_forward(sprout::begin(c1)),
			testspr::reduct_forward(len == 0 ? sprout::end(c1) : sprout::begin(c1) + len),
			testspr::reduct_forward(sprout::begin(c2)),
			eq()
			);
		if (expect == result) {
			std::cout << "Count: " << count << std::endl;
		} else {
			std::cout << "Expect: " << expect << ", Result: " << result << ", count: " << count << std::endl;
		}
	}

	{
		count = 0;
		auto result = std::is_permutation(
			testspr::reduct_random_access(sprout::begin(c1)),
			testspr::reduct_random_access(len == 0 ? sprout::end(c1) : sprout::begin(c1) + len),
			testspr::reduct_random_access(sprout::begin(c2)),
			eq()
			);
		if (expect == result) {
			std::cout << "Count: " << count << std::endl;
		} else {
			std::cout << "Expect: " << expect << ", Result: " << result << ", count: " << count << std::endl;
		}
	}
#endif

	std::cout << std::endl;
}

#undef SPROUT_STATIC_CONSTEXPR
#define SPROUT_STATIC_CONSTEXPR
SPROUT_STATIC_CONSTEXPR auto arr1 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
SPROUT_STATIC_CONSTEXPR auto arr2 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 1, 2, 3, 4, 5, 6, 7);
SPROUT_STATIC_CONSTEXPR auto arr3 = sprout::make_common_array(5, 4, 3, 2, 1, 11, 10, 9, 8, 7, 5, 4, 3, 2, 1, 11, 10, 9, 8, 7);
SPROUT_STATIC_CONSTEXPR auto arr4 = sprout::make_common_array(1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10);
SPROUT_STATIC_CONSTEXPR auto arr5 = sprout::make_common_array(10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);

int main()
{
	check3(true, arr1, arr2);
	check3(false, arr1, arr3);
	check3(true, arr1, arr2, 5);
	check3(true, arr1, arr3, 5);
	check3(false, arr1, arr2, 15);
	check3(true, arr4, arr5);

	//count = 0;
	//sprout::mismatch(sprout::begin(arr1), sprout::end(arr1), sprout::begin(arr3), eq());
	//std::cout << "Count: " << count << std::endl;

#if 0
{
	SPROUT_STATIC_CONSTEXPR auto result = sprout::is_permutation(
		sprout::begin(arr1),
		sprout::end(arr1),
		sprout::begin(arr2),
		sprout::end(arr2)
		);
	TESTSPR_BOTH_ASSERT(result);
}
{
	SPROUT_STATIC_CONSTEXPR auto result = sprout::is_permutation(
		sprout::begin(arr1),
		sprout::end(arr1),
		sprout::begin(arr3),
		sprout::end(arr3)
		);
	TESTSPR_BOTH_ASSERT(!result);
}
{
	SPROUT_STATIC_CONSTEXPR auto result = sprout::is_permutation(
		sprout::begin(arr1),
		sprout::begin(arr1) + 5,
		sprout::begin(arr2),
		sprout::end(arr2) + 5
		);
	TESTSPR_BOTH_ASSERT(!result);
}
{
	SPROUT_STATIC_CONSTEXPR auto result = sprout::is_permutation(
		sprout::begin(arr1),
		sprout::begin(arr1) + 5,
		sprout::begin(arr3),
		sprout::begin(arr3) + 5
		);
	TESTSPR_BOTH_ASSERT(result);
}
#endif
}
