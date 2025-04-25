cc=gcc
pgc=ecpg

enwords: main.o dbfunc.o
		$(cc) -o edit main.o dbfunc.o

main.o: main.c
		$(cc) -c main.c 

dbfunc.o: dbfunc.c
		$(cc) -c dbfunc.c

main.c: dbfunc.pgc
		$(pgc) dbfunc.pgc