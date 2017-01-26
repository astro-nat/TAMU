//2. Write a calculator program that evaluates boolean expressions (sometimes called logical expressions). You must handle the binary operations | (or), & (and), and ^ (xor), and the operands 0 (false) and 1 (true). 

//(Reminder: The or operator returns 1 if at least one of its operands is 1 and returns 0 otherwise; the and operator returns 1 if both its operands are 1 and returns 0 otherwise; 
//and the xor operator returns 1 if exactly one of its operands is 1 and returns 0 otherwise.) The order of precedence of operations is &, then ^, and then |. 
//For example, 0|1^0 means 0|(1^0). and 1^1&0 means 1^(1&0). Allow the use of parentheses to alter the default precedence.

//Begin by writing a grammar for logical expressions, and include the grammar in the documentation of your program. (It will be similar to the grammar for arithmetic expressions used in Chapter 6.)

#include "std_lib_facilities_4.h"

/* Grammar

Expression()
	Term
	Term '+' Expression
	Term '-' Expression
Term()
	Primary
	Term '*' Primary
	Term '/' Primary
	Term '%' Primary
Primary()
	Number floating-point-value
	'(' Expression ')'

	
User inputs expressions (no limit) and when they enter "q", it'll calculate whether all of them are true, one of them is true, or if only one of them is true. 

*/

struct Token 
	{
	public:
		char kind;
		double value; 
		Token(char ch):kind(ch),value(0){}
	};

class Token_stream
{
public:
	Token get();
	void putback(Token);
	Token_stream();
private:
	bool full {false};
	Token buffer;
};

void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get() 
{
	if (full) {full = false; return buffer;}
	
	char ch;
	cin >> ch;

	switch(ch)
	{
	case '(': case ')': case ';': case 'q': case '+': case '-':case '*':case '/':
		return Token(ch);
	case '.':
	case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
		{ 
		cin.putback(ch);
		double val;
		cin >> val;
		return Token('8');
		}
	default:
		error("Bad token");
	}
}

Token_stream ts;
bool expression();

double primary() 
{ 
	Token t = ts.get();
	switch (t.kind) 
	{
	case '(':
		{ 
		bool d = expression();
		t = ts.get();
		if (t.kind != ')') error ("')' expected");
		}
	case '8':
		return t.value;
	default:
		error("primary expected");
	}
}

double term() 
{ 
	double left = primary();
	Token t = ts.putback();
	
	while (true) 
	{
	switch (t.kind)
	{
	case '*':
		left *= primary();
		t = ts.get();
		break;
	case '/':
	{
		double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		t = ts.get();
		break;
	}
	default:
		t = ts.putback();
		return left;
	}
	}
}

bool expression()
{
	double left = term();
	Token t = ts.get();

	while (true) 
	{
		switch (t.kind) 
		{
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			t = ts.putback();
			return left;
		}
	}
}

int main() 
{
	try 
	{
		bool a;
		bool b;
		bool c;
		while (cin)
			a == expression();
			b == expression();
			c == expression();
		{
        Token t = ts.get();

        while(true)
			if (t.kind == 'q' | t.kind == ';') break; // 'q' or ';' for quit
			if (a | b | c == true) {
				cout << "At least one of your expressions is true." << endl;
				return 1;
				else return 0;
			
			else if (a & b & c == true)
			{
				cout << "All of your expressions are true." << endl;
				return 1; 
				else return 0; 
			}
			else if (a ^ b ^ c == true)
			{
				cout << "Exactly one of your expressions is true." << endl;
				return 1;
				else return 0;
			}
			}
        else 
		{
            t = ts.putback();
      	}
	}
	catch(exception& e) 
	{
		cerr << e.what("Something went wrong.");
	}
	catch(...)
	{
		cerr << e.what("Some other error.");
	}
	keep_window_open();
}

return 0;
}