#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "engine.h"

#define SIRINA 1920
#define VISINA 1080

int x, y;

typedef struct {
    int x;
    int y;
    int sir;
    int vis;
} pravougaonik;

typedef struct {
    int x;
    int y;
    int r;
} lopta;

void ctrprv(pravougaonik p) {
    //printf("%d %d %d %d\n", p.x,p.y,p.sir,p.vis);
    rect(p.x, p.y, p.sir, p.vis, 0);
}

void crtlpt(lopta l) {
    circ(l.x, l.y, l.r, 0);
}

pravougaonik i1, i2;
lopta l;

void init() {
    i1.y = i2.y = VISINA / 2;
    i1.sir = i2.sir = SIRINA / 100;
    i1.vis = i2.vis = VISINA / 10;
    i1.x = SIRINA / 10 - i1.sir;
    i2.x = SIRINA * 9 / 10 - i2.sir;

    l.x = SIRINA / 2;
    l.y = VISINA / 2;
    l.r = i1.sir / 2;
}

void petlja() {
    cls();
    ctrprv(i1);
    ctrprv(i2);
    crtlpt(l);
}
/*
emcc .\wasm\sources\igra.c -o .\wasm\binary\test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_test','_puts']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']"
emcc -I .\wasm\sources .\wasm\sources\igra.c .\wasm\sources\engine.c -o .\wasm\binary\test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_petlja','_init','_puts']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']"
*/