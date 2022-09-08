/**
 * DataGridView.cpp
 * A ListView control with a bit more abstraction to enable us to more easily
 * work with "grid data".
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "DataGridView.h"

/**
 * Blank control constructor that does nothing.
 */
DataGridView::DataGridView()
{
	this->lphInstance = NULL;
	this->lphwndParent = NULL;
	this->nColumns = 0;
	this->nRows = 0;
}

/**
 * Creates a DataGridView control and fills in the window.
 *
 * @param lphInstance  Current application's instance.
 * @param lphwndParent Parent window that will be filled with the control.
 */
DataGridView::DataGridView(HINSTANCE *lphInstance,
						   HWND *lphwndParent)
{
	this->lphInstance = lphInstance;
	this->lphwndParent = lphwndParent;
	this->nColumns = 0;
	this->nRows = 0;

	this->InitializeControl();
}

/**
 * Initializes the ListView control.
 *
 * @return TRUE if the operation was successful.
 */
BOOL DataGridView::InitializeControl()
{
	RECT rcClient;

	// Get the parent window size so we can fill it with our control.
	GetClientRect(*this->lphwndParent, &rcClient);

	// Create the ListView control window.
	this->hWnd = CreateWindow(
		WC_LISTVIEW, 
		TEXT(""),
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS,
		0, 0,
		rcClient.right - rcClient.left,
		rcClient.bottom - rcClient.top,
		*this->lphwndParent,
		NULL,
		*this->lphInstance,
		NULL);

	// Add some extended attributes to the ListView control.
	SendMessage(this->hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Check if the window creation was successful.
	if (!this->hWnd)
		return FALSE;
	
	return TRUE;
}

/**
 * Add a column to the ListView.
 *
 * @param szCaption Caption text of column.
 * @param lColWidth Column width in pixels.
 *
 * @return TRUE if the operation was successful.
 */
BOOL DataGridView::AddColumn(LPTSTR szCaption,
							 LONG lColWidth)
{
	LVCOLUMN lvc = { 0 };

	// Setup the LVCOLUMN structure.
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.iSubItem = this->nColumns;
	lvc.pszText = szCaption;
	lvc.cx = lColWidth;
	lvc.fmt = LVCFMT_LEFT;

	// Insert the column into the ListView control.
	return ListView_InsertColumn(this->hWnd, this->nColumns++, &lvc) != -1;
}

/**
 * Adds an item (row) to the ListView.
 *
 * @param szaFields Vector of strings (each field) to put in the row. This MUST
 *                  have the same number of elements as there are columns.
 *
 * @return TRUE if the operation was successful.
 */
BOOL DataGridView::AddItem(std::vector<LPTSTR> szaFields)
{
	LVITEM lvItem = { 0 };

	// Check if the vector has the correct size.
	if (szaFields.size() != this->nColumns)
		return FALSE;

	// Initialize LVITEM members that are common to all items.
	lvItem.mask = LVIF_TEXT | LVIF_STATE;
	lvItem.iSubItem = 0;
	lvItem.stateMask = 0;
	lvItem.state = 0;

	// Setup and insert the first list view item.
	lvItem.iItem = this->nRows;
	lvItem.pszText = szaFields[0];
	if (ListView_InsertItem(this->hWnd, &lvItem) == -1)
		return FALSE;
	//LocalFree(lvItem.pszText);

	// Insert the sub-items into the list view.
	for (int i = 1; i < this->nColumns; i++)
	{
		ListView_SetItemText(this->hWnd, this->nRows, i, szaFields[i]);
		//LocalFree(szText);
	}

	// Advance the row number.
	this->nRows++;

	return TRUE;
}
