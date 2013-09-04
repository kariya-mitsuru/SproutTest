#include <iostream>

#include <sprout/array.hpp>
#include <sprout/algorithm/lexicographical_compare.hpp>

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
void check(C1 const& c1, C2 const& c2, bool expect)
{
	std::cout << std::boolalpha;
	{
		auto comp = less<int>();
		auto result = sprout::lexicographical_compare(sprout::begin(c1), sprout::end(c1), sprout::begin(c2), sprout::end(c2), comp);
		if (expect == result) {
			std::cout << "Success: " << result << ", count = " << less<int>::count << std::endl;
		} else {
			std::cout << "Failure: " << " exptected: " << expect << ", result: " << result << ", count = " << less<int>::count << std::endl;
		}
	}
	{
		auto comp = less<int>();
		auto result = sprout::lexicographical_compare(testspr::reduct_input(sprout::begin(c1)), testspr::reduct_input(sprout::end(c1)), testspr::reduct_input(sprout::begin(c2)), testspr::reduct_input(sprout::end(c2)), comp);
		if (expect == result) {
			std::cout << "Success: " << result << ", count = " << less<int>::count << std::endl;
		} else {
			std::cout << "Failure: " << " exptected: " << expect << ", result: " << result << ", count = " << less<int>::count << std::endl;
		}
	}
}

int main()
{
    check(input1, input1, false);
    check(input1, input2, true);
    check(input2, input1, false);
    check(input1, input3, false);
    check(input3, input1, true);
    check(input2, input3, false);
    check(input3, input2, true);
}
