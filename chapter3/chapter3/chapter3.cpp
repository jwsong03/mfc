#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

LPCWSTR szAppName1 = L"Hello";
LPCWSTR szAppName2 = L"World";
HINSTANCE _hInstance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	HWND hWnd, hWnd2;
	MSG msg;
	WNDCLASS WndClass;

	_hInstance = hInstance;
	
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = _hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szAppName1;

	if (!RegisterClass(&WndClass)) return NULL;

	WndClass.lpfnWndProc = WndProc2;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszClassName = szAppName2;
	
	if (!RegisterClass(&WndClass)) return NULL;


	hWnd = CreateWindow(
		szAppName1,
		szAppName1,
		WS_OVERLAPPEDWINDOW,
		0, 0, 320, 240,
		NULL, NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	
	while (GetMessage(&msg, NULL, 0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam) {
	static HWND hWnd2; // static 변수를 통한 자식윈도우 저장
	switch (mesg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, L"안녕하세요", L"알림", MB_OK);
		SetWindowText(hWnd2, L"Black");		
		break;

	case WM_CREATE:
		hWnd2 = CreateWindow(
			szAppName2,
			szAppName2,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD, //WS_CHILD옵션을 주는 경우 반드시 부모 윈도우를 설정해주어야 함
			320, 0, 320, 240,
			hWnd, NULL,
			_hInstance,
			NULL
		);

		//ShowWindow(hWnd2, SW_SHOW);//WS_VISIBLE로 인해 생략 가능
		break;

	case WM_DESTROY: 
		MessageBox(hWnd, L"나죽네", L"", MB_OK);
		PostQuitMessage(0);	//프르그램 종료 메시지 포스팅(WM_DESTORY)
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
		MessageBox(hWnd, L"나죽어?", L"", MB_OK);
		//PostQuitMessage(0);	//프르그램 종료 메시지 포스팅(WM_DESTORY)
		return FALSE;
	default:
		break;
	}

	return DefWindowProc(hWnd, mesg, wParam, lParam);
}