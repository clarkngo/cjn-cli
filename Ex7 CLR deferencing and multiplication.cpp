// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 7 Defining Your Own Data Types
// Ex7 dereferencing and multiplication
#include "stdafx.h"
using namespace System;
int main(array < System::String ^ > ^args)
{
	double pi(3.142); // pi is stored on the stack
	int^ lucky(gcnew int(7)); // lucky is a handle and 7 is stored on the heap
	double^ two(2.0); // two is a handle, and 2.0 is stored on the heap

	Console::WriteLine(L"2pi = {0}", *two*pi); // dereferencing and multiplying

	Console::WriteLine(L"2pi = {0}", pi**two); // same result

	Console::WriteLine(L"2pi = {0}", pi*(*two)); // clearer code

	Console::ReadLine();
	return 0;
}