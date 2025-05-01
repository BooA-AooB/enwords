#include <stdio.h>
#include <windows.h>

/*
dbを変更する実行ファイルを作る
ボタンを選択することで、dbへ登録、削除、検索を行う
それぞれeditを使う
*/

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    int nCmdShow){

    HWND hwnd = CreateWindow(
            TEXT("HOME") , TEXT("Kitty on your lap") ,
            WS_OVERLAPPEDWINDOW ,
            100 , 100 , 200 , 200 , NULL , NULL ,
            hInstance , NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd , SW_SHOW);
    
    return 0;
}