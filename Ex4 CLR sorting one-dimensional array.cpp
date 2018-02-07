// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 CLR sorting one-dimensional array
#include "stdafx.h"
using namespace System;
int main(array < System::String ^ > ^args)
{
	array < int > ^ samples = { 27, 3, 54, 11, 18, 2, 16 };
	// Sort the array elements
	// Sort() function
	Array::Sort(samples);
	for each(int value in samples) // Output the array elements
		Console::Write(L"{0, 8}", value);
	Console::WriteLine();

	Console::ReadLine();
}