/**
 * LibXBase.h
 * xBase Read/Write library for WinBase.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _LIBXBASE_H_
#define _LIBXBASE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* The following ifdef block is the standard way of creating macros which make
   exporting from a DLL simpler. All files within this DLL are compiled with
   the LIBXBASE_EXPORTS symbol defined on the command line. this symbol should
   not be defined on any project that uses this DLL. This way any other project
   whose source files include this file see LIBXBASE_API functions as being
   imported from a DLL, wheras this DLL sees symbols defined with this macro as
   being exported.*/
#ifdef LIBXBASE_EXPORTS
#define LIBXBASE_API __declspec(dllexport)
#else
#define LIBXBASE_API __declspec(dllimport)
#endif

#include <tchar.h>
#include "xbasestruct.h"

/* Handle Operations */
LIBXBASE_API BOOL xBaseOpen(xBaseHandle *hndBase,
							LPTSTR szDbfPath);
LIBXBASE_API BOOL xBaseClose(xBaseHandle *hndBase);

/* Header Getters */
LIBXBASE_API LPCTSTR xBaseGetDBVersionName(const DbfHeader *dbfHeader);
LIBXBASE_API void xBaseGetLastUpdatedStr(const DbfHeader *dbfHeader,
										 LPTSTR szDate);
LIBXBASE_API UINT32 xBaseGetNumberRecords(const DbfHeader *dbfHeader);
LIBXBASE_API BOOL xBaseIsTransactionPending(const DbfHeader *dbfHeader);
LIBXBASE_API BOOL xBaseIsEncrypted(const DbfHeader *dbfHeader);

/* Field Descriptor Helpers */
LIBXBASE_API size_t xBaseFieldDescCount(const xBaseHandle *hndBase);
LIBXBASE_API DbfFieldDescriptor* xBaseGetFieldDescAt(const xBaseHandle *hndBase,
													 size_t ulIndex);
LIBXBASE_API void xBaseGetFieldDescName(const DbfFieldDescriptor *fldDesc,
										LPTSTR szName);
LIBXBASE_API LPCTSTR xBaseGetFieldDescTypeStr(const DbfFieldDescriptor *fldDesc);

#ifdef __cplusplus
}
#endif

#endif /* _LIBXBASE_H_ */
