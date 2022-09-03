/**
 * TestBase.c
 * A simple console program meant to automatically and quickly test the library
 * code that we wrote in LibXBase.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "stdafx.h"
#include <LibXBase.h>

int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	printf("nLibXBase = %d\r\n", nLibXBase);
	printf("fnLibXBase = %d\r\n", fnLibXBase());

	system("pause");
	return 0;
}

