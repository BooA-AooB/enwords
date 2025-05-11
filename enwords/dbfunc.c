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
 char pass [] = "J6'*J}JrsdW4hJ:,mjzwaWcv" ;
/* exec sql end declare section */
#line 41 "dbfunc.pgc"


    { ECPGconnect(__LINE__, 0, dbname , user , pass , NULL, 0); }
#line 43 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update enwords set finish = false where finish = true", ECPGt_EOIT, ECPGt_EORT);}
#line 44 "dbfunc.pgc"

    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 45 "dbfunc.pgc"

}

//dbから英単語+候補数分を返す
void getwords(int choices, char ans[11][101]) {
    /* exec sql begin declare section */
           
           
           
         
    
#line 51 "dbfunc.pgc"
 char dbname [] = "enwords" ;
 
#line 52 "dbfunc.pgc"
 char user [] = "postgres" ;
 
#line 53 "dbfunc.pgc"
 char pass [] = "J6'*J}JrsdW4hJ:,mjzwaWcv" ;
 
#line 54 "dbfunc.pgc"
 char test [ 11 ] [ 101 ] ;
/* exec sql end declare section */
#line 55 "dbfunc.pgc"


    memset(test, 0, sizeof(char) * 11 * 101);
    
    { ECPGconnect(__LINE__, 0, dbname , user , pass , NULL, 0); }
#line 59 "dbfunc.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select en from enwords where finish = false order by random ( ) limit 1", ECPGt_EOIT, 
	ECPGt_char,(test[1]),(long)101,(long)1,(101)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 61 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select jp from enwords where en = $1 ", 
	ECPGt_char,(test[1]),(long)101,(long)1,(101)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,(test[0]),(long)101,(long)1,(101)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 62 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update enwords set finish = true where en = $1 ", 
	ECPGt_char,(test[1]),(long)101,(long)1,(101)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 63 "dbfunc.pgc"

    
    for (int i = 2; i < choices + 2; i++) {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select en from enwords where en <> $1  order by random ( ) limit 1", 
	ECPGt_char,(test[0]),(long)101,(long)1,(101)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,(test[i]),(long)101,(long)1,(101)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 66 "dbfunc.pgc"

    }
    
    for (int i = 2; i < choices+2; i++){
        strcpy_s(ans[i], sizeof(ans[i]), test[i]);
    }
    { ECPGtrans(__LINE__, NULL, "commit");}
#line 72 "dbfunc.pgc"

    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 73 "dbfunc.pgc"

}