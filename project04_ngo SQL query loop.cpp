/*****

******

** Author: Ngo, Clark Jason

** Assignment: Project 4 (Database Design)

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
using namespace System;
#pragma comment( lib, "odbc32.lib" )

// error check function
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

// status check function
void status(SQLSMALLINT handleType, SQLHANDLE theHandle, int line)
{
	SQLCHAR sqlState[6];
	SQLINTEGER nativeError;
	SQLCHAR msgStr[256];
	SQLSMALLINT overBy;
	SQLRETURN retCode;

	for (int i = 1; i < 20; i++)
	{
		retCode = SQLGetDiagRecA(handleType, theHandle, i,

			// Specify status message you want to get.  
			// http://msdn.microsoft.com/en-us/library/ms716256(VS.85).aspx
			sqlState,		// Gives back 5 characters (HY*** style error code)
			&nativeError,	// numerical error number
			msgStr,			// buffer to store the description of the error. Most important 


			255,         // the number of characters in msgStr, so that
						 // the function doesn't do a buffer overrun in case it
						 // has A LOT to tell you
			&overBy      // again in case the function has A LOT to tell you,
						 // the 255 character size buffer we passed might not be large
						 // enough to hold the entire error message.  If that happens
						 // the error message will truncate and the 'overBy' variable
						 // will have a value > 0 (it will measure number of characters
						 // that you 'missed seeing' in the error message).

		);

		if (CHECK(retCode, "SQLGetDiagRecA"))
		{
			printf("LINE %d:  [%s][%d] %s\n", line, sqlState, nativeError, msgStr);
		}
		else
		{
			// Stop looping when retCode comes back
			// as a failure, because it means there are
			// no more messages to tell you
			break;
		}
	}
}

int main()
{
	// create handle for the environment.
	SQLHANDLE hEnv;
	SQLRETURN retCode;

	// allocate handle for environment
	retCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	CHECK(retCode, "allocate environment handle");

	// set environment
	retCode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	CHECK(retCode, "setting the environment attribute setting to ODBC version 3");


	// create handle for connection
	SQLHANDLE hConn;
	CHECK(SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn), "allocate handle");

	// connect to the database
	SQLCHAR* dsnName = (SQLCHAR*)"mysqlstuff"; 
	SQLCHAR* userid = (SQLCHAR*)"clarkngo";
	SQLCHAR* password = (SQLCHAR*)"May092017";

	// allocate handle for connection
	retCode = SQLConnectA(hConn, dsnName, SQL_NTS, userid, SQL_NTS, password, SQL_NTS );

	// check database connection
	if (!CHECK(retCode, "SqlConnectA", false))
	{	// status function is defined above.
		status(SQL_HANDLE_DBC, hConn, __LINE__);
	}

	// declare variable option
	int option;

	do // loop until Exit with "4";
	{
		// create handle for statement
		SQLHANDLE hStmt;
		CHECK(SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt), "allocate handle for statement");

		// prompt user
		Console::Write(L"1) Enter an employee last name to retrieve first name, home address and work phone number\n");
		Console::Write(L"2) Enter an employee last name to retrieve a department\n");
		Console::Write(L"3) Enter a department to retrieve a list comprising employee\n");
		Console::Write(L"\tlast names, addresses and work phone numbers for those in that department\n");
		Console::Write(L"4) Exit program\n");
		Console::Write(L"Enter number of chosen option\n");


		do // limit user to options 1-4
		{
			Console::Write(L"Enter numbers 1-4 only:\n");
			String^temp = Console::ReadLine();
			option = int::Parse(temp);

		} while (option > 4 || option < 0);

		// break to exit loop
		if (option == 4)
			break;		

		Console::WriteLine("Please enter text: ");
		char buffer[1024] = { 0, };

		// input last name / department name
		String^ text = Console::ReadLine();

		// sprintf_s to store series of characters in buffer
		// renamed department to d
		// renamed employee to e
		if (option == 1)
			sprintf_s(buffer,		
				"SELECT firstName, homeAddress, workPhoneNumber FROM employee WHERE lastName ='%s'", text);
		else if (option == 2)
			sprintf_s(buffer,
				"SELECT departmentName FROM department d INNER JOIN employee e ON e.departmentID = d.departmentID WHERE e.lastName = '%s'", text);
		else if (option == 3)
			sprintf_s(buffer,
				"SELECT lastName, homeAddress, workPhoneNumber FROM employee e INNER JOIN department d ON d.departmentID =  e.departmentID WHERE d.departmentName ='%s'", text);
		else
			return 0;

		// execute query
		SQLCHAR* query = (SQLCHAR*)buffer;

		CHECK(SQLExecDirectA(hStmt, query, SQL_NTS), "execute query");


		// read data results that are now in the hStmt.
		retCode = SQLFetch(hStmt);
		CHECK(retCode, "first sqlFetch");

		// returns total rows
		SQLLEN numRows;
		retCode = SQLRowCount(hStmt, &numRows);
		Console::WriteLine("{0} rows were fetched.\n", numRows);


		SQLSMALLINT numCols;
		retCode = SQLNumResultCols(hStmt, &numCols); 
		SQLCHAR colName[256];
		System::String^ colN;
		System::String^ bufN;

		SQLSMALLINT colNameLen, dataType, numDecimalDigits, allowsNullValues;
		SQLUINTEGER columnSize;

		// column names
		for (int i = 1; i <= numCols; i++)
		{
			retCode = SQLDescribeColA(hStmt, i, colName, 255, &colNameLen, &dataType, &columnSize, &numDecimalDigits, &allowsNullValues);
			if (CHECK(retCode, "SQLDescribeCol"))
			{
				colN = gcnew String((char *)colName);
				Console::WriteLine("Column #{0}: '{1}' , datatype={2} size={3} decimaldigits={4} nullable={5}",
					i, colN, dataType, columnSize, numDecimalDigits, allowsNullValues);
			}
		}

		// loop data retrieval
		for (int i = 1; i <= numRows; i++)
		{
			char buf[256];
			SQLINTEGER numBytes;

			for (int j = 1;	j <= numCols; j++)
			{
				retCode = SQLGetData(hStmt,j, SQL_C_CHAR, buf, 255, &numBytes);

				if (CHECK(retCode, "SqlGetData", false))
				{
					// print the data retrieved
					bufN = gcnew String((char *)buf);
					Console::Write(L" {0,20}", bufN);
				}
			} // end for.

			Console::Write(L"\n");

			// fetch results until no more data
			retCode = SQLFetch(hStmt);
			if (!SQL_SUCCEEDED(retCode))
			{
				Console::Write(L"The last row is {0} - no more data.\n\n\n", i);
				// User input for termination.
			}
		}

		// Free up resources.
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		SQLFreeHandle(SQL_HANDLE_DBC, hConn);
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	} while (option != 4); // end do...while loop, exit program
}