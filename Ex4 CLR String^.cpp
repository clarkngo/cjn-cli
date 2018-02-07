// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 CLR String^
#include "stdafx.h"
using namespace System;
int main(array < System::String ^ > ^args)
{
	// declare String^ speak
	// ^ is a pointer-like
	String^ speak(L"I do not wish to speak...");

	// output String^ speak
	Console::Write(speak);
	Console::ReadLine();
	return 0;
}