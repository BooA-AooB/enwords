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

//dbからレコードの個数を返す。
int countrecord(){
    /* exec sql begin declare section */
     
    
#line 18 "dbfunc.pgc"
 int countrecord ;
/* exec sql end declare section */
#line 19 "dbfunc.pgc"

    { ECPGconnect(__LINE__, 0, "enwords" , NULL, NULL , NULL, 0); }
#line 20 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( * ) from enwords", ECPGt_EOIT, 
	ECPGt_int,&(countrecord),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 21 "dbfunc.pgc"

    { ECPGdisconnect(__LINE__, "enwords");}
#line 22 "dbfunc.pgc"

    return countrecord;
}

//dbから英単語+候補数分を返す
int getwords(int choices,bool random){
    /* exec sql begin declare section */
     
    
#line 29 "dbfunc.pgc"
 char * ans [ 256 ] ;
/* exec sql end declare section */
#line 30 "dbfunc.pgc"


    { ECPGconnect(__LINE__, 0, "enwords" , NULL, NULL , NULL, 0); }
#line 32 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select en from enwords where finish = false order by random ( ) limit 1", ECPGt_EOIT, 
	ECPGt_char,&(ans[0]),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 33 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select jp from enwords where en = $1 ", 
	ECPGt_char,&(ans[0]),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,&(ans[1]),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 34 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update enwords set finish = true", ECPGt_EOIT, ECPGt_EORT);}
#line 35 "dbfunc.pgc"

    for (int i=2;i<choices;i++){
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select en from enwords where en <> $1  order by random ( ) limit 1", 
	ECPGt_char,&(ans[0]),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,&(ans[i]),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 37 "dbfunc.pgc"

    }
    { ECPGtrans(__LINE__, NULL, "commit");}
#line 39 "dbfunc.pgc"
 
    { ECPGdisconnect(__LINE__, "enwords");}
#line 40 "dbfunc.pgc"

    //0に正解を入れる
    return ans;
}

int insertwords(const char* jp,const char* en){
    /* exec sql begin declare section */
     
     
    
#line 47 "dbfunc.pgc"
 char word_jp [ 100 ] ;
 
#line 48 "dbfunc.pgc"
 char word_en [ 100 ] ;
/* exec sql end declare section */
#line 49 "dbfunc.pgc"


    strncpy(word_jp, jp,sizeof(word_jp)-1); 
    word_jp[sizeof(word_jp)-1] = '\0';
    strncpy(word_en, en,sizeof(word_en)-1);
    word_en[sizeof(word_en)-1] = '\0'; 

    { ECPGconnect(__LINE__, 0, "enwords" , NULL, NULL , NULL, 0); }
#line 56 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into enwords ( jp , en ) values ( $1  , $2  )", 
	ECPGt_char,(word_jp),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(word_en),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 57 "dbfunc.pgc"

    { ECPGtrans(__LINE__, NULL, "commit");}
#line 58 "dbfunc.pgc"
 
    { ECPGdisconnect(__LINE__, "enwords");}
#line 59 "dbfunc.pgc"

    //成功
    return 0;
}

int deletewords(const char* jp,const char* en){
    /* exec sql begin declare section */
     
     
    
#line 66 "dbfunc.pgc"
 char word_jp [ 100 ] ;
 
#line 67 "dbfunc.pgc"
 char word_en [ 100 ] ;
/* exec sql end declare section */
#line 68 "dbfunc.pgc"


    strncpy(word_jp, jp,sizeof(word_jp)-1); 
    word_jp[sizeof(word_jp)-1] = '\0';
    strncpy(word_en, en,sizeof(word_en)-1);
    word_en[sizeof(word_en)-1] = '\0'; 

    { ECPGconnect(__LINE__, 0, "enwords" , NULL, NULL , NULL, 0); }
#line 75 "dbfunc.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from enwords where jp = $1  and en = $2 ", 
	ECPGt_char,(word_jp),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(word_en),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 76 "dbfunc.pgc"

    { ECPGtrans(__LINE__, NULL, "commit");}
#line 77 "dbfunc.pgc"
 
    { ECPGdisconnect(__LINE__, "enwords");}
#line 78 "dbfunc.pgc"

    //成功
    return 0;
}

int viewwords(void){
    //成功
    return 0;
}