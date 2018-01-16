#set -x
function Usage()
{
    echo "Usage: ${0##*/} OS ARCH"
    echo "    OS: linux macosx ios mingw android"
    echo "    ARCH: x86 x86_64 armv5 armv7 armv7s armv64"
}

OS=${1}
ARCH=${2}
if [ ${OS}x = x ]; then Usage; exit 1; fi
if [ ${ARCH}x = x ]; then Usage; exit 1; fi

LUA=../lib/lua/${OS}-${ARCH}
TOLUA=../lib/tolua/${OS}-${ARCH}

CFLAGS="-g -std=c99 -Wall -Wextra"
LIB_PATH="-L${LUA}/lib -L${TOLUA}/lib"
LIBS="-llua -ltolua"

HOST=`uname`
if [ ${HOST} = Linux ]; then
    LIBS="${LIBS} -ldl -lm"
fi 

AIENGINE=../lib/aiengine/${OS}-${ARCH}
LIB_PATH="${LIB_PATH} -L${AIENGINE}"
LIBS="${LIBS} -laiengine"

./bind.sh

gcc ${CFLAGS} -I. -c main.c -o main.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c test.c -o test.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c log.c -o log.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c File.c -o File.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c cJSON.c -o cJSON.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c luaJson.c -o luaJson.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c lua_bind.c -o lua_bind.o
gcc ${CFLAGS} -I. -I${LUA}/include -I${TOLUA}/include -c aiengine_wraper.c -o aiengine_wraper.o
gcc main.o test.o log.o File.o cJSON.o luaJson.o lua_bind.o aiengine_wraper.o -o test ${LIB_PATH} ${LIBS}

rm -rf *.o
