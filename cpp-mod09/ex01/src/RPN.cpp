// incluir header 42

#include "../include/RPN.hpp"

// Default Constructor
RPN::RPN () {}

// Parametrized Constructor
RPN::RPN(char * input)
{
	evaluateExpression(input);
}

// Copy Constructor
RPN::RPN(RPN const &src) : _stack(src._stack) {}

// Destructor
RPN::~RPN() {}

// Copy assignment operator
RPN &RPN::operator=(RPN const &other)
{
	if (this != &other)
		this->_stack = other._stack;
	return (*this);
}

// Member function
void RPN::evaluateExpression(const char *input)
{
	int digitCount = 0, signCount = 0;

	// First pass to validate the input
	for (int i = 0; input[i] != '\0'; ++i)
	{
		if (isdigit(input[i]))
		{
			++digitCount;
		}
		else if (strchr("*/+-", input[i]))
		{
			++signCount;
		}
		else if (input[i] != ' ')
		{
			throw std::runtime_error("Error: Invalid character in input.");
		}
	}

	if (signCount != digitCount - 1)
		throw std::runtime_error("Error syntax: You must have one digit more than signs.");

	// Second pass to evaluate the expression
	for (int i = 0; input[i] != '\0'; ++i)
	{
		if (isdigit(input[i]))
		{
			_stack.push(input[i] - '0');
		}
		else if (strchr("*/+-", input[i]))
		{
			if (_stack.size() < 2)
			{
				throw std::runtime_error("Error: Invalid RPN expression.");
			}

			int second = _stack.top(); _stack.pop();
			int first = _stack.top(); _stack.pop();
			int result = 0;

			switch (input[i])
			{
				case '*':
					result = first * second;
					break;
				case '/':
					result = first / second;
					break;
				case '+':
					result = first + second;
					break;
				case '-':
					result = first - second;
					break;
			}
			_stack.push(result);
		}
	}

	if (_stack.size() != 1)
	{
		throw std::runtime_error("Error: Invalid RPN expression.");
	}
	std::cout << _stack.top() << std::endl;
}
