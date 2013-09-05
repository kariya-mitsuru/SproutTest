#include <sprout/array.hpp>
#include <testspr/tools.hpp>

SPROUT_STATIC_CONSTEXPR auto arr = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
SPROUT_STATIC_CONSTEXPR auto arr2 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 1, 2, 3, 4, 5, 6, 7);
SPROUT_STATIC_CONSTEXPR auto arr3 = sprout::make_common_array(5, 4, 3, 2, 1, 11, 10, 9, 8, 7, 5, 4, 3, 2, 1, 11, 10, 9, 8, 7);
SPROUT_STATIC_CONSTEXPR auto arr4 = sprout::make_common_array(1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10);
SPROUT_STATIC_CONSTEXPR auto arr5 = sprout::make_common_array(10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);

int main()
{
	auto b = testspr::reduct_random_access(sprout::begin(arr));
	auto e = testspr::reduct_random_access(sprout::end(arr));
	testspr::swap(b, e);
}
