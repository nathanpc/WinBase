/**
 * LibXBase.c
 * xBase Read/Write library for WinBase.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "stdafx.h"
#include "LibXBase.h"

/**
 * Library's entry point.
 *
 * @param hModule    The handle for this library.
 * @param dwReason   Reason for being called.
 * @param lpReserved Reserved.
 *
 * @return TRUE if everything went fine.
 */
BOOL APIENTRY DllMain(HANDLE hModule, 
                      DWORD  dwReason, 
                      LPVOID lpReserved)
{
    switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }

    return TRUE;
}

/**
 * Opens an xBase database.
 *
 * @param hndBase   Pointer to the handle that will contain the database.
 * @param szDbfPath Path to the xBase *.dbf file you wish to open.
 *
 * @return TRUE if the operation was successful.
 */
LIBXBASE_API BOOL xBaseOpen(xBaseHandle *hndBase,
							LPTSTR szDbfPath)
{
	size_t ulReadSize;

	/* Open the file. */
	hndBase->hFile = _tfopen(szDbfPath, TEXT("r+b"));
	if (hndBase->hFile == NULL)
		return FALSE;

	/* Read the database header. */
	ulReadSize = fread(&hndBase->dbfHeader, sizeof(DbfHeader), 1, hndBase->hFile);
	if (ulReadSize != 1)
		return FALSE;

	return TRUE;
}

/**
 * Closes an xBase database.
 *
 * @param hndBase Database handle to be closed.
 *
 * @return TRUE if the operation was successful.
 */
LIBXBASE_API BOOL xBaseClose(xBaseHandle *hndBase)
{
	fclose(hndBase->hFile);
	hndBase->hFile = NULL;

	return TRUE;
}

/**
 * Gets the version string of a database.
 *
 * @param dbfHeader Header of a database.
 *
 * @return String representation of the database version.
 */
LIBXBASE_API LPCTSTR xBaseGetDBVersionName(const DbfHeader *dbfHeader)
{
	switch (dbfHeader->ucVersion)
	{
		case 0x02:
			return TEXT("FoxBase");
		case 0x03:
			return TEXT("File without DBT");
		case 0x04:
			return TEXT("dBASE IV");
		case 0x05:
			return TEXT("dBASE V");
		case 0x07:
			return TEXT("Visual Objects for dBASE III");
		case 0x30:
			return TEXT("Visual FoxPro");
		case 0x31:
			return TEXT("Visual FoxPro (with Auto Increment)");
		case 0x43:
			return TEXT("DBV Memo Variable Size");
		case 0x7B:
			return TEXT("dBASE IV (with Memo)");
		case 0x83:
			return TEXT("dBASE III+ (with Memo)");
		case 0x87:
			return TEXT("Visual Objects for dBASE III (with Memo)");
		case 0x8B:
			return TEXT("dBASE IV (with Memo)");
		case 0x8E:
			return TEXT("dBASE IV (with SQL)");
		case 0xB3:
			return TEXT("DBV and DBT Memo");
		case 0xE5:
			return TEXT("Clipper SIX (with SMT Memo)");
		case 0xF5:
			return TEXT("FoxPro (with Memo)");
		case 0xFB:
			return TEXT("FoxPro (Unknown)");
		default:
			return TEXT("Unknown");
	}
}

/**
 * Gets the Last Updated value as a string in ISO-8601 format.
 *
 * @param dbfHeader Header of a database.
 * @param szDate    Pointer to a string that will contain the date and can hold
 *                  11 characters including the NULL terminator.
 */
LIBXBASE_API void xBaseGetLastUpdatedStr(const DbfHeader *dbfHeader,
										 LPTSTR szDate)
{
	_stprintf(szDate, "%04u-%02u-%02u", 1900 + dbfHeader->ucaLastUpdate[0],
		dbfHeader->ucaLastUpdate[1], dbfHeader->ucaLastUpdate[2]);
}

/**
 * Gets the number of records contained in a database.
 *
 * @param dbfHeader Header of a database.
 *
 * @return Amount of records in the database. 
 */
LIBXBASE_API UINT32 xBaseGetNumberRecords(const DbfHeader *dbfHeader)
{
	return dbfHeader->ulRecords;
}
