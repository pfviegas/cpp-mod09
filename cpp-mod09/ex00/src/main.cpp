// incluir header 42

#include "../include/BitcoinExchange.hpp"

/**
 * Checks the file for errors and throws exceptions if any errors are encountered.
 * 
 * @param file The input file stream to check.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @throws std::runtime_error If the number of arguments is incorrect or if the file cannot be opened.
 * @throws std::runtime_error If an empty line is found in the file.
 */
void checkFile(std::ifstream &file, int argc, char **argv)
{
	std::string		line;
	std::ifstream	lineTest;

	if (argc != 2)
		throw std::runtime_error("Error: Wrong arguments number.\nUsage: ./btc data.csv");
	
	file.open(argv[1], std::ifstream::in);
	if (!file.is_open())
		throw std::runtime_error("Error: Couldn't open file: " + static_cast<std::string>(argv[1]));
	
	lineTest.open(argv[1], std::ifstream::in);
	while (getline(lineTest, line))
		if (line.empty())
			throw std::runtime_error("Error: Empty line.");
}

/**
 * @brief Trims leading and trailing spaces from a string.
 * 
 * @param str The string to trim.
 * @return The trimmed string.
 */
std::string trim(const std::string &str)
{
	size_t first = str.find_first_not_of(' ');
	
	if (std::string::npos == first)
		return (str);
	
	size_t last = str.find_last_not_of(' ');
	return (str.substr(first, (last - first + 1)));
}

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