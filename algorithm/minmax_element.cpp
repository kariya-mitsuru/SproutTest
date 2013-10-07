#include <iostream>

#include <sprout/array.hpp>
#include <sprout/algorithm.hpp>

#include <testspr/iterator.hpp>

static constexpr auto a = sprout::make_common_array(1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 0);//, 8, 8, 9, 9, 10, 10, 0);
static constexpr auto d1 = sprout::minmax_element(a.begin(), a.end());
static constexpr auto d2 = sprout::minmax_element(testspr::reduct_forward(a.begin()), testspr::reduct_forward(a.end()));

static constexpr auto rb = a.begin();
static constexpr auto re = a.end();

static constexpr auto fb = testspr::reduct_forward(rb);
static constexpr auto fe = testspr::reduct_forward(re);

struct less {
	less(int& n) : n(n) {}
	bool operator()(int a, int b) const { ++n; return a < b; }

	int& n;
};

int main()
{
	int count = 0;
	auto fr = sprout::minmax_element(fb, fe, less(count));
	std::cout << fr.first - fb << ", " << fr.second - fb << ", " << count << std::endl;
	count = 0;
	auto rr = sprout::minmax_element(rb, re, less(count));
	std::cout << rr.first - rb << ", " << rr.second - rb << ", " << count << std::endl;
}
