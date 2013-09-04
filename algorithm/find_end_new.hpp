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

//#undef SPROUT_CONSTEXPR
//#define SPROUT_CONSTEXPR
//#include <iostream>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator1>
		inline SPROUT_CONSTEXPR RandomAccessIterator1
		find_end_impl_check_ra(RandomAccessIterator1 first1, RandomAccessIterator1 result, RandomAccessIterator1 searched) {
			return searched == first1 ? searched : result;
		}

		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		class find_end_impl_ra {
		public:
			SPROUT_CONSTEXPR
			find_end_impl_ra(RandomAccessIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
				: last1_(last1), first2(first2), last2(last2), pred(pred) {}

			SPROUT_CONSTEXPR RandomAccessIterator1
			search(RandomAccessIterator1 first1) const {
				return search(first1, sprout::distance(first1, last1_), sprout::distance(first2, last2));
			}

		private:
			typedef typename std::iterator_traits<RandomAccessIterator1>::difference_type difference_type1;
			typedef typename std::iterator_traits<ForwardIterator2>::difference_type difference_type2;

			SPROUT_CONSTEXPR RandomAccessIterator1
			search(RandomAccessIterator1 first, difference_type1 len1, difference_type2 len2) const {
				return len1 < len2 ? last1_ : search(first, last1_ - len2 + 1, len1 - len2 + 1, last1_);
			}

			SPROUT_CONSTEXPR RandomAccessIterator1
			search(RandomAccessIterator1 first1, RandomAccessIterator1 last1, difference_type1 len,
					RandomAccessIterator1 result) const {
				return result != last1_ ? result
						: len == 1
						? sprout::detail::find_end_impl_check_ra(first1, result, sprout::detail::search_one(first1, last1_, first2, last2, pred))
						:	search(first1, sprout::next(first1, len / 2), len / 2,
							search(sprout::next(first1, len / 2), last1 , len - len / 2,
								result));
			}

			RandomAccessIterator1 last1_;
			ForwardIterator2 first2;
			ForwardIterator2 last2;
			BinaryPredicate pred;
		};

		template<typename RandomAccessIterator1, typename ForwardIterator2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator1>::value,
			RandomAccessIterator1
		>::type
		find_end(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred,
			std::random_access_iterator_tag*)
		{
			return first1 == last1 || first2 == last2 ? last1
				: sprout::detail::find_end_impl_ra<RandomAccessIterator1, ForwardIterator2, BinaryPredicate>(
					last1, first2, last2, pred
					).search(first1)
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
