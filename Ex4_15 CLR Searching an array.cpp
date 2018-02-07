// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4_15.cpp : main project file.
// Searching an array
#include "stdafx.h"
using namespace System;
int main(array < System::String ^ > ^args)
{
	array < String^ > ^ names = { "Jill", "Ted", "Mary", "Eve", "Bill",
		" Al", "Ned", "Zoe", "Dan", "Jean" };
	array < int > ^ weights = { 103, 168, 128, 115, 180,
		176, 209, 98, 190, 130 };
	array < String^ > ^ toBeFound = { "Bill", "Eve", "Al", "Fred" };
	Array::Sort(names, weights); // Sort the arrays
	int result(0); // Stores search result
	for each(String^ name in toBeFound) // Search to find weights
	{
		result = Array::BinarySearch(names, name); // Search names array
		if (result < 0) // Check the result
			Console::WriteLine(L"{0} was not found.", name);
		else
			Console::WriteLine(L"{0} weighs {1} lbs.", name, weights[result]);
	}
	Console::ReadLine();
	return 0;
}