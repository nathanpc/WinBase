/**
 * MsgBoxes.h
 * Some utility functions to work with Message Boxes more easily and write less
 * boilerplate for something that is so simple.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _MSGBOXES_H
#define _MSGBOXES_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

#include "stdafx.h"

// Generic message box.
int MsgBox(HWND hwndParent, UINT uType, LPCTSTR szTitle, LPCTSTR szText);

// Commonly used message boxes.
int MsgBoxError(HWND hwndParent, LPCTSTR szTitle, LPCTSTR szText);
int MsgBoxLastError(HWND hwndParent);

#ifdef  __cplusplus
}
#endif  // __cplusplus

#endif // _MSGBOXES_H
