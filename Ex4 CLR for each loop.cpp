// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 CLR for each loop
#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	// handle values
	array <int>^ values = { 3, 5, 6, 8, 6 };

	// for each loop iterates all the elements in the array
	// use 'values' for 'item' calculation
	// outputs 7 11 13 17 13
	for each(int item in values)
	{
		item = 2 * item + 1;
		// outputs value in element 0 of item (values) and 5 spaces
		Console::Write("{0,5}", item);
	}

    Console::ReadLine();
    return 0;
}
