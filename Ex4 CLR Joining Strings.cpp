// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 Joining Strings

#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	String^ name1(L"Beth");
	String^ name2(L"Betty");
	String^ name3(name1 + L" and " + name2);

	Console::Write(name3);

	Console::Write(L"\n");

	String^ str(L"Value: ");
	String^ str1(str + 2.5); // Result is new string L"Value: 2.5"
	String^ str2(str + 25); // Result is new string L"Value: 25"
	String^ str3(str + true); // Result is new string L"Value: True"

	Console::Write(str3);

	Console::Write(L"\n");

	char ch('Z');
	wchar_t wch(L'Z');
	String^ str4(str + ch); // Result is new string L"Value: 90"
	String^ str5(str + wch); // Result is new string L"Value: Z"

	Console::Write(str5);

	Console::Write(L"\n");

	array < String^ > ^ names = { L"Jill", L"Ted", L"Mary", L"Eve", L"Bill" };
	String^ separator(L", ");
	String^ joined = String::Join(separator, names);

	Console::Write(joined);

	Console::ReadLine();

    return 0;
}
