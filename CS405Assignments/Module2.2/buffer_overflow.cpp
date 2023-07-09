// buffer_overflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Eric Slutz
// SNHU - CS405 Secure Coding
// Module 2 Assignment 2
//

// Define the max length to be used for input.
#define MAX_INPUT_LENGTH 20

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	// TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
	//  even though it is a constant and the compiler buffer overflow checks are on.
	//  You need to modify this method to prevent buffer overflow without changing the account_order
	//  varaible, and its position in the declaration. It must always be directly before the variable used for input.
	const std::string account_number = "CharlieBrown42";
	// To prevent buffer overflow issues, it's reccomended to use a string over a char array.
	char user_input[MAX_INPUT_LENGTH];
	// Get the length of the array.
	std::size_t len = sizeof(user_input);
	std::cout << "Enter a value: ";
	// Read in the users input, setting the maximum input to 20 characters.
	std::cin.getline(user_input, MAX_INPUT_LENGTH);

	// Check if the input exceeded 20 characters.
	// If true, warn user of buffer overflow and trimmed input.
	// Clear the buffer and any cin errors.
	if (!std::cin)
	{
		std::cout << "Buffer Overflow! Input values that exceeded the buffer limit will be stripped." << std::endl << std::endl;
		// Clear any cin errors.
		std::cin.clear();
		// Clear anything remaining in the buffer.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "You entered: " << user_input << std::endl;
	std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
