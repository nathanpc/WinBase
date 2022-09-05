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
	UCHAR ucFlag;

	/* Open the file. */
	hndBase->hFile = _tfopen(szDbfPath, TEXT("r+b"));
	if (hndBase->hFile == NULL)
		return FALSE;

	/* Read the database header. */
	ulReadSize = fread(&hndBase->dbfHeader, sizeof(DbfHeader), 1, hndBase->hFile);
	if (ulReadSize != 1)
		return FALSE;

	/* Populate the field descriptors. */
	hndBase->vecFieldDescriptors = NULL;
	ucFlag = 0;
	while (ucFlag != FIELD_DESC_ARRAY_TERM)
	{
		/* Try to get the terminator flag. */
		ulReadSize = fread(&ucFlag, 1, 1, hndBase->hFile);
		if (ulReadSize != 1)
			return FALSE;

		/* Check if we actually have a field descriptor. */
		if (ucFlag != FIELD_DESC_ARRAY_TERM)
		{
			DbfFieldDescriptor fldDesc;

			/* Go back from the flag that we've checked. */
			fseek(hndBase->hFile, -1, SEEK_CUR);

			/* Read the field descriptor structure. */
			ulReadSize = fread(&fldDesc, sizeof(DbfFieldDescriptor), 1, hndBase->hFile);
			if (ulReadSize != 1)
				return FALSE;

			/* Push the field descriptor into the array. */
			cvector_push_back(hndBase->vecFieldDescriptors, fldDesc);
		}
	}

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
	/* Close file handle. */
	fclose(hndBase->hFile);
	hndBase->hFile = NULL;

	/* Free up the field descriptor array. */
	cvector_free(hndBase->vecFieldDescriptors);

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
		case DBF_FOXBASE:
			return TEXT("FoxBase");
		case DBF_FILEWODBT:
			return TEXT("File without DBT");
		case DBF_DBASEIV:
			return TEXT("dBASE IV");
		case DBF_DBASEV:
			return TEXT("dBASE V");
		case DBF_VISOBJDBIII:
			return TEXT("Visual Objects for dBASE III");
		case DBF_VISFOXPRO:
			return TEXT("Visual FoxPro");
		case DBF_VISFOXPROAI:
			return TEXT("Visual FoxPro (with Auto Increment)");
		case DBF_DBVMEMOVAR:
			return TEXT("DBV Memo Variable Size");
		case DBF_DBASEIVMEMOSQL:
			return TEXT("dBASE IV (with Memo)");
		case DBF_DBASEIIIMEMO:
			return TEXT("dBASE III+ (with Memo)");
		case DBF_VISOBJDBIIIMEMO:
			return TEXT("Visual Objects for dBASE III (with Memo)");
		case DBF_DBASEIVMEMO:
			return TEXT("dBASE IV (with Memo)");
		case DBF_DBASEIVSQL:
			return TEXT("dBASE IV (with SQL)");
		case DBF_DBVDBTMEMO:
			return TEXT("DBV and DBT Memo");
		case DBF_CLIPPERMEMO:
			return TEXT("Clipper SIX (with SMT Memo)");
		case DBF_FOXPROMEMO:
			return TEXT("FoxPro (with Memo)");
		case DBF_FOXPROUNKOWN:
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

/**
 * Checks if there is an incomplete (pending) transaction in this database.
 *
 * @param dbfHeader Header of a database.
 *
 * @return Is there any transaction pending?
 */
LIBXBASE_API BOOL xBaseIsTransactionPending(const DbfHeader *dbfHeader)
{
	return (BOOL)dbfHeader->bIncompleteTrans;
}

/**
 * Checks if the database is encrypted.
 *
 * @param dbfHeader Header of a database.
 *
 * @return Is the database encrypted?
 */
LIBXBASE_API BOOL xBaseIsEncrypted(const DbfHeader *dbfHeader)
{
	return (BOOL)dbfHeader->bEncrypted;
}

/**
 * Gets the number of field descriptors in the database.
 *
 * @param hndBase Database handle to be inspected.
 *
 * @return Number of field descriptors in the database.
 */

LIBXBASE_API size_t xBaseFieldDescCount(const xBaseHandle *hndBase)
{
	return cvector_size(hndBase->vecFieldDescriptors);
}

/**
 * Gets a field descriptor at a position.
 *
 * @param hndBase Database handle to be inspected.
 * @param ulIndex Index to fetch the field descriptor.
 *
 * @return Requested field descriptor.
 */
LIBXBASE_API DbfFieldDescriptor* xBaseGetFieldDescAt(const xBaseHandle *hndBase,
													 size_t ulIndex)
{
	return &hndBase->vecFieldDescriptors[ulIndex];
}

/**
 * Gets the field descriptor name in a properly NULL terminated string.
 *
 * @param fldDesc Field descriptor structure.
 * @param szName  String that should hold exactly 12 characters including the
 *                NULL terminator.
 */
LIBXBASE_API void xBaseGetFieldDescName(const DbfFieldDescriptor *fldDesc,
										LPTSTR szName)
{
	UCHAR i;

	/* Preemptively NULL terminate the string. */
	szName[11] = TEXT('\0');

	/* Copy the name over ensuring we convert to TCHAR. */
	for (i = 0; i <= 10; i++)
	{
		szName[i] = (TCHAR)fldDesc->sfzpName[i];
	}
}

/**
 * Gets the field descriptor data type in a human-readable format.
 *
 * @param fldDesc Field descriptor structure.
 * 
 * @return Human-readable string of the data type.
 */
LIBXBASE_API LPCTSTR xBaseGetFieldDescTypeStr(const DbfFieldDescriptor *fldDesc)
{
	switch (fldDesc->cType)
	{
		case TYPE_CHARACTER:
			return TEXT("Character");
		case TYPE_NUMBER:
			return TEXT("Number");
		case TYPE_LOGICAL:
			return TEXT("Logical");
		case TYPE_DATE:
			return TEXT("Date");
		case TYPE_MEMO:
			return TEXT("Memo");
		case TYPE_FLOAT:
			return TEXT("Floating Point");
		default:
			return TEXT("Unknown");
	}
}
