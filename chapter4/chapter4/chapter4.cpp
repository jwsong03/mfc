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
	static HWND hBtn1, hEdit1, hEdit2;
	WORD wNotifyCode;
	switch (mesg) {
	case WM_CREATE:
		hBtn1 = CreateWindow(L"button", L"click",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	//WS_CHILD
			0, 0, 100, 100, hWnd, 
			(HMENU)888, _hInstance, NULL); //PARENT hWnd
		hEdit1 = CreateWindow(L"edit", L"Hello",
			WS_VISIBLE | WS_CHILD | WS_BORDER |
			ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,	//WS_CHILD
			102, 0, 200, 100, hWnd, 
			(HMENU)999, _hInstance, NULL); //PARENT hWnd

		hEdit2 = CreateWindow(L"edit", L"",
			WS_VISIBLE | WS_CHILD | ES_MULTILINE,	//WS_CHILD
			0, 102, 300, 50, hWnd,
			(HMENU)777, _hInstance, NULL); //PARENT hWnd

		break;

	case WM_COMMAND:
		//int id;
		//id = LOWORD(wParam);
		//if (id == 888)
		//	MessageBox(hWnd, L"안녕하세요(1)", L"알림", MB_OK);
		//else if(id == 999)
		//	MessageBox(hWnd, L"안녕하세요(2)", L"알림", MB_OK);

		wNotifyCode = HIWORD(wParam);
		WCHAR szMsg[1024];
		HDC hdc;

		if (hBtn1 == (HWND)lParam) {

			if (wNotifyCode == BS_PUSHBUTTON) {
				GetWindowText(hEdit1, szMsg, wcslen(szMsg));
				SetWindowText(hEdit2, szMsg);
				//hdc = GetDC(hWnd);
				//TextOut(hdc, 0, 102, szMsg, wcslen(szMsg));
				//ReleaseDC(hWnd, hdc);

			}
		}

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}
