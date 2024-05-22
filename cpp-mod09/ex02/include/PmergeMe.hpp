// incluir header 42

#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

class PmergeMe {
	public:
		PmergeMe(std::vector<int> &input, int size);
		PmergeMe(PmergeMe const &src);
		~PmergeMe();

		PmergeMe &	operator=(PmergeMe const &other);
	private:
		std::vector<int> _vector;
		std::deque<int>	 _deque;
		const int		 _size;

		void _vectorSort();
		void _dequeSort();

		// Ford-Johnson Aux functions
		void fordJohnsonSortVector(std::vector<int>&arr);
		void fordJohnsonSortDeque(std::deque<int>&arr);
		void insertSortedVector(std::vector<int>&arr, int value);
		void insertSortedDeque(std::deque<int>&arr, int value);
};

#endif