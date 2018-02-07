// ConsoleApplication14.cpp : main project file.

#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	array<String^>^ names = { "Jill", "Ted", "Mary", "Eve", "Bill",
	"Al", "Ned", "Zoe", "Dan", "Jean" };
	Array::Sort(names);			// Sort the array
	String^ name = L"Fred";
	int position(Array::BinarySearch(names, name));
	if (position < 0)			// If its is negative
		position = ~position;	// flip the bits to get the insert index

	array<String^>^ newNames = gcnew array<String^>(names->Length + 1);

	// copy elements from names to newNames
	for (int i = 0; i < position; i++)
		newNames[i] = name[i];

	newNames[position] = name;							// copy the new elements

	if (position < names->Length)		// if any elements in names				

		for (int i = position; i < names->Length, i++)	
			newNames[i + 1] = names[i];					//copy them to newNames

    Console::ReadLine();
    return 0;
}
