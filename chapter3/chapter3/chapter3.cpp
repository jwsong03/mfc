#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	HWND hWnd, hWnd2;
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

	WndClass.lpfnWndProc = WndProc2;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszClassName = L"WND2";
	
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


	hWnd2 = CreateWindow(
		L"WND2",
		L"World",
		WS_OVERLAPPEDWINDOW,
		320, 0, 320, 240,
		NULL, NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd2, nShowCmd);
	UpdateWindow(hWnd2);

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
		MessageBox(hWnd, L"안녕하세요", L"알림", MB_OK);
		SetWindowText(hWnd, L"Black");

		HWND hNote;
		hNote = FindWindow(NULL, L"제목 없음 - 메모장");
		HDC hdc;
		hdc = GetDC(hNote);
		TextOut(hdc, 0, 0, L"Hello", 5);
		ReleaseDC(hNote, hdc);


		break;
	case WM_DESTROY: 
		PostQuitMessage(0);
		return FALSE;
	default:
		break;
	}

	return DefWindowProc(hWnd, mesg, wParam, lParam);
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam) {
	switch (mesg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, L"저리가세요", L"알림", MB_OK);
		HWND hNote;
		hNote = (HWND)0x000603CC;
		HDC hdc;
		hdc = GetDC(hNote);
		TextOut(hdc, 0, 0, L"Hello", 5);
		ReleaseDC(hNote, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	default:
		break;
	}

	return DefWindowProc(hWnd, mesg, wParam, lParam);
}