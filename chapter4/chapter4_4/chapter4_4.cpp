#include <Windows.h>

#define WM_MYMOVE WM_USER+1
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

HINSTANCE _hInstance;
LPCWSTR szAppName = L"Hello";
LPCWSTR szAppName2 = L"WND2";

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szAppName;
	if (!RegisterClass(&WndClass)) return NULL;

	WndClass.lpfnWndProc = WndProc2;
	WndClass.lpszClassName = szAppName2;
	if (!RegisterClass(&WndClass)) return NULL;

	_hInstance = hInstance;

	hWnd = CreateWindow(
		szAppName, L"부모 윈도우",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 320, 240, NULL, NULL, hInstance, NULL
	);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam) {
	static HWND hWnd2;
	switch (mesg) {
	case WM_CREATE:
		hWnd2 = CreateWindow(szAppName2, szAppName2,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//WS_CHILD
			320, 0, 320, 240, hWnd,
			NULL, _hInstance, NULL); //PARENT hWnd
		break;
	case WM_MOUSEMOVE:
		int x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		lParam = (x << 16) | y;
		SendMessage(hWnd2, WM_MYMOVE, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam) {
	HWND hParentWnd;
	switch (mesg) {
	case WM_MYMOVE:
		WORD x, y;
		HDC hdc;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hdc = GetDC(hWnd);
		TextOut(hdc, x, y, L"*", 1);
		ReleaseDC(hWnd, hdc);
		break;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}


