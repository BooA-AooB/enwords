#define UNICODE
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONFIG_FILE "stataus.conf"

//stataus.confを入れる構造体
struct stataus{
    int choices;
    bool random;
};

struct stataus st;
bool returnhome;
HINSTANCE hInstancea;

//設定ファイルを読み込む
void readstataus(){
    FILE *fin;
    char line[128];
    char* str;
    char* key[128];
    char* value[128];
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
        if(key=="choices"){
            st.choices=value;
        }
        else if(key=="random"){
            st.random=value;
        }
    }
    fclose(fin);
    return ;
}

openhomewindow(){
    //設定ファイルを読み込み、値を構造体に保存
    readstataus();
    //ウィンドウと『問題を出題する』ボタンを作成する
    HWND hwnd = CreateWindow(
    TEXT("HOME"),TEXT("HOME"),
    WS_CAPTION,960,540,200,200,NULL,NULL,hInstancea,NULL);
}

/*
選択肢が選ばれた際の判定、およびそれに伴う描画を行います
judge関数はデータベースに選択肢が正解か不正解かを問い合わせます
drawT関数は正解のメッセージボックスを表示し、drawF関数は不正解のメッセージボックスを表示します
drawjudge関数はjudge関数の結果に応じて、正解ならdrawT()、不正解ならdrawF()を呼び出します
*/


judge(){
    
}

//正解の描画を行う
drawT(){
    MessageBox(NULL , TEXT("正解") ,
			TEXT("判定") , MB_ICONINFORMATION);
}

//不正解の描画を行う
drawF(){
    MessageBox(NULL , TEXT("不正解") ,
			TEXT("判定") , MB_ICONINFORMATION);
}

//判定結果によって描画を行う
void drawjudge(){
    bool answer;
    answer=judge();
    if (answer==true)
    {
        drawT();
    }
    else
    {
        drawF();
    }   
}

void study(){
    bool returnhome=false;
    while (true)
    {
        //候補の数に合うように描画する
        //候補、回答を取得する.回答は配列の0番目
        char** ans;
        ans=getwords(st.choices,st.random);
        //選択肢が選ばれたら正解か不正解かを判定し、描画する
        drawjudge();
        //『ホームに戻る』が押されたら、ループを終了する
        free(ans);
        if (returnhome==true){
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
        openhomewindow();
        returnhome=false;
        //問題の出題、回答ウィンドウを表示する
        study();
    }
    return 0;
}