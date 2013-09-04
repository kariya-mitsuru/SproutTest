#include <sprout/algorithm/binary_search.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>

SPROUT_STATIC_CONSTEXPR auto input1 = sprout::make_common_array(2, 3, 5, 5, 5, 5, 6, 7, 8, 9, 10);
SPROUT_STATIC_CONSTEXPR auto result1_1 = sprout::binary_search(sprout::begin(input1), sprout::end(input1), 5);
static_assert(result1_1, "found 5 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result1_2 = sprout::binary_search(sprout::begin(input1), sprout::end(input1), 4);
static_assert(!result1_2, "not found 4 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result1_3 = sprout::binary_search(sprout::begin(input1), sprout::end(input1), 8);
static_assert(result1_3, "found 8 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result1_4 = sprout::binary_search(sprout::begin(input1), sprout::end(input1), 2);
static_assert(result1_4, "found 1 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result1_5 = sprout::binary_search(sprout::begin(input1), sprout::end(input1), 1);
static_assert(!result1_5, "not found 0 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result1_6 = sprout::binary_search(sprout::begin(input1), sprout::end(input1), 10);
static_assert(result1_6, "found 10 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result1_7 = sprout::binary_search(sprout::begin(input1), sprout::end(input1), 11);
static_assert(!result1_7, "not found 11 by binary search.");

SPROUT_STATIC_CONSTEXPR auto input2 = sprout::make_common_array(10, 9, 8, 7, 6, 5, 5, 5, 5, 3, 2);
SPROUT_STATIC_CONSTEXPR auto result2_1 = sprout::binary_search(sprout::begin(input2), sprout::end(input2), 5, sprout::greater<>());
static_assert(result2_1, "found 5 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result2_2 = sprout::binary_search(sprout::begin(input2), sprout::end(input2), 4, sprout::greater<>());
static_assert(!result2_2, "not found 4 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result2_3 = sprout::binary_search(sprout::begin(input2), sprout::end(input2), 8, sprout::greater<>());
static_assert(result2_3, "found 8 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result2_4 = sprout::binary_search(sprout::begin(input2), sprout::end(input2), 2, sprout::greater<>());
static_assert(result2_4, "found 2 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result2_5 = sprout::binary_search(sprout::begin(input2), sprout::end(input2), 1, sprout::greater<>());
static_assert(!result2_5, "not found 1 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result2_6 = sprout::binary_search(sprout::begin(input2), sprout::end(input2), 10, sprout::greater<>());
static_assert(result2_6, "found 10 by binary search.");
SPROUT_STATIC_CONSTEXPR auto result2_7 = sprout::binary_search(sprout::begin(input2), sprout::end(input2), 11, sprout::greater<>());
static_assert(!result2_7, "not found 11 by binary search.");
