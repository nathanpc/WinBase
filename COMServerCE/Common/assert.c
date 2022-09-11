/**
 * assert.h
 * Definition of the assert macro that is absent in eVC++.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

void __cdecl _assert(void *exp, void *file, unsigned int line)
{
	TCHAR szMsg[255];

	_stprintf(szMsg, TEXT("ASSERT FAILED: [%s:%u] %s\r\n"),
		(TCHAR *)file, line, (TCHAR *)exp);
	OutputDebugString(szMsg);

	exit(1);
}
