// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 2 Data, Variables, and Calculations
// Ex2_12-13 
// Reading an Integer
#include "stdafx.h"
using namespace System;
int main(array < System::String ^ > ^args)
{
	Console::Write(L"Enter an integer: ");
	int value = Int32::Parse(Console::ReadLine());
	Console::WriteLine(L"You entered {0}", value);
	Console::ReadLine();
	return 0;
}