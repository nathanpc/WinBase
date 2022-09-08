/**
 * WinBase.cpp
 * A Windows database program that can read and write to xBase databases.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "stdafx.h"
#include "resource.h"
#include "WinBase.h"
#include "MsgBoxes.h"
#include "DataGridView.h"

#define MAX_LOADSTRING 100

// Global variables.
HINSTANCE hInst;
HWND hwndMain;
TCHAR szWindowClass[MAX_LOADSTRING];
TCHAR szAppTitle[MAX_LOADSTRING];
DataGridView ctrlGridView;

/**
 * Application's main entry point.
 *
 * @param hInstance     Program instance.
 * @param hPrevInstance Ignored: Leftover from Win16.
 * @param lpCmdLine     String with command line text.
 * @param nShowCmd      Initial state of the program's main window.
 *
 * @return wParam of the WM_QUIT message.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR lpCmdLine,
					 int nCmdShow)
{
	MSG msg;
	HACCEL hAccel;
	int rc;

	// Load the application class and title.
	LoadString(hInstance, IDC_WINBASE, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szAppTitle, MAX_LOADSTRING);

	// Initialize the application.
	rc = RegisterApplication(hInstance);
	if (rc == 0)
	{
		MsgBoxError(NULL, TEXT("Error Registering Class"),
			TEXT("An error occurred while trying to register the application's window class."));
		return 0;
	}

	// Initialize this single instance.
	hwndMain = InitializeInstance(hInstance, lpCmdLine, nCmdShow);
	if (hwndMain == 0)
	{
		MsgBoxError(NULL, TEXT("Error Initializing Instance"),
			TEXT("An error occurred while trying to initialize the application's instance."));
		return 0x10;
	}

	// Load accelerators.
	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINBASE));

	// Application message loop.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Translate accelerators.
		if (!TranslateAccelerator(hwndMain, hAccel, &msg))
		{
			// Translate message.
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// Clean up.
	return TerminateInstance(hInstance, msg.wParam);
}

/**
 * Initializes the application and registers the application class.
 *
 * @param hInstance Application instance.
 *
 * @return TRUE if the class was registered.
 */
ATOM RegisterApplication(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	// Setup the application's main window class.
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)MainWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_WINBASE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= GetSysColorBrush(COLOR_WINDOW);
	wcex.lpszMenuName	= (LPCSTR)IDC_WINBASE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	// Register the application's main window class.
	return RegisterClassEx(&wcex);
}

/**
 * Initializes the instance and creates the window.
 *
 * @param hInstance Program instance.
 * @param lpCmdLine String with command line text.
 * @param nShowCmd  Initial state of the program's main window.
 *
 * @return Window handler.
 */
HWND InitializeInstance(HINSTANCE hInstance,
						LPTSTR lpCmdLine,
						int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;

	// Create the main window.
	hWnd = CreateWindow(szWindowClass,			// Window class.
						szAppTitle,				// Window title.
						WS_OVERLAPPEDWINDOW,	// Style flags.
						CW_USEDEFAULT,			// X position.
						CW_USEDEFAULT,			// Y position.
						CW_USEDEFAULT,			// Initial width,
						CW_USEDEFAULT,			// Initial height.
						NULL,					// Parent window.
						NULL,					// Menu class. (Always NULL)
						hInstance,				// Application instance.
						NULL);					// Pointer to create parameters.

	// Check if the window creation worked.
	if (!IsWindow(hWnd))
	{
		MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error"),
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
	}

#if 0
	/* Only for WinCE in the future. */
	// Set the window task switching icon.
	HANDLE hIcon = LoadImage(hInst, MAKEINTRESOURCE(IDI_WINBASE), IMAGE_ICON,
		GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
	SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

	// Set window taskbar icon.
	hIcon = LoadImage(hInst, MAKEINTRESOURCE(IDI_SMALL), IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
#endif

	// Show and update the window.
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}


/**
 * Terminates the application instance.
 *
 * @param hInstance Application instance.
 * @param nDefRC    Return code.
 *
 * @return Previous return code.
 */
int TerminateInstance(HINSTANCE hInstance,
					  int nDefRC)
{
	return nDefRC;
}

/**
 * Main window procedure.
 *
 * @param hWnd   Window handler.
 * @param wMsg   Message type.
 * @param wParam Message parameter.
 * @param lParam Message parameter.
 *
 * @return 0 if everything worked.
 */
LRESULT CALLBACK MainWindowProc(HWND hWnd,
								UINT wMsg,
								WPARAM wParam,
								LPARAM lParam)
{
	switch (wMsg)
	{
		case WM_CREATE:
			return WndMainCreate(hWnd, wMsg, wParam, lParam);
		case WM_COMMAND:
			return WndMainCommand(hWnd, wMsg, wParam, lParam);
		case WM_NOTIFY:
			return WndMainNotify(hWnd, wMsg, wParam, lParam);
		case WM_CLOSE:
			return WndMainClose(hWnd, wMsg, wParam, lParam);
		case WM_DESTROY:
			return WndMainDestroy(hWnd, wMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, wMsg, wParam, lParam);
}

/**
 * Process the WM_CREATE message for the window.
 *
 * @param hWnd   Window handler.
 * @param wMsg   Message type.
 * @param wParam Message parameter.
 * @param lParam Message parameter.
 *
 * @return 0 if everything worked.
 */
LRESULT WndMainCreate(HWND hWnd,
					  UINT wMsg,
					  WPARAM wParam,
					  LPARAM lParam)
{
	// Ensure that the common controls DLL is loaded. 
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

	// Create and setup the DataGridView control.
	ctrlGridView = DataGridView(&hInst, &hWnd);
	ctrlGridView.AddColumn(TEXT("SOMETHING"), 80);
	ctrlGridView.AddColumn(TEXT("ANOTHER"), 200);
	ctrlGridView.AddColumn(TEXT("HELLO"), 100);
	ctrlGridView.AddColumn(TEXT("WHATEVER"), 150);

	// Rows.
	std::vector<LPTSTR> row1;
	row1.push_back(TEXT("001"));
	row1.push_back(TEXT("Another this thing"));
	row1.push_back(TEXT("Even more stuff"));
	row1.push_back(TEXT("1234-567"));
	ctrlGridView.AddItem(row1);
	std::vector<LPTSTR> row2;
	row2.push_back(TEXT("002"));
	row2.push_back(TEXT("Another this thing 2"));
	row2.push_back(TEXT("Even more stuff 2"));
	row2.push_back(TEXT("6789-012"));
	ctrlGridView.AddItem(row2);

	return 0;
}

/**
 * Process the WM_COMMAND message for the window.
 *
 * @param hWnd   Window handler.
 * @param wMsg   Message type.
 * @param wParam Message parameter.
 * @param lParam Message parameter.
 *
 * @return 0 if everything worked.
 */
LRESULT WndMainCommand(HWND hWnd,
					   UINT wMsg,
					   WPARAM wParam,
					   LPARAM lParam)
{
	int wmId = LOWORD(wParam);
	int wmEvent = HIWORD(wParam);

	switch (wmId)
	{
		case IDM_ABOUT:
		   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)AboutDlgProc);
		   break;
		case IDM_EXIT:
		   DestroyWindow(hWnd);
		   break;
	}

	return DefWindowProc(hWnd, wMsg, wParam, lParam);
}

/**
 * Process the WM_NOTIFY message for the window.
 *
 * @param hWnd   Window handler.
 * @param wMsg   Message type.
 * @param wParam Message parameter.
 * @param lParam Message parameter.
 *
 * @return 0 if everything worked.
 */
LRESULT WndMainNotify(HWND hWnd,
					  UINT wMsg,
					  WPARAM wParam,
					  LPARAM lParam)
{
	return DefWindowProc(hWnd, wMsg, wParam, lParam);
}

/**
 * Process the WM_CLOSE message for the window.
 *
 * @param hWnd   Window handler.
 * @param wMsg   Message type.
 * @param wParam Message parameter.
 * @param lParam Message parameter.
 *
 * @return 0 if everything worked.
 */
LRESULT WndMainClose(HWND hWnd,
					 UINT wMsg,
					 WPARAM wParam,
					 LPARAM lParam)
{
	// Send window destruction message.
	DestroyWindow(hWnd);

	return DefWindowProc(hWnd, wMsg, wParam, lParam);
}

/**
 * Process the WM_DESTROY message for the window.
 *
 * @param hWnd   Window handler.
 * @param wMsg   Message type.
 * @param wParam Message parameter.
 * @param lParam Message parameter.
 *
 * @return 0 if everything worked.
 */
LRESULT WndMainDestroy(HWND hWnd,
					   UINT wMsg,
					   WPARAM wParam,
					   LPARAM lParam)
{
	// Post quit message and return.
	PostQuitMessage(0);
	return 0;
}

/**
 * Mesage handler for the About dialog box.
 *
 * @param hDlg   Dialog window handler.
 * @param wMsg   Message type.
 * @param wParam Message parameter.
 * @param lParam Message parameter.
 *
 * @return 0 if everything worked.
 */
LRESULT CALLBACK AboutDlgProc(HWND hDlg,
							  UINT wMsg,
							  WPARAM wParam,
							  LPARAM lParam)
{
	switch (wMsg)
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}

    return FALSE;
}
