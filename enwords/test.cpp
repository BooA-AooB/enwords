#define UNICODE
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd , msg , wp , lp);
}

int openhomewindow(HINSTANCE hInstancea){
    //ウィンドウと『問題を出題する』ボタンを作成する
    MSG msg;
	WNDCLASS winc;

	winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstancea;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("KITTY");

    if (!RegisterClass(&winc)) return -1;

    HWND hwnd = CreateWindow(
    TEXT("KITTY"),TEXT("HOME"),
    WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
	CW_USEDEFAULT , CW_USEDEFAULT ,
	CW_USEDEFAULT , CW_USEDEFAULT ,NULL,NULL,hInstancea,NULL);

    CreateWindow(
		TEXT("BUTTON") , TEXT("Kitty") ,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
		0 , 0 , 100 , 50 ,
		hwnd , NULL , hInstancea , NULL
	);
    while(GetMessage(&msg , NULL , 0 , 0)) DispatchMessage(&msg);

	return msg.wParam;
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    int nCmdShow){

        int i= -1;
		LPCWSTR a;
        a=L"不正解";
        if (i<0)
        {
            a = L"正解";
        }
        

    HINSTANCE hInstancea = hInstance;
        //homeウィンドウを開く
        openhomewindow(hInstancea);
		MessageBox(NULL , a,
			TEXT("判定") , MB_ICONINFORMATION);
    return 0;
}