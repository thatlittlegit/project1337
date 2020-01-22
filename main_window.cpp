#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <CommCtrl.h>
#include <tchar.h>

#include "initial_dialog.h"
#include "resource.h"

#define WINDOW_CLASS TEXT("PROJECT1337")

// Forward declarations of functions included in this code module:
ATOM RegisterWindowClass(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int ShowMainWindow(_In_ HINSTANCE, _In_ int nCmdShow);

TCHAR* sequence;

int WINAPI _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	InitCommonControls();

	SIDret* diagret = ShowInitialDialog(hInstance, nCmdShow);

	if (diagret->value != IDOK)
		return 1;

	sequence = diagret->sequence;
	return ShowMainWindow(hInstance, nCmdShow);
}

int ShowMainWindow(_In_ HINSTANCE hInstance, _In_ int nCmdShow)
{
	RegisterWindowClass(hInstance);
	HWND hWnd = CreateWindow(WINDOW_CLASS, TEXT(""), WS_VISIBLE,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) {
		return 2;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

ATOM RegisterWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.hIconSm = NULL;
	wcex.hIcon = NULL;

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_CAPTIONTEXT + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WINDOW_CLASS;

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CREATE:
	case WM_KILLFOCUS:
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 10000, 10000, 0);
		break;
	case WM_SETCURSOR:
		SetCursor(NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR: {
		static int almost = 0;
		if (wParam == sequence[almost])
			almost++;
		else
			almost = 0;

		if (almost == _tcslen(sequence))
			ExitProcess(0);
		break;
	}
	case WM_CLOSE:
	case WM_NCCALCSIZE:
	case WM_PAINT:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
