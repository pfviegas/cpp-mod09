// incluir header 42

#include "../include/PmergeMe.hpp"
#include <cstdlib>

int	main(int argc, char **argv)
{
	if (argc < 3)
		return std::cout << "Error:\nUsage: ./sort [at least 2 int sequence]" << std::endl, 1;
	
	std::vector<int>	input;
	int					number;
	int					i;
	
	for (i = 1; i < argc; i++)
	{
		for (int j = 0; argv[i][j] != '\0'; j++)
			if (!isdigit(argv[i][j]))
				return std::cout << "Error" << std::endl, 1;

		number = atoi(argv[i]);
		input.push_back(number);
	}

	std::vector<int>::iterator	it;
	std::vector<int>::iterator	ite = input.end();

	std::cout << "Original: ";
	for (it = input.begin(); it != ite; it++)
		std::cout << " " << *it;
	std::cout << std::endl;
	
	PmergeMe	obj(input, i - 1);

	return (0);
}