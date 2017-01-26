/*

1. The Fibonacci numbers are a sequence of integers (F_1, F_2,...) defined as follows:
F_1 = 1
F_2 = 1
F_n = F_{n+1} + F_n{n-2} for all n > 2. 

Write a recursive function to compute the n-th Fibonacci number, where n is supplied by the user. What is the largest value of n for which your program will work? 

2. Write a calculator program that evaluates boolean expressions (sometimes called logical expressions). You must handle the binary operations | (or), & (and), and ^ (xor), and the operands 0 (false) and 1 (true). (Reminder: The or operator returns 1 if at least one of its operands is 1 and returns 0 otherwise; the and operator returns 1 if both its operands are 1 and returns 0 otherwise; and the xor operator returns 1 if exactly one of its operands is 1 and returns 0 otherwise.) The order of precedence of operations is &, then ^, and then |. For example, 0|1^0 means 0|(1^0). and 1^1&0 means 1^(1&0). Allow the use of parentheses to alter the default precedence.

Begin by writing a grammar for logical expressions, and include the grammar in the documentation of your program. (It will be similar to the grammar for arithmetic expressions used in Chapter 6.)

*/

#include "std_lib_facilities_4.h"

void fibonacci(int n) {
	if (x == 1 | x == 2)
		return 1;
	else if (x > 2) {
		return fibonacci(n+1) + fibonacci(n-2);
	else 
		error("ERROR");
	}
	
for(int n=2; n > 2; n++) {
	fibonacci(n);
	n++;
}

int main() {
	cout << "Insert a term 'n' to compute the nth Fibonacci number..." << endl;
	cin >> n;
	cout << fibonacci(n) << endl;

return 0;

}