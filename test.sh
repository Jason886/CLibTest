
HOST=`uname`
if [ ${HOST} = Darwin ]; then
    AIENGINE=lib/aiengine/macosx-x86_64
elif [ ${HOST} = Linux ]; then
    LONG_BIT=`getconf LONG_BIT`
    if [ ${LONG_BIT} = 64 ]; then
        AIENGINE=lib/aiengine/linux-x86_64
    else
        AIENGINE=lib/aiengine/linux-x86
    fi
elif [ ${HOST:0:7} = MINGW32 ]; then
    AIENGINE=lib/aiengine/mingw-x86
elif [ ${HOST:0:7} =  MINGW64 ]; then
    AIENGINE=lib/aiengine/mingw-x86_64
else
    echo "cannot run at ${HOST}"
    exit 1
fi

export LD_LIBRARY_PATH=.:${AIENGINE}:${LD_LIBRARY_PATH}
./src/test

