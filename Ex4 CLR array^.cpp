// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 CLR array^
#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	// Create an array to store 100 integers
	// array element type is int
	// handle name is data
	// gcnew operator to create CLR array
	/*
	array<int>^ data = gcnew array<int>(100); 
	*/

	// functional notion
	array<int>^ data(gcnew array<int>(100));

    Console::ReadLine();
    return 0;
}
