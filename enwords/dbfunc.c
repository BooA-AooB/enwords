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

//変数に代入するときは : で中身を取り出す

//dbの出題済み(仮)の列をすべてboolean=falseにする.
void cleardb(void){
    { ECPGconnect(__LINE__, 0, "enwords" , NULL, NULL , NULL, 0); }
#line 10 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update enwords set finish = false where finish = true", ECPGt_EOIT, ECPGt_EORT);}
#line 11 "dbfunc.pgc"

    { ECPGdisconnect(__LINE__, "enwords");}
#line 12 "dbfunc.pgc"

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
int getwords(int choices,bool random){
    /* exec sql begin declare section */
      
         
         
     
    
#line 33 "dbfunc.pgc"
 struct varchar { 
#line 31 "dbfunc.pgc"
 int len ;
 
#line 32 "dbfunc.pgc"
 char arr [ 100 ] ;
 } ans [ 256 ] ;
/* exec sql end declare section */
#line 34 "dbfunc.pgc"

    
    char** result = malloc(sizeof(char*) * (choices + 1));
    for (int i = 0; i < choices + 1; ++i) {
        result[i] = malloc(100); 
    }
    
    { ECPGconnect(__LINE__, 0, "enwords" , NULL, NULL , NULL, 0); }
#line 41 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select en from enwords where finish = false order by random ( ) limit 1", ECPGt_EOIT, 
	ECPGt_int,&(ans[0].len),(long)1,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(ans[0].arr),(long)100,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 42 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select jp from enwords where en = $1  ,  $2 ", 
	ECPGt_int,&(ans[0].len),(long)1,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(ans[0].arr),(long)100,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_int,&(ans[1].len),(long)1,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(ans[1].arr),(long)100,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 43 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update enwords set finish = true where en = $1  ,  $2 ", 
	ECPGt_int,&(ans[0].len),(long)1,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(ans[0].arr),(long)100,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 44 "dbfunc.pgc"

    for (int i=2;i<choices;i++){
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select en from enwords where en <> $1  ,  $2  order by random ( ) limit 1", 
	ECPGt_int,&(ans[0].len),(long)1,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(ans[0].arr),(long)100,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_int,&(ans[i].len),(long)1,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(ans[i].arr),(long)100,(long)1,sizeof( struct varchar ), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 46 "dbfunc.pgc"

    }
    { ECPGtrans(__LINE__, NULL, "commit");}
#line 48 "dbfunc.pgc"
 
    { ECPGdisconnect(__LINE__, "enwords");}
#line 49 "dbfunc.pgc"

    //0に正解を入れる
    for (int i = 0; i < choices + 1; ++i){
        strncpy(result[i], ans[i].arr, ans[i].len);
        result[i][ans[i].len] = '\0';  // null終端
    }
    return ans;
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