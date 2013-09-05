#ifndef SPROUTTEST_UTILITY_HPP
#define SPROUTTEST_UTILITY_HPP

#pragma once

#include <iostream>

#include <testspr/iterator.hpp>

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

struct equal_to {
	equal_to(int& count) : count(count) {}
	template<typename T, typename U>
	bool operator()(T const& t, U const& u) const { ++count; return t == u; }
	int& count;
};

struct less {
	less(int& count) : count(count) {}
	template<typename T, typename U>
	bool operator()(T const& t, U const& u) const { ++count; return t < u; }
	int& count;
};

template<typename T>
inline void print(T expect, T result, int count)
{
	if (expect == result) {
		std::cout << "Success:";
	} else {
		std::cout << "Failure: " << " exptected = " << expect << ",";
	}
	std::cout << " result = " << result << ", count = " << count << std::endl;
}

#endif
