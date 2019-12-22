#include <stdio.h>
#define SIRINA 1920
#define VISINA 1080


void test(){
    printf("Hello World!\n");
}
/*
emcc igra.c -o ..\binary\test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_main','_puts']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']"
*/