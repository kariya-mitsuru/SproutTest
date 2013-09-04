/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <sprout/algorithm/is_permutation.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>
#include <algorithm>
#include <sprout/iterator.hpp>
#include <vector>

template<typename Iterator>
using identity = Iterator;
template<typename Iterator>
using input = testspr::reduct_iterator<Iterator, std::input_iterator_tag>;
template<typename Iterator>
using forward = testspr::reduct_iterator<Iterator, std::forward_iterator_tag>;
template<typename Iterator>
using bidirectional = testspr::reduct_iterator<Iterator, std::bidirectional_iterator_tag>;
template<typename Iterator>
using random_access = testspr::reduct_iterator<Iterator, std::random_access_iterator_tag>;


struct eq {
	eq(int& count) : count(count) {}
	template<typename T, typename U>
	bool operator()(T const& t, U const& u) const { ++count; return t == u; }
	int& count;
};

template<
	template<typename> class Reducer, typename C1, typename C2, typename BinaryPredicate = eq,
	typename ForwardIterator1 = Reducer<typename C1::iterator>,
	typename ForwardIterator2 = Reducer<typename C2::iterator>
	>
inline void check_reduced(bool (*is_permutation)(ForwardIterator1, ForwardIterator1, ForwardIterator2, BinaryPredicate), bool expect, C1 c1, C2 c2, int len)
{
	int count = 0;
	eq pred(count);
	auto result = is_permutation(
		Reducer<typename C1::iterator>(sprout::begin(c1)),
		Reducer<typename C1::iterator>(len == 0 ? sprout::end(c1) : sprout::begin(c1) + len),
		Reducer<typename C2::iterator>(sprout::begin(c2)),
		pred
		);
	if (expect == result) {
		std::cout << "Count: " << pred.count << std::endl;
	} else {
		std::cout << "Expect: " << expect << ", Result: " << result << ", count: " << pred.count << std::endl;
	}
}

template<typename C1, typename C2>
inline void check3(bool expect, C1 c1, C2 c2, int len = 0)
{
	std::cout << std::boolalpha;

	check_reduced<identity>(sprout::is_permutation, expect, c1, c2, len);
	check_reduced<forward>(sprout::is_permutation, expect, c1, c2, len);
	check_reduced<random_access>(sprout::is_permutation, expect, c1, c2, len);
	check_reduced<identity>(std::is_permutation, expect, c1, c2, len);
	check_reduced<forward>(std::is_permutation, expect, c1, c2, len);
	check_reduced<random_access>(std::is_permutation, expect, c1, c2, len);

	std::cout << std::endl;
}

SPROUT_STATIC_CONSTEXPR auto arr1 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
SPROUT_STATIC_CONSTEXPR auto arr2 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 1, 2, 3, 4, 5, 6, 7);
SPROUT_STATIC_CONSTEXPR auto arr3 = sprout::make_common_array(5, 4, 3, 2, 1, 11, 10, 9, 8, 7, 5, 4, 3, 2, 1, 11, 10, 9, 8, 7);
SPROUT_STATIC_CONSTEXPR auto arr4 = sprout::make_common_array(1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10);
SPROUT_STATIC_CONSTEXPR auto arr5 = sprout::make_common_array(10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);

int main()
{
	check3(true, std::vector<int>({1, 2, 3, 4, 5}), std::vector<int>({1, 2, 3, 4, 5}));
	check3(true, arr1, arr2);
	check3(false, arr1, arr3);
	check3(true, arr1, arr2, 5);
	check3(true, arr1, arr3, 5);
	check3(false, arr1, arr2, 15);
	check3(true, arr4, arr5);
}
