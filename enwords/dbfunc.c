/* Processed by ecpg (17.4) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "dbfunc.pgc"
//mainから読みだすpgcファイル
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ecpglib.h>
#include <sqlca.h>

/*
connectまでの一連の処理(値を1つ取り出すプログラムより流用)
int main(void) {
    EXEC SQL BEGIN DECLARE SECTION;
        char dbname[] = "enwords";
        char user[] = "postgres";
        char pass[] = "pswd";
        char ver[512];
    EXEC SQL END DECLARE SECTION;

    EXEC SQL CONNECT TO :dbname USER :user USING :pass;

    EXEC SQL SELECT en INTO :ver FROM enwords WHERE finish = 'false';

    printf("false: %s\n", ver);

    EXEC SQL DISCONNECT;

    return 0;
}
*/




//変数に代入するときは : で中身を取り出す

//dbの出題済み(仮)の列をすべてboolean=falseにする.
void cleardb(void){
    /* exec sql begin declare section */
           
           
           
         
    
#line 38 "dbfunc.pgc"
 char dbname [] = "enwords" ;
 
#line 39 "dbfunc.pgc"
 char user [] = "postgres" ;
 
#line 40 "dbfunc.pgc"
 char pass [] = "PW:J6'*J}JrsdW4hJ:,mjzwaWcv" ;
 
#line 41 "dbfunc.pgc"
 char ver [ 512 ] ;
/* exec sql end declare section */
#line 42 "dbfunc.pgc"


    { ECPGconnect(__LINE__, 0, dbname , user , pass , NULL, 0); }
#line 44 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update enwords set finish = false where finish = true", ECPGt_EOIT, ECPGt_EORT);}
#line 45 "dbfunc.pgc"

    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 46 "dbfunc.pgc"

}
/*
//dbからレコードの個数を返す。
int countrecord(){
    EXEC SQL BEGIN DECLARE SECTION;
    int countrecord;
    EXEC SQL END DECLARE SECTION;
    EXEC SQL CONNECT TO enwords;
    EXEC SQL SELECT COUNT(*) INTO :countrecord FROM enwords;
    EXEC SQL DISCONNECT enwords;
    return countrecord;
}
*/

//dbから英単語+候補数分を返す
void getwords(int choices, char ans[][256]) {
    /* exec sql begin declare section */
           
           
           
         
    
#line 64 "dbfunc.pgc"
 char dbname [] = "enwords" ;
 
#line 65 "dbfunc.pgc"
 char user [] = "postgres" ;
 
#line 66 "dbfunc.pgc"
 char pass [] = "PW:J6'*J}JrsdW4hJ:,mjzwaWcv" ;
 
#line 67 "dbfunc.pgc"
 char ver [ 512 ] [ 256 ] ;
/* exec sql end declare section */
#line 68 "dbfunc.pgc"


    { ECPGconnect(__LINE__, 0, dbname , user , pass , NULL, 0); }
#line 70 "dbfunc.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select en from enwords where finish = false order by random ( ) limit 1", ECPGt_EOIT, 
	ECPGt_char,(ver[0]),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 72 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select jp from enwords where en = $1 ", 
	ECPGt_char,(ver[0]),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,(ver[1]),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 73 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update enwords set finish = true where en = $1 ", 
	ECPGt_char,(ver[0]),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 74 "dbfunc.pgc"

    for (int i = 2; i < choices + 1; i++) {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select en from enwords where en <> $1  order by random ( ) limit 1", 
	ECPGt_char,(ver[0]),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,(ver[i]),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 76 "dbfunc.pgc"

    }
    { ECPGtrans(__LINE__, NULL, "commit");}
#line 78 "dbfunc.pgc"


    for (int i = 0; i < choices + 1; i++) {
        strncpy(ans[i], ver[i],256);
        ans[i][255] = '\0';
    }
    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 84 "dbfunc.pgc"

}

/*
int insertwords(const char* jp,const char* en){
    EXEC SQL BEGIN DECLARE SECTION;
    char word_jp[100];
    char word_en[100];
    EXEC SQL END DECLARE SECTION;

    strncpy(word_jp, jp,sizeof(word_jp)-1); 
    word_jp[sizeof(word_jp)-1] = '\0';
    strncpy(word_en, en,sizeof(word_en)-1);
    word_en[sizeof(word_en)-1] = '\0'; 

    EXEC SQL CONNECT TO enwords;
    EXEC SQL INSERT INTO enwords (jp,en) VALUES (:word_jp,:word_en);
    EXEC SQL COMMIT; 
    EXEC SQL DISCONNECT enwords;
    //成功
    return 0;
}

int deletewords(const char* jp,const char* en){
    EXEC SQL BEGIN DECLARE SECTION;
    char word_jp[100];
    char word_en[100];
    EXEC SQL END DECLARE SECTION;

    strncpy(word_jp, jp,sizeof(word_jp)-1); 
    word_jp[sizeof(word_jp)-1] = '\0';
    strncpy(word_en, en,sizeof(word_en)-1);
    word_en[sizeof(word_en)-1] = '\0'; 

    EXEC SQL CONNECT TO enwords;
    EXEC SQL DELETE FROM enwords WHERE jp=:word_jp AND en=:word_en;
    EXEC SQL COMMIT; 
    EXEC SQL DISCONNECT enwords;
    //成功
    return 0;
}

int viewwords(void){
    //成功
    return 0;
}
*/