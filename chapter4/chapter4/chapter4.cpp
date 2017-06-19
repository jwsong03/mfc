#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BtnProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK EditProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE _hInstance;
HWND _hBtn1, _hEdit1, _hEdit2;
WNDPROC _fpOldBtnProc;
WNDPROC _fpOldEditProc;

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
	WORD wNotifyCode;
	WCHAR szMsg[1024];
	switch (mesg) {
	case WM_CREATE:
		 _hBtn1 = CreateWindow(L"button", L"click",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	//WS_CHILD
			0, 0, 100, 100, hWnd, 
			(HMENU)888, _hInstance, NULL); //PARENT hWnd
		_hEdit1 = CreateWindow(L"edit", L"Hello",
			WS_VISIBLE | WS_CHILD | WS_BORDER |
			ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,	//WS_CHILD
			102, 0, 200, 100, hWnd, 
			(HMENU)999, _hInstance, NULL); //PARENT hWnd

		_hEdit2 = CreateWindow(L"edit", L"",
			WS_VISIBLE | WS_CHILD | ES_MULTILINE,	//WS_CHILD
			0, 102, 300, 50, hWnd,
			(HMENU)777, _hInstance, NULL); //PARENT hWnd

		_fpOldBtnProc = (WNDPROC)GetWindowLong(_hBtn1, GWL_WNDPROC);
		_fpOldEditProc = (WNDPROC)GetWindowLong(_hEdit1, GWL_WNDPROC);
		
		SetWindowLong(_hBtn1, GWL_WNDPROC, (LONG)BtnProc);
		SetWindowLong(_hEdit1, GWL_WNDPROC, (LONG)EditProc);
		SetWindowLong(_hEdit2, GWL_WNDPROC, (LONG)EditProc);

		break;

	case WM_COMMAND:
		wNotifyCode = HIWORD(wParam);

		if (_hBtn1 == (HWND)lParam) {

			if (wNotifyCode == BS_PUSHBUTTON) {
				GetWindowText(_hEdit1, szMsg, wcslen(szMsg));
				SetWindowText(_hEdit2, szMsg);
				//hdc = GetDC(hWnd);
				//TextOut(hdc, 0, 102, szMsg, wcslen(szMsg));
				//ReleaseDC(hWnd, hdc);
			}
		}

		break;
	case WM_MOUSEMOVE:
		WORD x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		wsprintf(szMsg, L"%03d %03d", x, y);
		SetWindowText(_hEdit1, szMsg);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;

	}
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}

LRESULT CALLBACK BtnProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam) {
	WCHAR szMsg[1024];

	switch (mesg) {
	case WM_MOUSEMOVE:
		WORD x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		wsprintf(szMsg, L"%03d %03d", x, y);
		SetWindowText(_hEdit1, szMsg);
		break;
	}

	return CallWindowProc(_fpOldBtnProc, hWnd, mesg, wParam, lParam);
}

LRESULT CALLBACK EditProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam) {
	WCHAR szMsg[1024];

	switch (mesg) {
	case WM_MOUSEMOVE:
		WORD x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		wsprintf(szMsg, L"%03d %03d", x, y);
		SetWindowText(_hEdit1, szMsg);
		break;
	}

	return CallWindowProc(_fpOldEditProc, hWnd, mesg, wParam, lParam);
}
