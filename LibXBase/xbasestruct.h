/**
 * xbasedata.h
 * xBase data strutures.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _XBASEDATA_H_
#define _XBASEDATA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Database language definitions for DbfHeader.ucLanguage.
 */
typedef enum {
	LANG_DOS_USA   = 0x01,
	LANG_DOS_MULTI = 0x02,
	LANG_WIN_ANSI  = 0x03,
	LANG_MACINTOSH = 0x04,
	LANG_DOS_EE    = 0x64,
	LANG_DOS_NORD  = 0x65,
	LANG_DOS_RUS   = 0x66,
	LANG_DOS_ICEL  = 0x67,
	LANG_DOS_CZECH = 0x68,
	LANG_DOS_POL   = 0x69,
	LANG_DOS_GREEK = 0x6A,
	LANG_DOS_TURK  = 0x6B,
	LANG_MAC_RUS   = 0x96,
	LANG_MAC_EE    = 0x97,
	LANG_MAC_GREEK = 0x98,
	LANG_WIN_EE    = 0xC8,
	LANG_WIN_RUS   = 0xC9,
	LANG_WIN_TURK  = 0xCA,
	LANG_WIN_GREEK = 0xCB
} XBASE_LANG;

/**
 * Database file header section definition.
 */
typedef struct {
	UCHAR  ucVersion;
	UCHAR  ucaLastUpdate[3];
	UINT32 ulRecords;
	USHORT usHeaderLength;
	USHORT usRecordLength;
	UCHAR  usaReservedSpec[2];
	UCHAR  bIncompleteTrans;
	UCHAR  bEncrypted;
	UCHAR  ucaReservedMU[12];
	UCHAR  ucMdx;
	UCHAR  ucLanguage;  /* See XBASE_LANG */
	UCHAR  ucaReserved0[2];
} DbfHeader;

/**
 * xBase database handle.
 */
typedef struct {
	FILE *hFile;
	DbfHeader dbfHeader;
} xBaseHandle;

#ifdef __cplusplus
}
#endif

#endif /* _XBASEDATA_H_ */