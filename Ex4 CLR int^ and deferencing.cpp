// Author @Clark Jason Ngo
// Ivor Horton's Beginning C++ Beginning Visual C++ 2010
// Chapter 4 Arrays, Strings and Pointers
// Ex4 CLR int^ and deferencing
#include "stdafx.h"
using namespace System;
int main(array < System::String ^ > ^args)
{
	// declare handle damage
	// ^ is a pointer-like
	int^ damage(20);

	// deference handle damage to use value
	/*int resistance((*damage) / 2);*/

	// declaring handle resistance
	int^ resistance(nullptr);

	// deference
	/**resistance = ((*damage) / 2);*/
	
	// compiler automatically deference
	resistance = ((*damage) / 2);




	// output int resistance
	Console::Write(resistance);
	Console::ReadLine();
	return 0;
}