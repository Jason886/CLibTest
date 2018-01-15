../tools/tolua -o bind.c -H bind.h bind.pkg
gcc -I. -I../lib/lua/macosx-x86_64/include -I../lib/tolua/macosx-x86_64/include -c bind.c -o bind.o
gcc -I. -I../lib/lua/macosx-x86_64/include -I../lib/tolua/macosx-x86_64/include -c test.c -o test.o
gcc -I. -c main.c -o main.o
gcc main.o test.o bind.o -L../lib/lua/macosx-x86_64/lib -L../lib/tolua/macosx-x86_64/lib -o ../test -llua -ltolua
