/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIND_END_HPP
#define SPROUT_ALGORITHM_FIND_END_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/detail/algorithm/search_one.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		struct find_end_ra {
			SPROUT_CONSTEXPR
			find_end_ra(ForwardIterato2 first2, ForwardIterator2 last2, BinaryPredicate pred, RandomAccessIterator1 last1_)
				: first2(first2), last2(last2), pred(pred), last1_(last1_) {}

			ForwardIterator2 first2;
			ForwardIterator2 last2;
			BinaryPredicate pred;
			RandomAccessIterator1 last1_;
			typedef typename std::iterator_traits<RandomAccessIterator1>::difference_type difference_type;

			SPROUT_CONSTEXPR RandomAccessIterator1
			check_ra(RandomAccessIterator1 first1, RandomAccessIterator1 result, RandomAccessIterator1 searched) {
				return searched == first1 ? searched : result;
			}

			SPROUT_CONSTEXPR RandomAccessIterator1
			search_one(RandomAccessIterator1 first1) {
				return sprout::detail::search_one(first1, last1_, first2, last2, pred);
			}

			SPROUT_CONSTEXPR RandomAccessIterator1
			find_end(RandomAccessIterator1 first1, RandomAccessIterator1 last1, difference_type pivot,
				RandomAccessIterator1 result, RandomAccessIterator1 searched) {
				return
					searched == last1_ ?
						result :
					searched <  first1 ?
						pivot == 0 ?
							check_ra(first1, searched, search_one(first1)) :
							find_end(sprout::next(first1, pivot), last1, (sprout::distance(first1, last1) - pivot) / 2, searched,
							find_end(first1, sprout::next(first1, pivot), pivot / 2, searched, first1)) :
					pivot == 0 ?
						search_one(first1) :
						find_end(sprout::next(first1, pivot), last1, (sprout::distance(first1, last1) - pivot) / 2, result,
						find_end(first1, sprout::next(first1, pivot), pivot / 2, result, first1))
					;
			}
		}

		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value,
			RandomAccessIterator1
		>::type
		find_end(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? last1
				: sprout::detail::find_end_ra(first2, last2, pred, last1).find_end(
					first1, last1,
					sprout::distance(first1, last1) / 2, last1,
					first1
					)
				;
		}

		template<typename ForwardIterator1>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl_check(sprout::pair<ForwardIterator1, ForwardIterator1> const& current, ForwardIterator1 last1, ForwardIterator1 searched) {
			typedef sprout::pair<ForwardIterator1, ForwardIterator1> type;
			return searched == current.first ? type(sprout::next(current.first), searched)
				: searched == last1 ? type(last1, current.second)
				: type(sprout::next(current.first), current.second)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl_1(
			sprout::pair<ForwardIterator1, ForwardIterator1> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return current.first == last1 ? current
				: n == 1 ? sprout::detail::find_end_impl_check(
					current, last1,
					sprout::detail::search_one(current.first, last1, first2, last2, pred)
					)
				: sprout::detail::find_end_impl_1(
					sprout::detail::find_end_impl_1(
						current,
						last1, first2, last2, pred, n / 2
						),
					last1, first2, last2, pred, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, ForwardIterator1>
		find_end_impl(
			sprout::pair<ForwardIterator1, ForwardIterator1> const& current,
			ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return current.first == last1 ? current
				: sprout::detail::find_end_impl(
					sprout::detail::find_end_impl_1(
						current,
						last1, first2, last2, pred, n
						),
					last1, first2, last2, pred, n * 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR ForwardIterator1
		find_end(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::forward_iterator_tag*
			)
		{
			typedef sprout::pair<ForwardIterator1, ForwardIterator1> type;
			return sprout::detail::find_end_impl(type(first1, last1), last1, first2, last2, pred, 1).second;
		}
	}	// namespace detail

	// 25.2.6 Find end
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator1
	find_end(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred
		)
	{
		typedef typename std::iterator_traits<ForwardIterator1>::iterator_category* category;
		return sprout::detail::find_end(first1, last1, first2, last2, pred, category());
	}

	template<typename ForwardIterator1, typename ForwardIterator2>
	inline SPROUT_CONSTEXPR ForwardIterator1
	find_end(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return sprout::find_end(first1, last1, first2, last2, sprout::equal_to<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_END_HPP
