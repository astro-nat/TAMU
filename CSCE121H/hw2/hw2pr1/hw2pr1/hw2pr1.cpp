//hw2pr1.cpp : Defines the entry point for the console application.

/*

Chapter 5 Exercise 12

Implement a little guessing game called (for some oscure reason) Bulls and Cows." 
The program has a vector of four different integers in range 0 to 9 (e.g., 1234 but not 1122) and it is the user's task to discover those numbers by repeated guesses. 
Say the number to be guessed is 1234 and the user guesses 1359;
The response should be "1 bull and 1 cow" because the user got one digit (1) right and in the right position ( a bull) and one digit (3) right but in the wrong position (a cow). 
The guessing continues until the user gets four bulls, that is, has the four digits correct and in the correct order.

*/

#include "stdafx.h"
#include "std_lib_facilities_4.h"


int main()
{
	//create vector with 4 random integers
	int i;
	vector<int> v_computer(4);
	vector<int> v_userguess(4);
	for (i = 1; i < 10; ++i)
		v_computer.push_back(i);

	random_shuffle (v_computer.begin(), v_computer.end(), i); // 1 2 3 4 5 6 7 8 9

	cout << "Type four numbers between 1 and 9 and see if you can guess the sequence I have generated./n If you guess a number correctly in the right position, you will receive a BULL. If it is wrong, you will receive a COW./n Keep guessing until you receive four BULLs.";
	int guess;
	while (cin >> guess)
		v_userguess.push_back(guess);

	//if the user guesses a number in the correct space that matches the original vector, the program returns "BULL" in that place.
	//if the user guesses the wrong number in the matching position, the program returns "COW" in that place.
	while (v_computer[0, 1, 2, 3] != v_userguess[0, 1, 2, 3])
		if (v_computer[i] != v_userguess[i]) {
			cout << "COW ";
		}
		else if (v_computer[i] == v_userguess[i]) {
			cout << "BULL ";
		}
		else {
			cout << "Oops, something went wrong.\n";
		}

		if (v_computer[0, 1, 2, 3] == v_userguess[0, 1, 2, 3]) {
			cout << "BULL BULL BULL BULL. The correct answer is " << v_userguess[i] << ". Congratulation! You've won! YOU'RE SO SMART!\n";
		}
	//prompt the user to guess four numbers
	
	//The user keeps guessing until the program returns "bull bull bull bull"
	//Yay! You've won!
	return 0;
}