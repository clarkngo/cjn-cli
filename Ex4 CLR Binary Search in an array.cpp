// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 Binary Search in an array
#include "stdafx.h"
using namespace System;

int main(array<System::String ^> ^args)
{
	array <int>^ values = { 23, 45, 68, 94, 123, 127, 150, 203, 299 };
	int toBeFound(127);

	// BinarySearch() function
	int position = Array::BinarySearch(values, toBeFound);
	if (position < 0)
		Console::WriteLine(L"{0} was not found.", toBeFound);
	else
		Console::WriteLine(L"{0} was found at index position {1}.", toBeFound, position);
	Console::ReadLine();
	return 0;
}
