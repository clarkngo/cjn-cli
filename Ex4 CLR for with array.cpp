// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 CLR for with array
#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	array<int>^ data(gcnew array <int>(100));

	// for loop outputs 2, 4.... 200.
	/*
	for (int i = 0; i < 100; i++)
	{
		data[i] = 2 * (i + 1);
		Console::Write(data[i]);
		Console::Write(L" ");
	}
	*/

	// Length property to record the number of elements
	// loop-continuing condition set to <int>(100)
	for (int i = 0; i < data->Length; i++)
	{
		data[i] = 2 * (i + 1);
		Console::Write(data[i]);
		Console::Write(L" ");
	}

    Console::ReadLine();
    return 0;
}
