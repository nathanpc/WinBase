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


// This is an example of an exported variable
LIBXBASE_API int nLibXBase = 123;

// This is an example of an exported function.
LIBXBASE_API int fnLibXBase(void)
{
	return 42;
}
