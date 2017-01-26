//1. The Fibonacci numbers are a sequence of integers (F_1, F_2,...) defined as follows:
//F_1 = 1
//F_2 = 1
//F_n = F_{n-1} + F_n{n-2} for all n > 2. 

//Write a recursive function to compute the n-th Fibonacci number, where n is supplied by the user. What is the largest value of n for which your program will work? 

#include "std_lib_facilities_4.h"

int fibonacci(int x) {
	if (x == 1 | x == 2)
		return 1;
	else if (x > 2) {
		return fibonacci(x-1) + fibonacci(x-2);
	}
	else {
		error("ERROR");
	}
	
for(int x=2; x > 2; x++); {
	fibonacci(x);
	x++;
}

}

int main() {
	int n;
	cout << "Insert a term 'n' to compute the nth Fibonacci number..." << endl;
	cin >> n;
	cout << fibonacci(n) << endl;

return 0;

}

// The largest number is 46 for which the program will work.