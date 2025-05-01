#define UNICODE
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>

void openhomewindow(HINSTANCE hInstancea){
    //ウィンドウと『問題を出題する』ボタンを作成する
    HWND hwnd = CreateWindow(
    TEXT("STATIC"),TEXT("HOME"),
    WS_CAPTION,100,100,1000,1000,NULL,NULL,hInstancea,NULL);

	ShowWindow(hwnd , SW_SHOW);
	Sleep(10000);
	DestroyWindow(hwnd);
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    int nCmdShow){
    

		wchar_t a;

    HINSTANCE hInstancea = hInstance;
        //homeウィンドウを開く
        //openhomewindow(hInstancea);
		MessageBox(NULL , TEXT("不正解") ,
			TEXT("判定") , MB_ICONINFORMATION);
    return 0;
}