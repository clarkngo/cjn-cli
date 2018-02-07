// MyDBtest.cpp: main project file.

//  Based on an example from Bobobobo's Weblog 
// at: http://bobobobo.wordpress.com/2009/07/11/working-with-odbc-from-c/
// Modified for Visual C++ 2013 using CLI.

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

using namespace System;

// link with odbc32.lib
#pragma comment( lib, "odbc32.lib" )

// If we get an error message, print it.  
// Print success or fail if desired. Handle error if desired.

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

// status(): Find the status code.  Tricky.
void status(SQLSMALLINT handleType, SQLHANDLE theHandle, int line)
{
	SQLCHAR sqlState[6];
	SQLINTEGER nativeError;
	SQLCHAR msgStr[256];
	SQLSMALLINT overBy; // the number of characters that msgStr buffer was too short.
						// http://msdn.microsoft.com/en-us/library/ms716256(VS.85).aspx
						// Requires 8 parameters.
						// More "GetMeStatus()" function than "GetLastError()" function.

	SQLRETURN retCode;

	for (int i = 1; i < 20; i++)
	{
		retCode = SQLGetDiagRecA(

			handleType,  // type of object for which you're checking the status.
			theHandle,   // handle to the actual object for which you want the status.

			i,

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
	// Following this example, just adding a bit more
	// color and making it work with our specific example.

	// 1.  Create a handle for the environment.
	SQLHANDLE hEnv;
	SQLRETURN retCode;

	retCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	CHECK(retCode, "allocate environment handle");

	// 2.  Next, set the version of ODBC to use to ODBC version 3.
	// Format of this command is a bit weird, we cast the value we're passing
	// to (void*) because the function requires it, but then we say that the
	// length of the "string" we've passed in is 0 characters long, so I assume
	// that means SQLSetEnvAttr should know to interpret the "pointer value" that
	// we passed in as actually an integer value (which is what it is).
	retCode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	CHECK(retCode, "setting the environment attribute setting to ODBC version 3");


	// 3.  Allocate the connection handle.  
	// Note that this doesn't connect us to the database yet.  
	SQLHANDLE hConn;
	CHECK(SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn), "allocate handle");

	// Actually connect to the database.
	SQLCHAR* dsnName = (SQLCHAR*)"mySQLservice";  // MUST BE THE SAME
												  // as the name of the ODBC data source you set
												  // in the Microsoft ODBC Administrator window.

	SQLCHAR* userid = (SQLCHAR*)"";
	SQLCHAR* password = (SQLCHAR*)"";
	// using a BLANK userid and password since it is set in the ODBC connection.

	// 4.  Open database connection.
	retCode = SQLConnectA(

		hConn,

		dsnName,  // name of data source we are connecting to,
				  // as registered IN ODBC Data Source Administrator.

				  // If you are on a 64-bit machine, and you
				  // DO NOT USE THE 64-bit driver.  As long as
				  // your compiler publishes a 32-bit .exe (which
				  // Visual Studio does), you'll keep getting:

				  // [Microsoft][ODBC Driver Manager] Data source name not found and no default driver specified

				  // SO DON'T USE THE 64-BIT DRIVERS!  Instead, install
				  // the 32-bit driver, and then manage / use the 32-bit datasources, located in:
				  // c:\windows\syswow64\odbcad32.exe

				  // http://stackoverflow.com/questions/949959/why-do-64bit-dlls-go-to-system32-and-32bit-dlls-to-syswow64-on-64bit-windows
				  // http://blogs.sepago.de/helge/2008/04/20/windows-x64-all-the-same-yet-very-different-part-7/

		SQL_NTS,  // the DSN name is a NULL TERMINATED STRING, so "count it yourself"

		userid,
		SQL_NTS,  // userid is a null-terminated string

		password,
		SQL_NTS   // password is a null terminated string

	);

	if (!CHECK(retCode, "SqlConnectA", false))
	{

		// if this fails, this provides extra status
		// information about why the failure happened.
		// status function is defined above.
		status(SQL_HANDLE_DBC, hConn, __LINE__);
	}

	// 6.  Create and allocate a handle.
	SQLHANDLE hStmt;
	CHECK(SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt), "allocate handle for statement");

	// 7.  Form a query to run and attach it to the hStmt
	// This connects the hStmt to some results.
	SQLCHAR* query = (SQLCHAR*)"SELECT * from city";
	CHECK(SQLExecDirectA(hStmt, query, SQL_NTS), "execute query");


	// 8.  Read data results that are now in the hStmt.
	retCode = SQLFetch(hStmt);
	CHECK(retCode, "first sqlFetch");

	// How many rows got returned?
	SQLLEN numRows;
	retCode = SQLRowCount(hStmt, &numRows);
	Console::WriteLine("{0} rows were fetched.\n", numRows);

	// With a query like the one we wrote (SELECT *),
	// we don't know how many columns should be in
	// the result set at this point.
	// So we ask ODBC to tell us!
	SQLSMALLINT numCols;
	retCode = SQLNumResultCols(hStmt, &numCols); // SqlNumResultCols

												 // Now print the column names.
												 // SQLDescribeCol function
	SQLCHAR colName[256];
	System::String^ colN;
	System::String^ bufN;

	SQLSMALLINT colNameLen, dataType, numDecimalDigits, allowsNullValues;
	SQLUINTEGER columnSize;

	for (int i = 1; i <= numCols; i++)
	{
		retCode = SQLDescribeColA(hStmt, i, colName, 255, &colNameLen, &dataType, &columnSize, &numDecimalDigits, &allowsNullValues);
		if (CHECK(retCode, "SQLDescribeCol"))
		{
			// We typecast colName from an SQLCHAR to a regular char pointer
			// and then create a CLI string object from it.
			// This same conversion can be used if we want to work with string data from our database.
			colN = gcnew String((char *)colName);
			Console::WriteLine("Column #{0}: '{1}' , datatype={2} size={3} decimaldigits={4} nullable={5}",
				i, colN, dataType, columnSize, numDecimalDigits, allowsNullValues);
		}
	}

	// Now get the data for each of the rows from the result set.
	for (int i = 1; i <= numRows; i++)
	{

		// Datatypes
		// SQLGetData
		char buf[256];
		SQLINTEGER numBytes;

		for (int j = 1;		// column counter starts at 1, not 0.
			j <= numCols;   // numCols retrieved above
			j++)
		{
			retCode = SQLGetData(

				hStmt,
				j,           // COLUMN NUMBER of the data to get
				SQL_C_CHAR,  // the data type that you expect to receive
				buf,         // the place to put the data that you expect to receive
				255,         // the size in bytes of buf (-1 for null terminator)
				&numBytes    // size in bytes of data returned

			);

			if (CHECK(retCode, "SqlGetData", false))
			{
				// Print the data we got.
				bufN = gcnew String((char *)buf);
				Console::Write(L" {0,10}", bufN);
			}
		} // end for.

		Console::Write(L"\n");

		// Try and fetch the next result.
		// fall out of the loop if fetch fails
		// (meaning, no more data to get)
		retCode = SQLFetch(hStmt);
		if (!SQL_SUCCEEDED(retCode))
		{
			// SQLFetch FAILS AS IT FETCHES the last row of data.
			Console::Write(L"The last row is {0} - no more data.\n", i);
			// User input for termination.
			Console::ReadLine();
		}
	}

	// A FOR loop was used to fetch exactly numRows rows from the results.
	// Another (more common?) way to do this is to use a while loop, like:

	// while( SQL_SUCCEEDED( SQLFetch( hStmt ) ) )
	// {
	//		Work with result data
	// }

	// With the WHILE loop, we rely on SQLFetch to fail last row is reached.

	// Free up resources.
	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, hConn);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}