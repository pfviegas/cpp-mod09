// incluir header 42

#include "../include/BitcoinExchange.hpp"

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

std::string trim(const std::string &str)
{
	size_t first = str.find_first_not_of(' ');
	
	if (std::string::npos == first)
		return (str);
	
	size_t last = str.find_last_not_of(' ');
	return (str.substr(first, (last - first + 1)));
}