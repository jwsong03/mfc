#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND _hWnd2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	LPCWSTR szAppName = L"Hello";
	
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

	hWnd = CreateWindow(
		szAppName,
		L"Hello",
		WS_OVERLAPPEDWINDOW,
		0, 0, 320, 240,
		NULL, NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);


	_hWnd2 = CreateWindow(
		szAppName,
		L"World",
		WS_OVERLAPPEDWINDOW,
		320, 0, 320, 240,
		NULL, NULL,
		hInstance,
		NULL
	);

	ShowWindow(_hWnd2, nShowCmd);
	UpdateWindow(_hWnd2);

	while (GetMessage(&msg, NULL, 0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam) {
	switch (mesg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, L"왼쪽 버튼 눌림", L"알림", MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	default:
		break;
	}

	return DefWindowProc(hWnd, mesg, wParam, lParam);
}