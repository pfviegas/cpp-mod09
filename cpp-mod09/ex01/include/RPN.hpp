// incluir header 42

#ifndef _RPN_HPP_
#define _RPN_HPP_

#include <iostream>
#include <string>
#include <stack>
#include <cstring>

class RPN
{
	public:
		RPN();
		RPN(char *input);
		RPN(RPN const &src);
		~RPN();

		RPN &operator=(RPN const &other);

	private:
		std::stack<int>	_stack;
		void evaluateExpression(const char *input);
};

#endif