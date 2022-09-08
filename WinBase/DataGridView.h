/**
 * DataGridView.h
 * A ListView control with a bit more abstraction to enable us to more easily
 * work with "grid data".
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _DATAGRIDVIEW_H
#define _DATAGRIDVIEW_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include <vector>

class DataGridView
{
	protected:
		HWND hWnd;
		HINSTANCE *lphInstance;
		HWND *lphwndParent;
		int nColumns;
		int nRows;

		BOOL InitializeControl();

	public:
		// Contructors and Destructors
		DataGridView();
		DataGridView(HINSTANCE *lphInstance,
					 HWND *lphwndParent);

		// Control operations.
		BOOL AddColumn(LPTSTR szCaption,
					   LONG lColWidth);
		BOOL AddItem(std::vector<LPTSTR> szaFields);
};

#endif // _DATAGRIDVIEW_H
