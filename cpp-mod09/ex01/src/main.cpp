// incluir header 42

#include "../include/BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	std::ifstream	file;
	BitcoinExchange *btcValue = NULL;
	
	try
	{
		checkFile(file, argc, argv);
		btcValue = new BitcoinExchange(file, argv);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	delete btcValue;
	return (0);
}