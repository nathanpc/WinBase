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
void PrintFieldDescriptor(DbfFieldDescriptor *fldDesc);

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
	_tprintf(TEXT("\r\n"));

	/* Print out the field descriptors. */
	if (hndDB.vecFieldDescriptors)
	{
		size_t i;
		for (i = 0; i < cvector_size(hndDB.vecFieldDescriptors); i++)
		{
			_tprintf(TEXT("[%u] "), i);
			PrintFieldDescriptor(&hndDB.vecFieldDescriptors[i]);
			_tprintf(TEXT("\r\n"));
		}
	}

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

/**
 * Prints the information contained in a field descriptor.
 *
 * @param fldDesc Field descriptor to be printed out.
 */
void PrintFieldDescriptor(DbfFieldDescriptor *fldDesc)
{
	TCHAR szName[12];

	xBaseGetFieldDescName(fldDesc, szName);
	_tprintf(TEXT("(%s) %s\r\n"), xBaseGetFieldDescTypeStr(fldDesc), szName);
	_tprintf(TEXT("Memory Address: %u\r\n"), fldDesc->ulMemoryAddress);
	_tprintf(TEXT("Length: %u\r\n"), fldDesc->ucLength);
	_tprintf(TEXT("Decimal Count: %u\r\n"), fldDesc->ucDecimalCount);
	_tprintf(TEXT("Work Area ID: %u\r\n"), fldDesc->ucWorkAreaID);
	_tprintf(TEXT("Set Fields Flag: %u\r\n"), fldDesc->ucSetFieldsFlag);
	_tprintf(TEXT("Indexed Field: %s\r\n"), ((fldDesc->bIndexedField) ? TEXT("YES") : TEXT("NO")));
}

