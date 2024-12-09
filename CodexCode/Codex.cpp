#include "Codex.h"
#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT UMsg, WPARAM wParam, LPARAM lParam)
{
	switch (UMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case MENU_EXIT_ID:
			PostQuitMessage(0);
			break;
		case SETTINGS_ID:
			MessageBox(hwnd, L"�� ������ � ������������", L"���������", MB_OKCANCEL);
			break;
		default:
			return DefWindowProc(hwnd, UMsg, wParam, lParam);
		}
		break;
	default:
		return DefWindowProc(hwnd, UMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const wchar_t CLASS_NAME[] = L"Window";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Codex",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, nCmdShow);

	HMENU hMainMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();


	AppendMenu(hFileMenu, MF_STRING, MENU_EXIT_ID, L"�����");
	AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"����");


	HMENU hSettingsMenu = CreateMenu();
	AppendMenu(hSettingsMenu, MF_STRING, SETTINGS_ID, L"������������");

	AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR)hSettingsMenu, L"������������");

	SetMenu(hwnd, hMainMenu);


	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
