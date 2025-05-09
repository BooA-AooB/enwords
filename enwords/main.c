//enwords実行ファイルのmainファイル
//『☆彡』は途中
#define UNICODE
#define BUTTON_ID1 0
#define BUTTON_ID2 1
#define BUTTON_ID3 2
#define BUTTON_ID4 3
#define BUTTON_ANSWER 99
#define BUTTON_ERROR 90
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
bool clickbutton=false;
//ウィンドウを閉じるかのフラグ
bool endflag=false;
//問題の回答したか、正解かのフラグ
bool end=false;
bool answer=false;
//出題数、正解数
int question=0; 
int correct=0;
LPCWSTR rate[256];

//設定ファイルを読み込む
int readstataus(){
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
    return 0;
}

//HOMEウィンドウボタンの描画
LRESULT CALLBACK WndProcHOME(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
    switch (msg) {
    case WM_COMMAND:
        switch(LOWORD(wp)) {
            //問題へ
            case BUTTON_ID1:
                clickbutton=true;
                DestroyWindow(hwnd);
                break;
            //CHECKを表示するメッセージウィンドウ
            case BUTTON_ID3:
                MessageBox(NULL , rate ,
                    TEXT("CHECK") , MB_ICONINFORMATION);
                break;
        }
	}
	return DefWindowProc(hwnd , msg , wp , lp);
}

int openhomewindow(HINSTANCE hInstancea){
    HWND hwnd;
    MSG msg;

    //設定ファイルを読み込み、値を構造体に保存
    readstataus();
    //ウィンドウと『問題を出題する』ボタンを作成する
    hwnd = CreateWindow(
    TEXT("HOME"),TEXT("HOME"),
    WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
    CW_USEDEFAULT , CW_USEDEFAULT ,
    CW_USEDEFAULT , CW_USEDEFAULT ,NULL,NULL,hInstancea,NULL);
    swprintf(rate, 256, L"%d/%d", correct, question);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    CreateWindow(
        TEXT("BUTTON") , TEXT("START") ,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        0 , 0 , 300 , 100 ,
        hwnd , (HMENU)BUTTON_ID1 , hInstancea , NULL
    );
    CreateWindow(
        TEXT("BUTTON") , TEXT("CHECK") ,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        0 , 100 , 300 , 50 ,
        hwnd , (HMENU)BUTTON_ID3 , hInstancea , NULL
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

//判定結果によって描画を行う
void drawjudge(){
    LPCWSTR draw;
    if (answer==true)
    {
        draw=L"正解";
    }
    else
    {
        draw=L"不正解";
    }
    MessageBox(NULL , draw ,
			TEXT("CHECK") , MB_ICONINFORMATION);
}

//BASEウィンドウボタンの描画
LRESULT CALLBACK WndProcBASE(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
    switch (msg) {
	    case WM_COMMAND:
            switch(LOWORD(wp)) {
                //HOMEに戻る
                case BUTTON_ID2:
                    returnhome=true;
                    DestroyWindow(hwnd);
                    break;
                //CHECKを表示するメッセージウィンドウ
                case BUTTON_ID3:
                    MessageBox(NULL , rate ,
                        TEXT("CHECK") , MB_ICONINFORMATION);
                    break;
                //次の問題へ
                case BUTTON_ID4:
                    endflag=true;
                    DestroyWindow(hwnd);
                    break;
                //判定
                case BUTTON_ANSWER:
                    answer=true;
                    end = true;
                    correct++;
                    break;
                case BUTTON_ERROR:
                    end = true;
                    break;
                }
	}
	return DefWindowProc(hwnd , msg , wp , lp);
}

//ansをシャッフルする
void shuffle(char ans[256][256]) {
    for (int i = st.choices; i > 1; i--) {
        int j = 1 + rand() % i; // 1 から i-1 の間で選ぶ
        char tmp[256];
        strcpy_s(tmp,256, ans[i]);
        strcpy_s(ans[i],256, ans[j]);
        strcpy_s(ans[j], 256,tmp);
    }

}


int drawBase(HINSTANCE hInstancea, char** ans) {
    HWND hwnd;
    MSG msg;
    question++;

    hwnd = CreateWindow(
        TEXT("BASE") , TEXT("question") ,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
        CW_USEDEFAULT , CW_USEDEFAULT ,
        CW_USEDEFAULT , CW_USEDEFAULT ,
        NULL , NULL , hInstancea , NULL
    );
    swprintf(rate, 256, L"%d/%d", correct, question);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    //HOMEに戻るボタンを作成する
    CreateWindow(
        TEXT("BUTTON") , TEXT("HOME") ,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        0 , 0 , 300 , 50 ,
        hwnd , (HMENU)BUTTON_ID2 , hInstancea , NULL
    );
    
    CreateWindow(
        TEXT("BUTTON") , TEXT("CHECK") ,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        0 , 50 , 300 , 50 ,
        hwnd , (HMENU)BUTTON_ID3 , hInstancea , NULL
    );
    
    CreateWindow(
        TEXT("BUTTON") , TEXT("NEXT") ,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        0 , 100 , 300 , 50 ,
        hwnd , (HMENU)BUTTON_ID4 , hInstancea , NULL
    );
    
    //乱数でバラバラの順番にしたものを出題する。
    srand((unsigned int)time(NULL));
    char cache[256];
    strncpy_s(cache,256,ans[1],256);
    if (strcmp(cache, ans[1]) == 0) {
        MessageBox(NULL, TEXT("A"),
            TEXT("CHECK"), MB_ICONINFORMATION);
    }
    /*
    shuffle(ans);
    for (int i = 1; i < 4; i++) {
        wchar_t wbuf[256];
        MultiByteToWideChar(CP_UTF8, 0, ans[i], -1, wbuf, 256);

        if (strcmp(cache, ans[i]) == 0) {
            CreateWindow(
                TEXT("Button"),
                wbuf,
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 200 + i * 50,
                300, 50,
                hwnd, (HMENU)BUTTON_ANSWER, hInstancea, NULL
            );
        }
        
        else {
            CreateWindow(
                TEXT("Button"),
                wbuf,
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 200 + i * 50,
                300, 50,
                hwnd, NULL, hInstancea, NULL
            );
        }
    }
    */

    while (!returnhome && !endflag && !end && GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void study(HINSTANCE hInstancea){
    while (true)
    {
        answer=false;
        endflag=false;
        end=false;
        //候補、回答を取得する.回答は配列の0番目
        char ans[2][256];
        getwords(st.choices,ans);
        //候補の数に合うように描画する
        drawBase(hInstancea, ans);
        //選択肢が選ばれたら正解か不正解かを判定し、描画する
        if (end==true){
            drawjudge();
        }
        //『ホームに戻る』が押されたら、ループを終了する
        if (returnhome == true){
            break;
        }
    }
}

int RegisterClassHOME(){
    //初期化していないと不定なので、設定漏れのために初期化するらしい
	WNDCLASS winc = {0};
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
    return 0;
}

int RegisterClassBASE(){
    WNDCLASS winc={0};
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
    return 0;
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    int nCmdShow){
    
    hInstancea = hInstance;
    
    RegisterClassHOME();
    RegisterClassBASE();
    cleardb();
    while(true)
    {
        //homeウィンドウを開く
        clickbutton=false;
        openhomewindow(hInstancea);
        returnhome=false;
        //問題の出題、回答ウィンドウを表示する
        study(hInstancea);
    }
    return 0;
}