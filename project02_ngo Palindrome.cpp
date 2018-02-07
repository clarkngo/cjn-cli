// Author @Clark Jason Ngo
// IS 375 C++ Intermediate Winter 2018
// City University of Seattle
// Professor Richard Gary
// Project 2 - CLR String Program
#include "stdafx.h"
using namespace System;

int main(array<System::String ^> ^args)
{
	// declare int variables
	int upperCase;
	int lowerCase;
	int nonLetter;
	int blankSpaces;

	// declare and initialize bool variable
	bool palindrome = true;

	// prompt message
	Console::Write(L"Palindrome examples:\n");
	Console::Write(L"ABBA\n");
	Console::Write(L"racecar\n");
	Console::Write(L"was it a car or a cat i saw\n");
	Console::Write(L"1_(@_@)_1\n\n");

	Console::Write(L"Enter word/number/phrase or sequence:\n");
	// String object word 
	String^ word = Console::ReadLine();

	// for loop, no. of uppercase, lowercase, non letter characters
	for (int i = 0; i < word->Length; i++)
	{
		// assign String^ individual character element to wchar_t
		wchar_t letter = word[i];
		if (letter < 'A')		// Test for numerical and symbols
			nonLetter++;		// no. of non letters
		if (letter >= 'A')		// Test for 'A' or larger
			if (letter <= 'Z')	// Test for 'Z' or smaller
				upperCase++;	// no. of uppercase letters
		if (letter >= 'a')		// Test for 'a' or larger
			if (letter <= 'z')	// Test for 'z' or smaller
				lowerCase++;	// no. of lowercase letters
		if (letter == ' ')		// Test for ' '
			blankSpaces++;		// no. of blank spaces
	}

	// String object capitalize to standarize case of characters to check
	// palindrome regardless if upper or lower case in String object word
	String^ capitalized = word->ToUpper();

	// for loop until half length of characters
	// loop starts at at element 0 
	// ends until total no. of characters (element MAX -1)
	for (int j = 0, k = capitalized->Length - 1; k >= j; k--)
	{
		if (j > k) break;			// exit loop
		if (capitalized[j] == ' ') j++;	// skip spaces
		if (capitalized[k] == ' ') k--;	// skip spaces
		if (capitalized[j] != capitalized[k]) palindrome = false; // return bool false
		j++;						// increment int j counter
	}

	// Display results
	Console::Write(L"\nTotal number of uppercase characters: ");
	Console::Write(upperCase);
	Console::Write(L"\nTotal number of lowercase characters: ");
	Console::Write(lowerCase);
	Console::Write(L"\nTotal number of non-alphabetic characters: ");
	Console::Write(nonLetter);
	Console::Write(L"\nTotal number of blank spaces: ");
	Console::Write(blankSpaces);
	Console::Write(L"\nTotal number of characters with blank spaces: ");
	Console::Write(word->Length);
	Console::Write(L"\nTotal number of characters without blank spaces: ");
	Console::Write((word->Length) - blankSpaces);
	Console::Write(L"\nPalindrome?: ");
	Console::Write(palindrome);
	Console::Write(L"\n");

	Console::ReadLine();
	return 0;
}