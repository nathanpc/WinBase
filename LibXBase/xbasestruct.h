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
#include <cvector.h>

/**
 * Field descriptor array terminator flag.
 */
#define FIELD_DESC_ARRAY_TERM 0x0D

/**
 * Database magic code flag that denotes which kind of file we have.
 */
typedef enum
{
	DBF_FOXBASE         = 0x02,
	DBF_FILEWODBT       = 0x03,
	DBF_DBASEIV         = 0x04,
	DBF_DBASEV          = 0x05,
	DBF_VISOBJDBIII     = 0x07,
	DBF_VISFOXPRO       = 0x30,
	DBF_VISFOXPROAI     = 0x31,
	DBF_DBVMEMOVAR      = 0x43,
	DBF_DBASEIVMEMOSQL  = 0x7B,
	DBF_DBASEIIIMEMO    = 0x83,
	DBF_VISOBJDBIIIMEMO = 0x87,
	DBF_DBASEIVMEMO     = 0x8B,
	DBF_DBASEIVSQL      = 0x8E,
	DBF_DBVDBTMEMO      = 0xB3,
	DBF_CLIPPERMEMO     = 0xE5,
	DBF_FOXPROMEMO      = 0xF5,
	DBF_FOXPROUNKOWN    = 0xFB
} XBASE_SIGNATURE;

/**
 * Database language definitions for DbfHeader.ucLanguage.
 */
typedef enum
{
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
 * Data types definitions.
 */
typedef enum
{
	TYPE_CHARACTER = 'C',
	TYPE_NUMBER    = 'N',
	TYPE_LOGICAL   = 'L',
	TYPE_DATE      = 'D',
	TYPE_MEMO      = 'M',
	TYPE_FLOAT     = 'F'
} XBASE_DATATYPE;

/**
 * Database file header section definition.
 */
typedef struct
{
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
 * Database field descriptor definition.
 */
typedef struct
{
	char   sfzpName[11];
	char   cType;
	UINT32 ulMemoryAddress;
	UCHAR  ucLength;
	UCHAR  ucDecimalCount;
	UCHAR  ucaReserved0[2];
	UCHAR  ucWorkAreaID;
	UCHAR  ucaReserved1[2];
	UCHAR  ucSetFieldsFlag;
	UCHAR  ucaReserved[7];
	UCHAR  bIndexedField;
} DbfFieldDescriptor;

/**
 * Field descriptor array definition.
 */
typedef cvector_vector_type(DbfFieldDescriptor) VectorFieldDescriptors;

/**
 * xBase database handle.
 */
typedef struct
{
	FILE *hFile;
	
	DbfHeader dbfHeader;
	VectorFieldDescriptors vecFieldDescriptors;
} xBaseHandle;

#ifdef __cplusplus
}
#endif

#endif /* _XBASEDATA_H_ */
