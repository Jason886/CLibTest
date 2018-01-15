HOST=`uname`
LUA=../lib/lua/linux-x86_64
TOLUA=../lib/tolua/linux-x86_64
LIB="-L${LUA}/lib -L${TOLUA}/lib -L../lib -llua -ltolua -laiengine"
CFLAGS="-std=c99 -Wall -Wextra"
if [ ${HOST} = Linux ]; then
    LIB="${LIB} -ldl -lm"
fi 

gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c aiengine_wraper.c -o aiengine_wraper.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c lua_bind.c -o lua_bind.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c test.c -o test.o
gcc ${CFLAGS} -I. -c main.c -o main.o
gcc main.o test.o lua_bind.o -o ../test ${LIB}
