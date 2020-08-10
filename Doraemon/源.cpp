#include<Windows.h>

/* 另一种添加额外库的方式是在“项目属性->链接器->输入->附加依赖项”中添加库 */
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
		TEXT("Doraemon 哆啦A梦~~"),
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
	HBRUSH hBlueBrush, hOldBrush, hRedBrush, hYellowBrush;
	POINT apt[4];

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
		
		// 辅助线
		hPen = CreatePen(PS_DOT, 1, RGB(192, 192, 192));
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, cxClient / 2, 0, NULL);
		LineTo(hdc, cxClient / 2, cyClient);
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);
		SelectObject(hdc, hOldPen); //画完辅助线后，恢复到默认画笔

		// 头( 直径240 )
		hBlueBrush = CreateSolidBrush(RGB(0, 159, 232));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
		Ellipse(hdc, cxClient / 2 - 120, cyClient / 2 - 200, cxClient / 2 + 120, cyClient / 2 + 40);
		SelectObject(hdc, hOldBrush);

		// 脸（直径200）
		Ellipse(hdc, cxClient / 2 - 100, cyClient / 2 - 160, cxClient / 2 + 100, cyClient / 2 + 40);

		// 眼眶（长60，宽50）
		Ellipse(hdc, cxClient / 2 - 50, cyClient / 2 - 180, cxClient / 2, cyClient / 2 - 120);
		Ellipse(hdc, cxClient / 2, cyClient / 2 - 180, cxClient / 2 + 50, cyClient / 2 - 120);

		// 眼珠（长20，宽15）
		hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, cxClient / 2 - 20, cyClient / 2 - 160, cxClient / 2 - 5, cyClient / 2 - 140);
		Ellipse(hdc, cxClient / 2 + 5, cyClient / 2 - 160, cxClient / 2 + 20, cyClient / 2 - 140);
		SelectObject(hdc, hOldBrush);

		// 眼光（长8，宽6）
		Ellipse(hdc, cxClient / 2 - 15, cyClient / 2 - 156, cxClient / 2 - 7, cyClient / 2 - 150);
		Ellipse(hdc, cxClient / 2 + 7, cyClient / 2 - 156, cxClient / 2 + 15, cyClient / 2 - 150);

		// 鼻子红色
		hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hRedBrush);
		Ellipse(hdc, cxClient / 2 - 10, cyClient / 2 - 135, cxClient / 2 + 10, cyClient / 2 - 115);
		SelectObject(hdc, hOldBrush);

		// 人中 + 嘴巴
		MoveToEx(hdc, cxClient / 2, cyClient / 2 - 115, NULL);
		LineTo(hdc, cxClient / 2, cyClient / 2 - 30);
		Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 120, cxClient / 2 + 70, cyClient / 2 - 30, \
			cxClient / 2 - 60, cyClient / 2 - 60, cxClient / 2 + 60, cyClient / 2 - 60);

		// 胡须
		MoveToEx(hdc, cxClient / 2 - 70, cyClient / 2 - 115, NULL);
		LineTo(hdc, cxClient / 2 - 20, cyClient / 2 - 100);
		MoveToEx(hdc, cxClient / 2 - 80, cyClient / 2 - 85, NULL);
		LineTo(hdc, cxClient / 2 - 20, cyClient / 2 - 85);
		MoveToEx(hdc, cxClient / 2 - 70, cyClient / 2 - 55, NULL);
		LineTo(hdc, cxClient / 2 - 20, cyClient / 2 - 70);

		MoveToEx(hdc, cxClient / 2 + 70, cyClient / 2 - 115, NULL);
		LineTo(hdc, cxClient / 2 + 20, cyClient / 2 - 100);
		MoveToEx(hdc, cxClient / 2 + 80, cyClient / 2 - 85, NULL);
		LineTo(hdc, cxClient / 2 + 20, cyClient / 2 - 85);
		MoveToEx(hdc, cxClient / 2 + 70, cyClient / 2 - 55, NULL);
		LineTo(hdc, cxClient / 2 + 20, cyClient / 2 - 70);

		// 身体
		hOldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
		Rectangle(hdc, cxClient / 2 - 90, cyClient / 2, cxClient / 2 + 90, cyClient / 2 + 150);
		SelectObject(hdc, hOldBrush);

		// 肚皮
		Ellipse(hdc, cxClient / 2 - 70, cyClient / 2 - 20, cxClient / 2 + 70, cyClient / 2 + 120);
		hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 20, cxClient / 2 + 70, cyClient / 2 + 120,\
			cxClient/2+60,cyClient/2-10,cxClient/2-60,cyClient/2-10);
		SelectObject(hdc, hOldPen);
		
		// 项圈
		hOldBrush = (HBRUSH)SelectObject(hdc, hRedBrush);
		RoundRect(hdc, cxClient / 2 - 95, cyClient / 2 - 5, cxClient / 2 + 95, cyClient / 2 + 10, \
			20, 20);
		SelectObject(hdc, hOldBrush);

		// 铃铛
		hYellowBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hYellowBrush);
		Ellipse(hdc, cxClient / 2 - 15, cyClient / 2, cxClient / 2 + 15, cyClient / 2 + 30);
		RoundRect(hdc, cxClient / 2 - 15, cyClient / 2 + 10, cxClient / 2 + 15, cyClient / 2 + 15, 2, 2);
		SelectObject(hdc, hRedBrush);
		Ellipse(hdc, cxClient / 2 - 4, cyClient / 2 + 18, cxClient / 2 + 4, cyClient / 2 + 26);
		MoveToEx(hdc, cxClient / 2, cyClient / 2 + 26, NULL);
		LineTo(hdc, cxClient / 2, cyClient / 2 + 30);

		SelectObject(hdc, hOldBrush);

		// 口袋
		Pie(hdc, cxClient / 2 - 50, cyClient / 2, cxClient / 2 + 50, cyClient / 2 + 100, \
			cxClient / 2 - 50, cyClient / 2 + 50, cxClient / 2 + 50, cyClient / 2 + 50);
		// Ellipse(hdc, cxClient / 2 - 50, cyClient / 2, cxClient / 2 + 50, cyClient / 2 + 100);

		// 裤裆
		Pie(hdc, cxClient / 2 - 20, cyClient / 2 + 130, cxClient / 2 + 20, cyClient / 2 + 170, \
			cxClient / 2 + 20, cyClient / 2 + 150, cxClient / 2 - 20, cyClient / 2 + 150);
		hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, cxClient / 2 - 20, cyClient / 2 + 150, NULL);
		LineTo(hdc, cxClient / 2 + 20, cyClient / 2 + 150);
		SelectObject(hdc, hOldPen);

		// 脚丫
		Ellipse(hdc, cxClient / 2 - 110, cyClient / 2 + 130, cxClient / 2 - 10, cyClient / 2 + 170);
		Ellipse(hdc, cxClient / 2 + 10, cyClient / 2 + 130, cxClient / 2 + 110, cyClient / 2 + 170);

		// 手
		hOldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
		apt[0].x = cxClient / 2 - 90;
		apt[0].y = cyClient / 2 + 10;
		apt[1].x = cxClient / 2 - 130;
		apt[1].y = cyClient / 2 + 50;
		apt[2].x = cxClient / 2 - 110;
		apt[2].y = cyClient / 2 + 70;
		apt[3].x = cxClient / 2 - 90;
		apt[3].y = cyClient / 2 + 60;
		Polygon(hdc, apt, 4);
		apt[0].x = cxClient / 2 + 90;
		apt[0].y = cyClient / 2 + 10;
		apt[1].x = cxClient / 2 + 130;
		apt[1].y = cyClient / 2 + 50;
		apt[2].x = cxClient / 2 + 110;
		apt[2].y = cyClient / 2 + 70;
		apt[3].x = cxClient / 2 + 90;
		apt[3].y = cyClient / 2 + 60;
		Polygon(hdc, apt, 4);

		SelectObject(hdc, hOldBrush);

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