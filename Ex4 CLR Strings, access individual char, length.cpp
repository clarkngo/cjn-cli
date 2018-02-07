// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 Strings, access individual char, length
#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	System::String^ saying(L"Many hands make light work.");
	Console::WriteLine(L"The third character in the string is {0}", saying[2]);
	Console::WriteLine(L"The string has {0} characters.", saying -> Length);
    Console::ReadLine();
    return 0;
}
