#include <Windows.h>

#define WM_MYBTN1_DOWNUP WM_USER+1
#define WM_MYBTN2_DOWNUP WM_USER+2
#define WM_MYBTN3_DOWNUP WM_USER+3
#define WM_MYBTN4_DOWNUP WM_USER+4
#define WM_MYBTN4_MOUSEMOVE WM_USER+5
#define MAX_WCHARS 2048


LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK EditProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK EditProc2(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK BtnProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BtnProc2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BtnProc3(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BtnProc4(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK StaticProc4(HWND, UINT, WPARAM, LPARAM);


HINSTANCE _hInstance;

WNDPROC _fpOldBtnProc;
WNDPROC _fpOldEditProc;
WNDPROC _fpOldStaticProc;

LPCWSTR szWinName1 = L"Parent";
LPCWSTR szWinName2 = L"Child";


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc1;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szWinName1;
	if (!RegisterClass(&WndClass)) return NULL;

	WndClass.lpfnWndProc = WndProc2;
	WndClass.lpszClassName = szWinName2;
	if (!RegisterClass(&WndClass)) return NULL;

	_hInstance = hInstance;

	hWnd = CreateWindow(
		szWinName1, L"부모 윈도우",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 640, 480, NULL, NULL, hInstance, NULL
	);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc1(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hChildWnd;
	static HWND hEditWnd;
	static HWND hStaticWnd;
	HDC hdc;
	WCHAR szBuf[MAX_WCHARS];
	switch (uMsg)
	{
	case WM_CREATE:
		hChildWnd = CreateWindow(
			szWinName2, L"자식 윈도우",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			0, 482, 640, 240, hWnd, NULL, _hInstance, NULL
		);
		hEditWnd = CreateWindow(
			L"EDIT", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
			5, 5, 320 - 10, 480 - 50, hWnd, NULL, _hInstance, NULL
		);
		hStaticWnd = CreateWindow(
			L"STATIC", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			320 + 5, 5, 320 - 30, 480 - 50, hWnd, NULL, _hInstance, NULL
		);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	case WM_MYBTN1_DOWNUP:
		SetWindowText(hEditWnd, L"송재원");
		break;
	case WM_MYBTN2_DOWNUP:
		SetWindowText(hEditWnd, L"9754321");
		break;
	case WM_MYBTN3_DOWNUP:
		SetWindowText(hEditWnd, L"");
		break;
	case WM_MYBTN4_DOWNUP:
		SetWindowText(hStaticWnd, L"");
		break;
	case WM_MYBTN4_MOUSEMOVE:
		int x, y, mx, my;
		int width, height;
		RECT rt_view, rt_btn;

		x = LOWORD(lParam);
		y = HIWORD(lParam);

		GetClientRect(hStaticWnd, &rt_view);
		GetClientRect((HWND)wParam, &rt_btn);

		width = rt_view.right - rt_view.left;
		height = rt_view.bottom - rt_view.top;

		mx = width * x / (rt_btn.right - rt_btn.left);
		my = height * y / (rt_btn.bottom - rt_btn.top);

		if (mx < 1) mx = 1;
		else if (mx >(width - 1)) mx = width - 1;

		if (my < 1) my = 1;
		else if (my >(height - 1)) mx = height - 1;

		hdc = GetDC(hStaticWnd);
		SetPixel(hdc, mx - 1, my - 1, RGB(0, 0, 255));
		SetPixel(hdc, mx, my - 1, RGB(0, 0, 255));
		SetPixel(hdc, mx + 1, my - 1, RGB(0, 0, 255));

		SetPixel(hdc, mx - 1, my, RGB(0, 0, 255));
		SetPixel(hdc, mx, my, RGB(0, 0, 255));
		SetPixel(hdc, mx + 1, my, RGB(0, 0, 255));

		SetPixel(hdc, mx - 1, my + 1, RGB(0, 0, 255));
		SetPixel(hdc, mx, my + 1, RGB(0, 0, 255));
		SetPixel(hdc, mx + 1, my + 1, RGB(0, 0, 255));

		ReleaseDC(hStaticWnd, hdc);
		break;
	case WM_COMMAND:
		WORD wNotifyCode, wId;
		

		if (hEditWnd != (HWND)lParam) {
			wNotifyCode = HIWORD(wParam);
			wId = LOWORD(wParam);

			switch (wNotifyCode){
			case EN_CHANGE: 
				GetWindowText((HWND)lParam, szBuf, MAX_WCHARS - 1);
				SetWindowText(hEditWnd, szBuf);
				break;
			}

		}

		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hBtnWnd1, hBtnWnd2, hBtnWnd3, hBtnWnd4;
	static HWND hEditWnd;
	HWND hParentWnd;
	hParentWnd = (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);

	switch (uMsg)
	{
	case WM_CREATE:
		hBtnWnd1 = CreateWindow(
			L"BUTTON", L"이름은",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			160 * 0, 0, 160, 120, hWnd, NULL, _hInstance, NULL
		);

		hBtnWnd2 = CreateWindow(
			L"BUTTON", L"학번은",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			160 * 1, 0, 160, 120, hWnd, NULL, _hInstance, NULL
		);

		hBtnWnd3 = CreateWindow(
			L"BUTTON", L"지움",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			160 * 2, 0, 160, 120, hWnd, NULL, _hInstance, NULL
		);

		hBtnWnd4 = CreateWindow(
			L"BUTTON", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			160 * 3, 0, 160, 240, hWnd, NULL, _hInstance, NULL
		);

		hEditWnd = CreateWindow(
			L"EDIT", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
			0, 120, 160 * 3, 120, hWnd, NULL, _hInstance, NULL
		);
		_fpOldBtnProc = (WNDPROC)GetWindowLong(hBtnWnd1, GWL_WNDPROC);
		_fpOldEditProc = (WNDPROC)GetWindowLong(hEditWnd, GWL_WNDPROC);

		SetWindowLong(hBtnWnd1, GWL_WNDPROC, (LONG)BtnProc1);
		SetWindowLong(hBtnWnd2, GWL_WNDPROC, (LONG)BtnProc2);
		SetWindowLong(hBtnWnd3, GWL_WNDPROC, (LONG)BtnProc3);
		SetWindowLong(hBtnWnd4, GWL_WNDPROC, (LONG)BtnProc4);
		SetWindowLong(hEditWnd, GWL_WNDPROC, (LONG)EditProc2);
		break;
	case WM_MYBTN1_DOWNUP:
	case WM_MYBTN2_DOWNUP:
	case WM_MYBTN3_DOWNUP:
	case WM_MYBTN4_DOWNUP:
	case WM_MYBTN4_MOUSEMOVE:
		SendMessage(hParentWnd, uMsg, wParam, lParam);
		break;
	case WM_COMMAND:
		if (hEditWnd ==(HWND)lParam ){
			WORD wNotifyCode = HIWORD(wParam);
			WORD wID = LOWORD(wParam);

			switch (wNotifyCode){
			case EN_CHANGE:
				SendMessage(hParentWnd, uMsg, wParam, lParam);
				break;
			}
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK EditProc1(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK EditProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HWND hParentWnd;
	hParentWnd = (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);

	WORD wNotifyCode = HIWORD(wParam);
	WORD wID = LOWORD(wParam);

	switch (uMsg) {	
	case WM_COMMAND:
		switch (wNotifyCode) {
		case EN_CHANGE:
			SendMessage(hParentWnd, uMsg, wParam, lParam);
			break;
		}
		break;
	}

	return CallWindowProc(_fpOldEditProc, hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK BtnProc1(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_LBUTTONUP:
		HWND hParentWnd;
		hParentWnd = (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);
		SendMessage(hParentWnd, WM_MYBTN1_DOWNUP, wParam, lParam);
		break;
	default:
		break;
	}

	return CallWindowProc(_fpOldBtnProc, hWnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK BtnProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_LBUTTONUP:
		HWND hParentWnd;
		hParentWnd = (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);
		SendMessage(hParentWnd, WM_MYBTN2_DOWNUP, wParam, lParam);
		break;
	default:
		break;
	}

	return CallWindowProc(_fpOldBtnProc, hWnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK BtnProc3(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_LBUTTONUP:
		HWND hParentWnd;
		hParentWnd = (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);
		SendMessage(hParentWnd, WM_MYBTN3_DOWNUP, wParam, lParam);
		break;
	default:
		break;
	}

	return CallWindowProc(_fpOldBtnProc, hWnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK BtnProc4(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HWND hParentWnd;
	hParentWnd = (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);

	switch (uMsg)
	{
	case WM_LBUTTONUP:
		SendMessage(hParentWnd, WM_MYBTN4_DOWNUP, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		SendMessage(hParentWnd, WM_MYBTN4_MOUSEMOVE, (WPARAM)hWnd, lParam); //wParam : hWnd
		break;
	default:
		break;
	}

	return CallWindowProc(_fpOldBtnProc, hWnd, uMsg, wParam, lParam);
}
