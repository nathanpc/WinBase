/**
 * WinBase.h
 * A Windows database program that can read and write to xBase databases.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _WINBASE_H
#define _WINBASE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

// Instance operators.
ATOM RegisterApplication(HINSTANCE hInstance);
HWND InitializeInstance(HINSTANCE hInstance,
						LPTSTR lpCmdLine,
						int nCmdShow);
int TerminateInstance(HINSTANCE hInstance,
					  int nDefRC);

// Window procedure.
LRESULT CALLBACK MainWindowProc(HWND hWnd,
								UINT wMsg,
								WPARAM wParam,
								LPARAM lParam);
LRESULT CALLBACK AboutDlgProc(HWND hDlg,
							  UINT wMsg,
							  WPARAM wParam,
							  LPARAM lParam);

// Window message handlers.
LRESULT WndMainCreate(HWND hWnd,
					  UINT wMsg,
					  WPARAM wParam,
					  LPARAM lParam);
LRESULT WndMainCommand(HWND hWnd,
					   UINT wMsg,
					   WPARAM wParam,
					   LPARAM lParam);
LRESULT WndMainNotify(HWND hWnd,
					  UINT wMsg,
					  WPARAM wParam,
					  LPARAM lParam);
LRESULT WndMainClose(HWND hWnd,
					 UINT wMsg,
					 WPARAM wParam,
					 LPARAM lParam);
LRESULT WndMainDestroy(HWND hWnd,
					   UINT wMsg,
					   WPARAM wParam,
					   LPARAM lParam);

// Database operations.
BOOL OpenDatabase(LPCTSTR szPath);
BOOL CloseDatabase(void);

#endif // _WINBASE_H
