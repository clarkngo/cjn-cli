// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 CLR array sort with a range
#include "stdafx.h"
using namespace System;
int main(array < System::String ^ > ^args)
{
	// stores 50 values
	array < int > ^ samples = { 27, 3, 54, 11, 18, 2, 16 };
	Array::Sort(samples, 2, 3); // Sort elements 2 to 4
	
	for each(int value in samples) // Output the array elements
		Console::Write(L"{0, 8}", value);
	Console::WriteLine();

	Console::ReadLine();
}



