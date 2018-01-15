HOST=`uname`

OS=${1}
ARCH=${2}

LUA=../lib/lua/${OS}-${ARCH}
TOLUA=../lib/tolua/${OS}-${ARCH}
AIENGINE=../lib/aiengine/${OS}-${ARCH}

LIB="-L${LUA}/lib -L${TOLUA}/lib -L${AIENGINE} -llua -ltolua -laiengine"
CFLAGS="-g -std=c99 -Wall -Wextra"
if [ ${HOST} = Linux ]; then
    LIB="${LIB} -ldl -lm"
fi 

gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c cJSON.c -o cJSON.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c aiengine_wraper.c -o aiengine_wraper.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c lua_bind.c -o lua_bind.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c test.c -o test.o
gcc ${CFLAGS} -I. -c main.c -o main.o
#gcc test.o main.o cJSON.o lua_bind.o aiengine_wraper.o -o ../test ${LIB}

rm -rf *.o
