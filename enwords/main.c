#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONFIG_FILE "stataus.conf"

struct stataus{
    int choices;
    bool random;
};

struct stataus st;
bool returnhome;

//設定ファイルを読み込む
void readstataus(){
    
}

openhomewindow(){
    //設定ファイルを読み込み、値を保存

    //ホーム画面を呼び出す

}

/*
learn関数は、
選択肢が選ばれた際の判定、およびそれに伴う描画を行います。
judge関数はデータベースに選択肢が正解か不正解かを問い合わせます。
drawT関数は正解のメッセージボックスを表示し、drawF関数は不正解のメッセージボックスを表示します。
drawjudge関数はjudge関数の結果に応じて、正解ならdrawT()、不正解ならdrawF()を呼び出します。
*/


judge(){
    
}

//正解の描画を行う
drawT(){
    
}

//不正解の描画を行う
drawF(){
    
}

//判定結果によって描画を行う。
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
        //選択肢が選ばれたら正解か不正解かを判定し、描画する。
        drawjudge();
        //『ホームに戻る』が押されたら、ループを終了する
        if (returnhome==true){
            break;
        }
    }
}

main(){
    while(true)
    {
        //homeウィンドウを開く
        openhomewindow();
        returnhome=false;
        //問題の出題、回答ウィンドウを表示する。
        study();
    }
}