cc=gcc
pgc=ecpg

#enwords(問題の出題、回答)を作成する
enwords: main.o dbfunc.o
		$(cc) -o edit main.o dbfunc.o

#changedb(問題の登録、削除、検索)を作成する
changedb: changedb.o dbfunc.o
		$(cc) -o edit changedb.o dbfunc.o

main.o: main.c
		$(cc) -c main.c 

dbfunc.o: dbfunc.c
		$(cc) -c dbfunc.c

dbfunc.c: dbfunc.pgc
		$(pgc) dbfunc.pgc

changedb.o: changedb.c
		$(cc) -c changedb.c