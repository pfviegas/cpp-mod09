// incluir header 42

#include "../include/BitcoinExchange.hpp"

// Default Constructor
BitcoinExchange::BitcoinExchange() {}

// Parametrized Constructor
BitcoinExchange::BitcoinExchange (std::ifstream &file, char **argv)
{
	std::ifstream	data;

	data.open("data.csv", std::ifstream::in);
	this->_parseData(data);

	this->_inputSize = this->_getFileSize(file) - 1;
	this->_input = new int[this->_inputSize];

	for (int i = 0; i < this->_inputSize; i++)
		this->_input[i] = 0;

	file.open(argv[1], std::ifstream::in);
	this->_parseInput(file);

	file.open(argv[1], std::ifstream::in);
	this->_output(file);
}

// Copy Constructor
BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
	this->_map = other._map;
	this->_inputSize = other._inputSize;
	this->_input = other._input;
}

// Destructor
BitcoinExchange::~BitcoinExchange()
{
	delete [] this->_input;
}

// Copy assignment operator
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
	if (this != &other) {
		this->_map = other._map;
		this->_inputSize = other._inputSize;
		this->_input = other._input;
	}
	return (*this);
}

// Members functions
/**
 * @brief Prints the contents of the BitcoinExchange container.
 *
 * This function iterates over the map container and prints each key-value pair.
 * The keys represent the names of cryptocurrencies, and the values represent their corresponding exchange rates.
 * The output is formatted with fixed precision of 2 decimal places.
 */
void BitcoinExchange::printContainer() const
{
	std::map<std::string, float>::const_iterator	it;
	std::map<std::string, float>::const_iterator	ite = this->_map.end();

	for (it = this->_map.begin(); it != ite; it++)
		std::cout << "\'" << it->first << "\' : \'" << std::fixed << std::setprecision(2) << it->second << "\'" << std::endl;
}

/**
 * @brief Get the size of a file.
 * 
 * This function reads the contents of the given file and returns the number of lines in the file.
 * 
 * @param file The input file stream to read from.
 * @return The number of lines in the file.
 */
int BitcoinExchange::_getFileSize(std::ifstream &file) const
{
	int i = 0;
	std::string line;

	while (getline(file, line))
		i++;
	
	file.close();
	return (i);
}

/**
 * @brief Parses data from a file and populates a map with key-value pairs.
 * 
 * This function reads data from a file and extracts key-value pairs separated by commas.
 * It then converts the value to a float and inserts it into a map using the key.
 * 
 * @param file The input file stream to read data from.
 */
void BitcoinExchange::_parseData(std::ifstream &file)
{
	std::string line;
	std::string key;
	std::string field;
	std::string value;
	float f;
	int i = 0;
	
	while (getline(file, line))
	{
		std::istringstream	s(line);
		while (getline(s, field, ','))
		{
			if (i == 1)
				key = field;
			if (i == 2)
			{
				value = field;
				f = atof(field.c_str());
				this->_map.insert(std::pair<std::string, float>(key, f));
			}
			i++;
		}
		i = 1;
	}
	file.close();
}

/**
 * Parses the input from a file and populates the _input array.
 * 
 * @param file The input file stream to read from.
 */
void BitcoinExchange::_parseInput(std::ifstream &file)
{
	std::string line;
	int	i = 0;

	// Skip the first line (header)
	getline(file, line);
	while(getline(file, line))
	{
		this->_input[i] = 0;		// 0 = no error
		if (this->_checkPositive(line) == false)
			this->_input[i] = 1;	// 1 = not a positive number
		if (this->_checkDate(line) == false && line.length() < 11)
			this->_input[i] = 2;	// 2 = Invalid date
		if (this->_checkTooLarge(line) == false)
			this->_input[i] = 3;	// 3 = too large a number
		i++;
	}
	file.close();
}

/**
 * @brief Checks if the given date is valid.
 * 
 * This function checks if the date provided in the input string is valid.
 * The date should be in the format "YYYY-MM-DD".
 * 
 * @param line The input string containing the date to be checked.
 * @return True if the date is valid, false otherwise.
 */
bool BitcoinExchange::_checkDate(std::string line)
{
	std::istringstream	s(line);
	std::string			date;

	getline(s, date, '|');
	date = ::trim(date);

	if (date.length() != 10)
		return (false);

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year > 2024 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);

	return (true);
}

/**
 * Checks if a given line contains a positive value.
 *
 * @param line The line to be checked.
 * @return True if the value is positive, false otherwise.
 */
bool BitcoinExchange::_checkPositive(std::string line)
{
	std::istringstream	s(line);
	std::string			value;
	size_t				found;
	float				f;

	getline(s, value, '|');
	getline(s, value, '|');

	found = value.find("-");
	found = value.find("-", found + 1);
	if (found == std::string::npos)
	{
		f = atof(value.c_str());
		if (f > 0)
			return (true);
		else
			return (false);
	}
	return (false);
}

/**
 * Checks if the value in the given line is too large.
 * 
 * @param line The input line containing the value to check.
 * @return True if the value is not too large, false otherwise.
 */
bool	BitcoinExchange::_checkTooLarge(std::string line)
{
	std::istringstream	s(line);
	std::string			value;
	float				f;

	getline(s, value, '|');
	getline(s, value, '|');

	f = atof(value.c_str());
	if (f >= static_cast<float>(__INT_MAX__))
		return (false);
	return (true);
}

/**
 * Reads data from the input file stream and performs calculations based on the data.
 * Prints the results to the standard output.
 *
 * @param file The input file stream to read data from.
 */
void BitcoinExchange::_output(std::ifstream &file)
{
	std::string line, key, value;
	int i = 0;

	// Skip the first line (header)
	getline(file, line);
	while (i < this->_inputSize)
	{
		if (!getline(file, line))
			break;

		std::istringstream	s(line);
		getline(s, key, '|');
		key = ::trim(key);
		getline(s, value, '|');
		value = ::trim(value);

		if (this->_input[i] == 0)
		{
			if (this->_map.find(key) == this->_map.end())
			{
				while (this->_map.find(key) == this->_map.end() && key != "Error: Year too old.")
					this->_nearestDate(key);
			}

			if (key == "Error: Year too old.")
				std::cout << key << std::endl;
			else
				std::cout << key << " => " << value << " = " << atof(value.c_str()) * this->_map[key] << std::endl;
		}
		else if (this->_input[i] == 1)
			std::cout << "Error: not a positive number." << std::endl;
		else if (this->_input[i] == 2)
			std::cout << "Error: bad input => " << key << std::endl;
		else if (this->_input[i] == 3)
			std::cout << "Error: too large a number." << std::endl;

		++i;
	}
}

/**
 * @brief Adjusts the given date to the nearest previous date.
 * 
 * This function takes a date in the format "YYYY-MM-DD" and adjusts it to the nearest previous date.
 * 
 * If the given date is the first day of the month, 
 * it will be adjusted to the last day of the previous month.
 * If the given date is the first day of the year, 
 * it will be adjusted to the last day of the previous year.
 * 
 * If the given date is before the year 2009, an error message will be returned.
 * 
 * @param key The date to be adjusted, in the format "YYYY-MM-DD".
 */
void BitcoinExchange::_nearestDate(std::string &key)
{
	int year = std::atoi(key.substr(0, 4).c_str());
	int month = std::atoi(key.substr(5, 2).c_str());
	int day = std::atoi(key.substr(8, 2).c_str());

	if (day > 1)
	{
		day--;
	}
	else
	{
		day = 31;
		if (month > 1)
		{
			month--;
		}
		else
		{
			month = 12;
			if (year > 2009)
			{
				year--;
			}
			else
			{
				key = "Error: Year too old.";
				return;
			}
		}
	}

	key = toString(year) + "-";
		if (month > 9)
			key += toString(month) + "-";
		else
			key += "0" + toString(month) + "-";
		if (day > 9)
			key += toString(day);
		else
			key += "0" + toString(day);
}
