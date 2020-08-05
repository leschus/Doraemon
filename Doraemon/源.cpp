#include<Windows.h>

/* ��һ����Ӷ����ķ�ʽ���ڡ���Ŀ����->������->����->�������������ӿ� */
#pragma comment(lib,"winmm.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("Doraemon");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR szCmdLine, int nShowCmd)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("This program requires Windows NT"), szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,
		TEXT("Doraemon ����A��~~"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT	CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxClient, cyClient;

	HPEN hPen, hOldPen;
	HBRUSH hBlueBrush, hOldBrush, hRedBrush;

	switch (message) {
	case WM_CREATE:
		//MessageBox(hwnd, TEXT("Welcome to my colorful world!"), szAppName, 0);
		
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		// ������
		hPen = CreatePen(PS_DOT, 1, RGB(192, 192, 192));
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, cxClient / 2, 0, NULL);
		LineTo(hdc, cxClient / 2, cyClient);
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);
		SelectObject(hdc, hOldPen); //���긨���ߺ󣬻ָ���Ĭ�ϻ���

		// ͷ( ֱ��240 )
		hBlueBrush = CreateSolidBrush(RGB(0, 159, 232));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
		Ellipse(hdc, cxClient / 2 - 120, cyClient / 2 - 200, cxClient / 2 + 120, cyClient / 2 + 40);
		SelectObject(hdc, hOldBrush);

		// ����ֱ��200��
		Ellipse(hdc, cxClient / 2 - 100, cyClient / 2 - 160, cxClient / 2 + 100, cyClient / 2 + 40);

		// �ۿ�����60����50��
		Ellipse(hdc, cxClient / 2 - 50, cyClient / 2 - 180, cxClient / 2, cyClient / 2 - 120);
		Ellipse(hdc, cxClient / 2, cyClient / 2 - 180, cxClient / 2 + 50, cyClient / 2 - 120);

		// ���飨��20����15��
		hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, cxClient / 2 - 20, cyClient / 2 - 160, cxClient / 2 - 5, cyClient / 2 - 140);
		Ellipse(hdc, cxClient / 2 + 5, cyClient / 2 - 160, cxClient / 2 + 20, cyClient / 2 - 140);
		SelectObject(hdc, hOldBrush);

		// �۹⣨��8����6��
		Ellipse(hdc, cxClient / 2 - 15, cyClient / 2 - 156, cxClient / 2 - 7, cyClient / 2 - 150);
		Ellipse(hdc, cxClient / 2 + 7, cyClient / 2 - 156, cxClient / 2 + 15, cyClient / 2 - 150);

		// ���Ӻ�ɫ
		hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hRedBrush);
		Ellipse(hdc, cxClient / 2 - 10, cyClient / 2 - 135, cxClient / 2 + 10, cyClient / 2 - 115);
		SelectObject(hdc, hOldBrush);

		// ���� + ���
		MoveToEx(hdc, cxClient / 2, cyClient / 2 - 115, NULL);
		LineTo(hdc, cxClient / 2, cyClient / 2 - 30);
		Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 120, cxClient / 2 + 70, cyClient / 2 - 30, \
			cxClient / 2 - 60, cyClient / 2 - 60, cxClient / 2 + 60, cyClient / 2 - 60);




		EndPaint(hwnd, &ps);
		return 0;
	//case WM_CLOSE:
	//	if (MessageBox(hwnd, TEXT("Are you sure about this?"), TEXT("Confirm Box"), MB_YESNO) == IDYES) {
	//		DestroyWindow(hwnd);
	//	}
	//	else return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}