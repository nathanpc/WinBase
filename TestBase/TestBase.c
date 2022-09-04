/**
 * TestBase.c
 * A simple console program meant to automatically and quickly test the library
 * code that we wrote in LibXBase.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "stdafx.h"
#include <LibXBase.h>

/* Function Prototypes */
void PrintHeader(DbfHeader *dbfHeader);

/**
 * Program's main entry point.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Command-line arguments passed to the program.
 *
 * @return 0 if the program exited successfully.
 */
int main(int argc, char* argv[])
{
	xBaseHandle hndDB;

	_tprintf(TEXT("WinBase Test!\r\n\r\n"));

	/* Open the database. */
	if (!xBaseOpen(&hndDB, TEXT("C:\\TESTDB\\TEST.DBF")))
	{
		_tprintf(TEXT("An error occurred in xBaseOpen()\r\n"));
		return 1;
	}

	/* Print out its header. */
	PrintHeader(&hndDB.dbfHeader);

	xBaseClose(&hndDB);
	system("pause");
	return 0;
}

/**
 * Prints the header of a database in a human-readable format.
 *
 * @param dbfHeader Header to be printed out.
 */
void PrintHeader(DbfHeader *dbfHeader)
{
	TCHAR szLastUpdated[11];

	_tprintf(TEXT("Version: %s\r\n"), xBaseGetDBVersionName(dbfHeader));
	xBaseGetLastUpdatedStr(dbfHeader, szLastUpdated);
	_tprintf(TEXT("Last Updated: %s\r\n"), szLastUpdated);
	_tprintf(TEXT("Number of Records: %u\r\n"), xBaseGetNumberRecords(dbfHeader));
	_tprintf(TEXT("Pending Transactions: %s\r\n"),
		(xBaseIsTransactionPending(dbfHeader) ? TEXT("YES") : TEXT("NO")));
	_tprintf(TEXT("Database Encrypted: %s\r\n"),
		(xBaseIsEncrypted(dbfHeader) ? TEXT("YES") : TEXT("NO")));
}

