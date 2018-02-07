// Author @Clark Jason Ngo
// IS 375 C++ Intermediate Winter 2018
// City University of Seattle
// Professor Richard Gary
// Project 1 - CLR Console Program

/*
The student will implement a CLR console program that takes input from a user,
calculates a result and returns it to the console.The program should loop and continue
to take input until the user closes the program.There must be at least 4 options the user
can select for manipulation of the inputs.The program must use a C++ / CLI Enumeration.


A typical session might look like :

Would you like to :
a) add two numbers
b) multiply two numbers
...
Enter first number :
Enter second number :
Result is :
Would you like to :
a) ...
*/


#include "stdafx.h"
using namespace System;
int main(array < System::String ^ > ^args)
{
	// Describe console key that was pressed
	// Response to Console.ReadKey method
	ConsoleKeyInfo keyPress;

	// defined enumeration class Choose
	enum class Choose { add = 1, multiply, subtract, divide };

	// declared int choose
	int option;
	// do...while loop until keyboard input is equal to 'Escape'
	do
	{
		// Prompt message to add or multiple
		Console::Write(L"Would you like to:\n");
		Console::Write(L"a) add two numbers (press 1)\n");
		Console::Write(L"b) multiply two numbers (press 2)\n");
		Console::Write(L"c) subtract two numbers (press 2)\n");
		Console::Write(L"d) divide two numbers (press 2)\n");
		String^temp = Console::ReadLine();
		option = int::Parse(temp);


		// if statement
		// add 2 integers if variable option is 1
		if (option == (int)Choose::add)
		{
			Console::Write(L"Enter first number: ");
			int num1 = Int32::Parse(Console::ReadLine());
			Console::Write(L"Enter second number: ");
			int num2 = Int32::Parse(Console::ReadLine());
			Console::Write(L"Result is: ");
			Console::WriteLine(num1 + num2);
		}
		// multiply 2 integers if variable option is 2
		else if (option == (int)Choose::multiply)
		{
			Console::Write(L"Enter first number: ");
			int num1 = Int32::Parse(Console::ReadLine());
			Console::Write(L"Enter second number: ");
			int num2 = Int32::Parse(Console::ReadLine());
			Console::Write(L"Result is: ");
			Console::WriteLine(num1 * num2);
		}
		// subtract 2 integers if variable option is 3
		else if (option == (int)Choose::subtract)
		{
			Console::Write(L"Enter first number: ");
			int num1 = Int32::Parse(Console::ReadLine());
			Console::Write(L"Enter second number: ");
			int num2 = Int32::Parse(Console::ReadLine());
			Console::Write(L"Result is: ");
			Console::WriteLine(num1 - num2);
		}
		// divide 2 integers if variable option is 4
		else if (option == (int)Choose::divide)
		{
			Console::Write(L"Enter first number: ");
			int num1 = Int32::Parse(Console::ReadLine());
			Console::Write(L"Enter second number: ");
			int num2 = Int32::Parse(Console::ReadLine());
			Console::Write(L"Result is: ");
			Console::WriteLine(num1 / num2);
		}
		// if variable option is not 1, 2, 3 or 4
		else
			Console::Write(L"Please Choose option 1, 2, 3 or 4: ");

		// prompt message to quit or continue
		Console::WriteLine(L"Press Escape to quit, Press Any Key to continue.");

		ConsoleKeyInfo keyPress;

		// true, results in key press no being displayed on the command line
		// false, will cause the key press to be displayed on the command line
		keyPress = Console::ReadKey(true);

		// exit if keyboard input is 'Escape'
		if (keyPress.Key == ConsoleKey::Escape)
			return 0;
	} while (keyPress.Key != ConsoleKey::Escape); // end do...while loop
} // end main
