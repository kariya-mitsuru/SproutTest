#include <iostream>

#include <sprout/array.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>

#include <testspr/iterator.hpp>

SPROUT_STATIC_CONSTEXPR auto input1 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
SPROUT_STATIC_CONSTEXPR auto input2 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 11, 12, 13);
SPROUT_STATIC_CONSTEXPR auto input3 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7);

template<typename T>
struct less {
	static int count;
	less() { count = 0; }
	bool operator()(T const& t1, T const& t2) const {
		++count;
		return t1 < t2;
	}
};

template<>
int less<int>::count = 0;

template<typename C1, typename C2>
void check(C1 const& c1, C2 const& c2, int expect)
{
	{
		auto comp = less<int>();
		auto result = sprout::tristate_lexicographical_compare(sprout::begin(c1), sprout::end(c1), sprout::begin(c2), sprout::end(c2), comp);
		if (expect == result) {
			std::cout << "Success: " << result << ", count = " << less<int>::count << std::endl;
		} else {
			std::cout << "Failure: " << " exptected: " << expect << ", result: " << result << ", count = " << less<int>::count << std::endl;
		}
	}
	{
		auto comp = less<int>();
		auto result = sprout::tristate_lexicographical_compare(testspr::reduct_input(sprout::begin(c1)), testspr::reduct_input(sprout::end(c1)), testspr::reduct_input(sprout::begin(c2)), testspr::reduct_input(sprout::end(c2)), comp);
		if (expect == result) {
			std::cout << "Success: " << result << ", count = " << less<int>::count << std::endl;
		} else {
			std::cout << "Failure: " << " exptected: " << expect << ", result: " << result << ", count = " << less<int>::count << std::endl;
		}
	}
}

template<typename C1, typename T1, typename C2, typename T2>
void check(C1 const& c1, T1 const& delim1, C2 const& c2, T2 const& delim2, int expect)
{
	{
		auto comp = less<int>();
		auto result = sprout::tristate_lexicographical_compare(sprout::begin(c1), sprout::end(c1), delim1, sprout::begin(c2), sprout::end(c2), delim2, comp);
		if (expect == result) {
			std::cout << "Success: " << result << ", count = " << less<int>::count << std::endl;
		} else {
			std::cout << "Failure: " << " exptected: " << expect << ", result: " << result << ", count = " << less<int>::count << std::endl;
		}
	}
	{
		auto comp = less<int>();
		auto result = sprout::tristate_lexicographical_compare(testspr::reduct_input(sprout::begin(c1)), testspr::reduct_input(sprout::end(c1)), delim1, testspr::reduct_input(sprout::begin(c2)), testspr::reduct_input(sprout::end(c2)), delim2, comp);
		if (expect == result) {
			std::cout << "Success: " << result << ", count = " << less<int>::count << std::endl;
		} else {
			std::cout << "Failure: " << " exptected: " << expect << ", result: " << result << ", count = " << less<int>::count << std::endl;
		}
	}
}

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
