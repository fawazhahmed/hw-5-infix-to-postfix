#include<string>
#include<iostream>
#include<stack>

int prec(char c)					//function to decide operator precedence
{
		switch (c)					//switch statement based on the inputs
		{
		case '+':  
		case '-':
			return 2;				 //if any of these operators, return this value 
		case '*':
		case '/':
			return 4;				//if any of these operators, return higher value
		}
		return -1;					//if none, return this
}

std::string I2PConvertor(const std::string& infix_expr)
{
	std::stack<char> st;				//initialize stack and variables
	std::string a;
	
	for(auto ch : infix_expr)				//loop through the given string
	{ 
		if (isalpha(ch))				//if its a character	
		{
			a += ch;						//push in into string
		}
		else if (ch == '(')					//if this
		{
			st.push(ch);					//push into stack
		}
		else if(ch == ')')					//if this 
		{
			while (!st.empty() && st.top() != '(')				//while stack is not empty and the top is not equal to closing bracket
			{
				a += st.top();							//add to the string from the stack 
				st.pop();								//remove it from stack
			}	
			if (st.top() == '(')						//if this is still in stack
				st.pop();								//simply remove it
		 }
		else										//any other thing in there (operator)
		{
			if (st.empty())							//if the stack is empty
			{
				st.push(ch);						//push next value into it
			}
			else									//if not
			{	
				if (prec(ch) > prec(st.top()))			//if there is a higher precedence in input than in the stack 
				{
					st.push(ch);						//push it into stack
				}
				else
				{
					while (!st.empty() && prec(ch) <= prec(st.top()))			//while the stack is not empty and the next character is less precedence than the value at top stack 
					{
						a += st.top();				//add to string from the stack
						st.pop();					//remove it from stack
					}
					st.push(ch);					//push any final characters to stack
				}
			}
		}
	}
	while (!st.empty())								//while stack is not empty, repeat the above steps
	{
		a += st.top();
		st.pop();
	}
	return a;							//return what is left over in string function
}

int main()
{
//	std::string test{ "a+b" };
	std::string infix1{ "a*b+c" };

	std::string infix2{ "a-b*c" };

	std::string infix3{ "(a+b)/c" };

	std::string infix4{ "(a+b)*(c-d)" };

	// expected: ab*c+
	std::cout << I2PConvertor(infix1) << std ::endl;			//call the function for the following and display the results
	// expected: abc*-
	std::cout << I2PConvertor(infix2) << std::endl;
	// expected: ab+c/
	std::cout << I2PConvertor(infix3) << std::endl;
	// expected: ab+cd-*
	std::cout << I2PConvertor(infix4) << std::endl;
//	std::cout << I2PConvertor(test) << std::endl;

	return 0; 
}