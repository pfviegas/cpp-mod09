// incluir header 42

#include "../include/PmergeMe.hpp"

// Parametrized Constructor
PmergeMe::PmergeMe(std::vector<int> & input, int size) : _vector(input), _deque(input.begin(), input.end()), _size(size)
{
	this->_vectorSort();
	this->_dequeSort();
}

// Copy Constructor
PmergeMe::PmergeMe(PmergeMe const &src) : _size(src._size)
{
	this->_vector = src._vector;
	this->_deque = src._deque;
	*this = src;
}

// Destructor
PmergeMe::~PmergeMe() {}

// Copy assignment operator
PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
	if (this != &other)
	{
		this->_vector = other._vector;
		this->_deque = other._deque;
	}
	return (*this);
}

// Member function
void PmergeMe::_vectorSort()
{
	clock_t start = clock();
	fordJohnsonSortVector(this->_vector);
	clock_t end = clock();

	std::cout << "  Sorted: ";
	for (size_t i = 0; i < this->_vector.size(); i++)
		std::cout << " " << this->_vector[i];
	
	std::cout << std::endl;

	double duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << this->_size << " elements with std::vector<int> : " << duration << " us" << std::endl;
}

void PmergeMe::_dequeSort()
{
	clock_t start = clock();
	fordJohnsonSortDeque(this->_deque);
	clock_t end = clock();

	double duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << this->_size << " elements with std::deque<int>  : " << duration << " us" << std::endl;
}

/**
 * Sorts the elements in the given vector using the Ford-Johnson sorting algorithm.
 * The sorting is done in ascending order.
 *
 * @param arr The vector of integers to be sorted.
 */
void PmergeMe::fordJohnsonSortVector(std::vector<int>&arr)
{
	if (arr.size() <= 1)
		return;

	std::vector<int> lesser, greater;
	for (size_t i = 0; i < arr.size() - 1; i += 2)
	{
		if (arr[i] < arr[i + 1])
		{
			lesser.push_back(arr[i]);
			greater.push_back(arr[i + 1]);
		}
		else
		{
			lesser.push_back(arr[i + 1]);
			greater.push_back(arr[i]);
		}
	}

	if (arr.size() % 2 != 0)
		lesser.push_back(arr.back());

	fordJohnsonSortVector(lesser);

	for (size_t i = 0; i < greater.size(); ++i)
		insertSortedVector(lesser, greater[i]);

	arr = lesser;
}

/**
 * Inserts a value into a sorted vector in a way that maintains the sorted order.
 *
 * @param arr The sorted vector to insert the value into.
 * @param value The value to be inserted.
 */
void PmergeMe::insertSortedVector(std::vector<int>&arr, int value)
{
	std::vector<int>::iterator it = std::upper_bound(arr.begin(), arr.end(), value);
	arr.insert(it, value);
}

/**
 * Sorts a deque of integers using the Ford-Johnson sorting algorithm.
 *
 * The Ford-Johnson sorting algorithm is a recursive sorting algorithm that works by dividing the deque into two halves,
 * sorting each half recursively, and then merging the two sorted halves together.
 *
 * @param arr The deque of integers to be sorted.
 */
void PmergeMe::fordJohnsonSortDeque(std::deque<int>&arr)
{
	if (arr.size() <= 1)
		return;

	std::deque<int> lesser, greater;
	for (size_t i = 0; i < arr.size() - 1; i += 2)
	{
		if (arr[i] < arr[i + 1])
		{
			lesser.push_back(arr[i]);
			greater.push_back(arr[i + 1]);
		}
		else
		{
			lesser.push_back(arr[i + 1]);
			greater.push_back(arr[i]);
		}
	}

	if (arr.size() % 2 != 0)
		lesser.push_back(arr.back());

	fordJohnsonSortDeque(lesser);

	for (size_t i = 0; i < greater.size(); ++i)
		insertSortedDeque(lesser, greater[i]);

	arr = lesser;
}

/**
 * Inserts a value into a sorted deque in a sorted manner.
 *
 * This function takes a sorted deque `arr` and inserts the given `value` into it
 * while maintaining the sorted order of the deque. The insertion is done using
 * the `std::upper_bound` algorithm to find the correct position for the value.
 *
 * @param arr The sorted deque to insert the value into.
 * @param value The value to be inserted into the deque.
 */
void PmergeMe::insertSortedDeque(std::deque<int>&arr, int value)
{
	std::deque<int>::iterator it = std::upper_bound(arr.begin(), arr.end(), value);
	arr.insert(it, value);
}
