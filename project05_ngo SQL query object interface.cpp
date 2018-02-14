/*****

******

** Author: Ngo, Clark Jason

** Assignment: Project 5 (Database and C++ Classes)

** Course: IS 375 C++ Intermediate

** Term: Winter, 2018

** School: City University of Seattle

******

*****/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <string>
#include <iostream>
using namespace System;
using namespace std;

// link with odbc32.lib
#pragma comment( lib, "odbc32.lib" )


// Employee class
class Employee
{
private:
	string _lastName;
	string _firstName;
	string _homeAddress;
	string _workPhoneNumber;
	string _departmentID;
	string _attribute;
	string _newValue;
public:
	// default constructor and overloading constructors
	Employee::Employee();
	Employee::Employee(char*, char*, char*, char*, char*);
	Employee(char * first, char * last, char * address, char*  phone, char*  depID, char * attribute, char * newValue);

	// getters
	string prepViewEmp();
	SQLCHAR* viewEmp();
	string prepareModEmpAtt();
	SQLCHAR* modifyEmpAtt();
	string prepareNewEmployee();
	SQLCHAR* newEmployee();
	SQLCHAR* convert(string);

	// void function call
	void displayLastName();
	void displayAttribute();
	void displayNewValue();
};

// constructors
Employee::Employee()
{
}
Employee::Employee(char *, char *, char *, char*, char*)
{
}
Employee::Employee(char* first, char* last, char* address,
	char*  phone, char*  depID, char* attribute, char* newValue)
{
	_firstName = first;
	_lastName = last;
	_homeAddress = address;
	_workPhoneNumber = phone;
	_departmentID = depID;
	_attribute = attribute;
	_newValue = newValue;
}

// 1) Given a last name, view all attributes for an employee.
string Employee::prepViewEmp()
{
	string lname;
	Console::WriteLine("Enter last name: ");
	cin >> lname;
	_lastName = lname;
	return "SELECT * FROM Employee WHERE lastName = \"" + lname + "\"";
}

// conversion of retrive employee string to SQLCHAR*
SQLCHAR* Employee::viewEmp()
{
	return convert(prepViewEmp());
}

// 2) Given a last name, attribute and new value, modify any attribute for an employee in the personnel schema.
string Employee::prepareModEmpAtt()
{
	string lname;
	Console::WriteLine("Enter last name: ");
	cin >> lname;
	_lastName = lname;

	string att;
	Console::WriteLine("Enter attribute: ");
	cin >> att;
	_attribute = att;

	string newValue;
	Console::WriteLine("Enter value: ");
	cin >> newValue;
	_newValue = newValue;

	return "UPDATE employee SET " + att + "=\"" + newValue + "\" WHERE lastName=\"" + lname + "\"";
}

// conversion of modify employee string to SQLCHAR*
SQLCHAR* Employee::modifyEmpAtt()
{
	return convert(prepareModEmpAtt());
}

// 3) Given a last name, first name, home address, work phone number and department, create a new employee entity in the personnel schema.
string Employee::prepareNewEmployee()
{
	Console::WriteLine("Enter first name: ");
	string fname;
	cin >> fname;
	_firstName = fname;

	Console::WriteLine("Enter last name: ");
	string lname;
	cin >> lname;
	_lastName = lname;

	Console::WriteLine("Enter address: ");
	string address;
	cin >> address;
	_homeAddress = address;

	Console::WriteLine("Enter work phone number: ");
	string phone;
	cin >> phone;
	_workPhoneNumber = phone;

	Console::WriteLine("Enter department ID: ");
	string depID;
	cin >> depID;
	_departmentID = depID;

	return
		"INSERT INTO Employee (firstName, lastName, homeAddress, workPhoneNumber, departmentID) "
		"VALUES (\"" + fname + "\", \"" + lname + "\", \"" + address + "\", \"" + phone + "\", \"" + depID + "\")";
}

// conversion of new employee string to SQLCHAR*
SQLCHAR* Employee::newEmployee()
{
	return convert(prepareNewEmployee());
}

// converter from string to SQL*CHAR
SQLCHAR* Employee::convert(string str)
{
	char* query = new char[str.length() + 1];
	strcpy(query, str.c_str());
	return (SQLCHAR*)query;
}

void Employee::displayLastName()
{
	cout << _lastName;
}
void Employee::displayAttribute()
{
	cout << _attribute;
}
void Employee::displayNewValue()
{
	cout << _newValue;
}

// Department class
class Department
{
private:
	string _departmentName;
	string _departmentLocation;
public:
	// constructors
	Department::Department();
	Department::Department(char*, char*);

	// getters
	string prepareModDepLoc();
	SQLCHAR* modifyDepLoc();
	SQLCHAR* convert(string);

	// void function call
	void displayDepartmentName();
	void displayDepartmentLocation();
};

// constructors
Department::Department()
{

}
Department::Department(char* depName, char* depLoc)
{
	_departmentName = depName;
	_departmentLocation = depLoc;
}

// 4) Given a department name and a new location, modify the location of that department in the personnel schema.
string Department::prepareModDepLoc()
{
	string depName;
	Console::WriteLine("Enter department name: ");
	cin >> depName;
	_departmentName = depName;

	string newDepLoc;
	Console::WriteLine("Enter value: ");
	cin >> newDepLoc;
	_departmentLocation = newDepLoc;

	return "UPDATE Department SET location =\"" + newDepLoc + "\" WHERE departmentName=\"" + depName + "\"";
}

// conversion of modify employee string to SQLCHAR*
SQLCHAR* Department::modifyDepLoc()
{
	return convert(prepareModDepLoc());
}

// conversion function
SQLCHAR* Department::convert(string str)
{
	char* query = new char[str.length() + 1];
	strcpy(query, str.c_str());
	return (SQLCHAR*)query;
}

void Department::displayDepartmentName()
{
	cout << _departmentName;
}
void Department::displayDepartmentLocation()
{
	cout << _departmentLocation;
}

// prompts user
void displayMessage()
{
	Console::Write(L"1) View all details of employee, enter last name\n");
	Console::Write(L"2) Modify detail of an employee, enter last name, attribute and new value\n");
	Console::Write(L"3) Create new entry for employee, enter last name, first name, address, work phone, department\n");
	Console::Write(L"4) Modify department location, enter department name\n");
	Console::Write(L"5) Exit program\n");
}

// function check error
bool CHECK(SQLRETURN rc, System::String^ msg, bool printSucceededMsg = false, bool quit = true)
{
	if (SQL_SUCCEEDED(rc))
	{
		if (printSucceededMsg)
		{
			Console::Write(msg);
			Console::Write(L"succeeded\n");
		}
		return true;
	}
	else
	{
		Console::Write(L" ");
		Console::Write(msg);
		Console::Write(L"FAILED!\n");

		if (quit)  FatalAppExitA(0, "OK - Quit then");

		return false;
	}
}

// function status 
void status(SQLSMALLINT handleType, SQLHANDLE theHandle, int line)
{
	SQLCHAR sqlState[6];
	SQLINTEGER nativeError;
	SQLCHAR msgStr[256];
	SQLSMALLINT overBy;
	SQLRETURN retCode;

	for (int i = 1; i < 20; i++)
	{
		retCode = SQLGetDiagRecA(handleType, theHandle, i, sqlState, &nativeError, msgStr,
			255, &overBy);

		if (CHECK(retCode, "SQLGetDiagRecA"))
		{
			printf("LINE %d:  [%s][%d] %s\n", line, sqlState, nativeError, msgStr);
		}
		else
		{
			break;
		}
	}
}



int main()
{
	Employee myEmployee; // Employee object named myEmployee
	Department myDepartment; // Department object named myDepartment

							 // create handles
	SQLHANDLE hEnv;
	SQLRETURN retCode;

	// allocate environment handle
	retCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	CHECK(retCode, "allocate environment handle");

	// set environment
	retCode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	CHECK(retCode, "setting the environment attribute setting to ODBC version 3");

	// allocate connection handle
	SQLHANDLE hConn;
	CHECK(SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn), "allocate handle");

	// connect to the database.
	SQLCHAR* dsnName = (SQLCHAR*)"mysqlstuff";
	SQLCHAR* userid = (SQLCHAR*)"clarkngo";
	SQLCHAR* password = (SQLCHAR*)"May092017";

	// open database connection
	retCode = SQLConnectA(hConn, dsnName, SQL_NTS, userid, SQL_NTS, password,
		SQL_NTS);

	if (!CHECK(retCode, "SqlConnectA", false))
	{
		status(SQL_HANDLE_DBC, hConn, __LINE__);
	}

	// declare variable option
	int option;		// variable to choose program function

	do // loop until Exit with "5";
	{
		// create and allocate a handle to statement
		SQLHANDLE hStmt;
		CHECK(SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt), "allocate handle for statement");

		// prompts user
		displayMessage();

		// declare variable choosen
		SQLCHAR* choosen;

		// 5 to exit
		do // limit user to options 1-5
		{
			String^temp = Console::ReadLine();
			option = int::Parse(temp);

			if (option == 1)
				choosen = myEmployee.viewEmp();
			else if (option == 2)
				choosen = myEmployee.modifyEmpAtt();
			else if (option == 3)
				choosen = myEmployee.newEmployee();
			else if (option == 4)
				choosen = myDepartment.modifyDepLoc();
			else if (option == 5)
				break; // break to exit loop
			else
				Console::Write(L"Enter numbers 1-5 only:\n");

		} while (option > 5 || option < 0);

		// execute query
		(SQLCHAR*)choosen;

		CHECK(SQLExecDirectA(hStmt, choosen, SQL_NTS), "execute query");


		// view all attributes 
		if (option == 1)
		{
			// read data results in the hStmt.
			retCode = SQLFetch(hStmt);
			CHECK(retCode, "first sqlFetch");

			// total numbers of rows
			SQLLEN numRows;
			retCode = SQLRowCount(hStmt, &numRows);
			/*Console::WriteLine("{0} rows were fetched.\n", numRows);*/
			SQLSMALLINT numCols;
			retCode = SQLNumResultCols(hStmt, &numCols);
			SQLCHAR colName[256];
			System::String^ colN;
			System::String^ bufN;

			SQLSMALLINT colNameLen, dataType, numDecimalDigits, allowsNullValues;
			SQLUINTEGER columnSize;

			Console::Write(L"\n");

			// column headers
			for (int i = 1; i <= numCols; i++)
			{
				retCode = SQLDescribeColA(hStmt, i, colName, 255, &colNameLen, &dataType, &columnSize, &numDecimalDigits, &allowsNullValues);
				if (CHECK(retCode, "SQLDescribeCol"))
				{
					colN = gcnew String((char *)colName);
					Console::WriteLine("Column #{0}: '{1}'",
						i, colN);
				}
			}
			Console::Write(L"\n");
			// retrieve data for each of the rows from the result set.
			for (int i = 1; i <= numRows; i++)
			{

				// Datatypes
				// SQLGetData
				char buf[256];
				SQLINTEGER numBytes;

				for (int j = 1; j <= numCols; j++)
				{
					retCode = SQLGetData(hStmt, j, SQL_C_CHAR, buf, 255, &numBytes);

					if (CHECK(retCode, "SqlGetData", false))
					{
						// print data retrieved
						bufN = gcnew String((char *)buf);
						Console::Write(L" {0,15}", bufN);
					}
				} // end for.

				  /*	Console::Write(L"\n");

				  retCode = SQLFetch(hStmt);
				  if (!SQL_SUCCEEDED(retCode))
				  {
				  Console::Write(L"The last row is {0} - no more data.\n\n\n", i);
				  }*/
			}
		}

		// free-up handles
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		SQLFreeHandle(SQL_HANDLE_DBC, hConn);
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

		// display status after query
		if (option == 1)
		{
			Console::WriteLine("\n");
			myEmployee.displayLastName();
			Console::WriteLine("'s attributes was retrieved successfully.\n");
		}
		else if (option == 2)
		{
			Console::WriteLine("\n");
			myEmployee.displayLastName();
			Console::WriteLine("'s ");
			myEmployee.displayAttribute();
			Console::WriteLine(" was changed to ");
			myEmployee.displayNewValue();
			Console::WriteLine(".\n");
		}
		else if (option == 3)
		{
			Console::WriteLine("\nRecord Created for ");
			myEmployee.displayLastName();
			Console::WriteLine(".\n");
		}
		else if (option == 4)
		{
			Console::WriteLine("\n");
			myDepartment.displayDepartmentName();
			Console::WriteLine("'s location was changed to ");
			myDepartment.displayDepartmentLocation();
			Console::WriteLine(".\n");
		}

	} while (option != 5); // end do...while loop, exit program
}
