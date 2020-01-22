#include "initial_dialog.h"
#include "resource.h"
#include <CommCtrl.h>

INT_PTR CALLBACK InitDlgProc(HWND, UINT, WPARAM, LPARAM);

int ShowInitialDialog(_In_ HINSTANCE hInst, _In_ int nCmdShow)
{
	return (int)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, InitDlgProc);
}

INT_PTR InitDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst = GetModuleHandle(NULL);

	switch (message) {
	case WM_INITDIALOG:
		TCHAR buffer[512];
		ZeroMemory(buffer, sizeof(buffer));
		LoadString(hInst, IDS_INTRO, (LPWSTR)&buffer, sizeof(buffer) / 2);
		SetDlgItemText(hWnd, IDC_TEXT, buffer);

		PostMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON)));
		PostMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON)));
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCLOSE) {
			EndDialog(hWnd, LOWORD(wParam));
			break;
		}
		return FALSE;
	case WM_CLOSE:
		EndDialog(hWnd, IDCLOSE);
		break;
	default:
		return FALSE;
	}

	return TRUE;
}
