#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE _hInstance;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;

	LPCWSTR szAppNmae = L"Hello";
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szAppNmae;

	if (!RegisterClass(&WndClass)) return NULL;

	_hInstance = hInstance;

	hWnd = CreateWindow(szAppNmae, szAppNmae,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 320, 240,
		NULL, NULL, hInstance, NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam) {
	static HWND hBtn1, hBtn2;

	switch (mesg) {
	case WM_CREATE:
		hBtn1 = CreateWindow(L"button", L"click",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	//WS_CHILD
			0, 0, 100, 100, hWnd, 
			(HMENU)888, _hInstance, NULL); //PARENT hWnd
		hBtn2 = CreateWindow(L"button", L"click",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	//WS_CHILD
			100, 0, 100, 100, hWnd, 
			(HMENU)999, _hInstance, NULL); //PARENT hWnd
		break;

	case WM_COMMAND:
		//int id;
		//id = LOWORD(wParam);
		//if (id == 888)
		//	MessageBox(hWnd, L"안녕하세요(1)", L"알림", MB_OK);
		//else if(id == 999)
		//	MessageBox(hWnd, L"안녕하세요(2)", L"알림", MB_OK);
		if (hBtn1 == (HWND)lParam) {
			MessageBox(hWnd, L"안녕하세요(1)", L"알림", MB_OK);
		}
		else if (hBtn2 == (HWND)lParam) {
			MessageBox(hWnd, L"안녕하세요(2)", L"알림", MB_OK);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}
