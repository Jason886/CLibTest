#!/bin/bash

sed -i '147a\  pthread_mutex_t lock;' src/lstate.h
sed -i '14a\#include <pthread.h>' src/lstate.h

sed -i '306a\  pthread_mutex_init(\&g->lock, NULL);' src/lstate.c
sed -i '232a\  pthread_mutex_unlock(\&g->lock);\n  pthread_mutex_destroy(\&g->lock);' src/lstate.c

sed -i 's/^#define lua_lock(L).*$/#define lua_lock(L) {pthread_mutex_lock(\&(G(L)->lock));}/' src/llimits.h
sed -i 's/^#define lua_unlock(L).*$/#define lua_unlock(L) {pthread_mutex_unlock(\&(G(L)->lock));}/' src/llimits.h


