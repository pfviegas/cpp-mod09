// incluir header 42

#ifndef _BITCOINEXCHANGE_HPP_
#define _BITCOINEXCHANGE_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <cstdlib>


/**
 * @brief Converts a numeric value to a string.
 * 
 * Takes a numeric value and converts it to a string using the std::ostringstream class.
 * The converted string is then returned.
 * 
 * @tparam		T The type of the numeric value.
 * @param value	The numeric value to be converted.
 * @return		std::string The converted string.
 */
template <typename T>
std::string toString(const T &value)
{
	std::ostringstream oss;
	
	oss << value;
	return (oss.str());
}

void checkFile(std::ifstream &file, int argc, char **argv);

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(std::ifstream &file, char **argv);
		BitcoinExchange(BitcoinExchange const &other);
		~BitcoinExchange();

		BitcoinExchange &operator=(BitcoinExchange const &other);

		void	printContainer() const;

	private:
		std::map<std::string, float>	_map;
		int		_inputSize;
		int*	_input;
		std::string const	_inputPath;

		int		_getFileSize(std::ifstream &file) const;
		void	_parseData(std::ifstream &file);
		void	_parseInput(std::ifstream &file);
		bool	_checkDate(std::string line);
		bool	_checkPositive(std::string line);
		bool	_checkTooLarge(std::string line);
		void	_output(std::ifstream &file);
		void	_nearestDate(std::string &key);
};

std::string trim(const std::string &str);

#endif