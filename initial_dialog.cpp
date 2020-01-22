#include "initial_dialog.h"
#include "resource.h"
#include <CommCtrl.h>
#include <stdlib.h>

INT_PTR CALLBACK InitDlgProc(HWND, UINT, WPARAM, LPARAM);

SIDret* ShowInitialDialog(_In_ HINSTANCE hInst, _In_ int nCmdShow)
{
	return (SIDret*)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, InitDlgProc);
}

void FreeSidRet(SIDret* subject)
{
	free(subject->sequence);
	free(subject);
}

INT_PTR
InitDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst = GetModuleHandle(NULL);

	switch (message) {
	case WM_INITDIALOG:
		TCHAR buffer[512];
		ZeroMemory(buffer, sizeof(buffer));
		LoadString(hInst, IDS_INTRO, (LPWSTR)&buffer, sizeof(buffer) / 2);
		SetDlgItemText(hWnd, IDC_TEXT, buffer);

		SetDlgItemText(hWnd, IDC_SEQUENCE, TEXT("zp`"));

		PostMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON)));
		PostMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON)));
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCLOSE) {
			SIDret* ret = (SIDret*)malloc(sizeof(SIDret));
			TCHAR* sequence = (TCHAR*)malloc(128);

			if (ret == NULL || sequence == NULL) {
				EndDialog(hWnd, NULL);
				break;
			}

			ZeroMemory(sequence, sizeof(sequence));
			ret->value = LOWORD(wParam);
			ret->sequence = sequence;
			GetDlgItemText(hWnd, IDC_SEQUENCE, sequence, 128 / 2);
			EndDialog(hWnd, (INT_PTR)ret);
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
