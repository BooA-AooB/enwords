//enwords実行ファイルのmainファイル
#define UNICODE
#define BUTTON_ID1 0
#define BUTTON_ID2 1
#define BUTTON_ID3 2
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONFIG_FILE "stataus.conf"

/*
part1
設定ファイルから出題をランダムにするか、出題する問題数を取得し、構造体に渡す
ホームウィンドウを描画する
問題を出題ボタンを押すと、画面を破棄して次の動作を行う
*/


//stataus.confを入れる構造体
struct stataus{
    int choices;
    bool random;
};

struct stataus st;
//HOMEに戻るかのフラグ
bool returnhome;
HINSTANCE hInstancea;
//ボタンが押されたかどうかのフラグ
bool clickbutton=FALSE;

//設定ファイルを読み込む
void readstataus(){
    FILE *fin;
    char line[128];
    char* str;
    char key[128];
    char value[128];
    if ((fin=fopen(CONFIG_FILE,"r"))==NULL){
        return -1;
    }

    //fgets(char *srting,int n,FILE *stream); 
    //fgetsは最初の"\n" or "EOF" or 読み込まれた文字数がn-1までの文字を戦闘から読み取る
    //結果は*stringに入れる
    while(str=fgets(line,128,fin)!=NULL){
        //sscanf(const char *buffer, const char *format, argument-list);
        //bufferからargument-list で指定された位置へ、データを読み取る
        //%[^=]は、=を格納しないの意.=を区切りとして前後をkey,valueに格納
        sscanf(line,"%[^=]=%s", key, value);
        //choicesのvalueは整数
        //strcmpの戻り値は成功ならば0
        if(strcmp(key,"choices")==0){
            st.choices=value;
        }
        else if(key=="random"){
            st.random=value;
        }
    }
    fclose(fin);
}

//HOMEウィンドウボタンの描画
LRESULT CALLBACK WndProcHOME(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	switch (msg) {
    case WM_COMMAND:
        switch(LOWORD(wp)) {
            case BUTTON_ID1:
                clickbutton=TRUE;
                DestroyWindow(hwnd);
                break;
            }
	}
	return DefWindowProc(hwnd , msg , wp , lp);
}

void openhomewindow(HINSTANCE hInstancea){
    HWND hwnd;
    MSG msg;
	WNDCLASS winc;
    winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProcHOME;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstancea;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("HOME");

    if (!RegisterClass(&winc)) return -1;
    //設定ファイルを読み込み、値を構造体に保存
    readstataus();
    //ウィンドウと『問題を出題する』ボタンを作成する
    hwnd = CreateWindow(
    TEXT("HOME"),TEXT("HOME"),
    WS_CAPTION,960,540,100,100,NULL,NULL,hInstancea,NULL);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    CreateWindow(
        TEXT("BUTTON") , TEXT("Kitty") ,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        0 , 0 , 100 , 50 ,
        hwnd , (HMENU)BUTTON_ID1 , hInstancea , NULL
    );
    while (!clickbutton && GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

/*
part2
選択肢が選ばれた際の判定、およびそれに伴う描画を行います
judge関数はデータベースに選択肢が正解か不正解かを問い合わせます
正解ならばdrawに正解を渡し、そうでないならば不正解を渡す
*/

☆
//正解、不正解の判定を行う
bool judge(){
    return true;
    return false;
}

//判定結果によって描画を行う
void drawjudge(){
    bool answer;
    LPCWSTR draw;
    answer=judge();
    if (answer==true)
    {
        draw=L"正解";
    }
    else
    {
        draw=L"不正解";
    }
    MessageBox(NULL , draw ,
			TEXT("判定") , MB_ICONINFORMATION);
}

☆

//BASEウィンドウボタンの描画
LRESULT CALLBACK WndProcBASE(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd , msg , wp , lp);
}

int drawBase(HINSTANCE hInstancea){
    HWND hwnd;
    MSG msg;
	WNDCLASS winc;
    winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProcBASE;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstancea;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("BASE");

    if (!RegisterClass(&winc)) return -1;

    hwnd = CreateWindow(
        TEXT("BASE") , TEXT("question") ,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
        CW_USEDEFAULT , CW_USEDEFAULT ,
        CW_USEDEFAULT , CW_USEDEFAULT ,
        NULL , NULL , hInstancea , NULL
    );

    CreateWindow(
        TEXT("BUTTON") , TEXT("Kitty") ,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        0 , 0 , 100 , 50 ,
        hwnd , (HMENU)BUTTON_ID2 , hInstancea , NULL
    );
    CreateWindow(
        TEXT("BUTTON") , TEXT("Kitty") ,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        0 , 0 , 100 , 50 ,
        hwnd , (HMENU)BUTTON_ID3 , hInstancea , NULL
    );
    while(GetMessage(&msg , NULL , 0 , 0)) DispatchMessage(&msg);

	return msg.wParam;
}

void study(HINSTANCE hInstancea){
    bool returnhome=false;
    while (true)
    {
        //候補の数に合うように描画する
        drawBase(hInstancea);
        //候補、回答を取得する.回答は配列の0番目
        char** ans;
        ans=getwords(st.choices,st.random);
        //選択肢が選ばれたら正解か不正解かを判定し、描画する
        drawjudge();
        //『ホームに戻る』が押されたら、ループを終了する
        free(ans);
        if (returnhome == true){
            break;
        }
    }
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    int nCmdShow){
    
    HINSTANCE hInstancea = hInstance;
    while(true)
    {
        cleardb();
        //homeウィンドウを開く
        openhomewindow(hInstancea);
        returnhome=false;
        //問題の出題、回答ウィンドウを表示する
        study(hInstancea);
    }
    return 0;
}