#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "engine.h"

#define SIRINA 1920
#define VISINA 1080

#define KORAK 10
#define LKORAK 5
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define IZMEDJU(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

int x, y;

typedef struct {
    int x;
    int y;
    int sir;
    int vis;
    int v;
} pravougaonik;

typedef struct {
    int x;
    int y;
    int r;
    int vx;
    int vy;
} lopta;

void ctrprv(pravougaonik p) {
    rect(p.x, p.y, p.sir, p.vis, 0);
}

void crtlpt(lopta l) {
    circ(l.x, l.y, l.r, 0);
}

pravougaonik i1, i2;
lopta l;

void pomeri(pravougaonik *p) {
    p->y = IZMEDJU(p->y + p->v, 0, VISINA - p->vis);
    //p->y = max(min(p->y + p->v, VISINA - p->vis), 0);
}

void lpomeri(lopta *l, pravougaonik i1, pravougaonik i2){
    if ((l->y + l->vy - l->r < 0) || (l->y + l->vy + l->r > VISINA)) {
        l->vy *= -1;
    }

    if (l->x + l->vx - l->r <= i1.x + i1.sir) {
        if(l->y >= i1.y && l->y <= i1.y + i1.vis) {
            l->vx *= -1;
        }
        else {
            printf("Igrac 1 je izgubio!");
        }
        
    }

    if ((l->x + l->vx + l->r >= i2.x)) {
        if(l->y >= i2.y && l->y <= i2.y + i2.vis) {
            l->vx *= -1;
        }
        else {
            printf("Igrac 2 je izgubio!");
        }
    }
    
    l->x+=l->vx;
    l->y+=l->vy;
}

void init(int rand) {
    i1.v = i2.v = 0;
    i1.sir = i2.sir = SIRINA / 100;
    i1.vis = i2.vis = VISINA / 10;
    i1.x = SIRINA / 10 - i1.sir;
    i2.x = SIRINA * 9 / 10 - i2.sir;
    i1.y = i2.y = (VISINA - i1.vis) / 2;

    l.x = SIRINA / 2;
    l.y = VISINA / 2;
    l.r = i1.sir / 2;



    switch (rand % 4) {
    case 0:
        l.vx = LKORAK;
        l.vy = LKORAK;
        break;
    case 1:
        l.vx = -LKORAK;
        l.vy = LKORAK;
        break;
    case 2:
        l.vx = LKORAK;
        l.vy = -LKORAK;
        break;
    case 3:
        l.vx = -LKORAK;
        l.vy = -LKORAK;
        break;

    default:
        break;
    }
}

void petlja(char *keydown, char *keyup) {
    cls();
    pomeri(&i1);
    pomeri(&i2);

    lpomeri(&l, i1, i2);

    ctrprv(i1);
    ctrprv(i2);
    crtlpt(l);
    int duz = (int)*keydown;

    if (duz != 0) {
        for (int i = 1; i < duz + 1; i++) {
            switch (keydown[i]) {
            case 'W':
                i1.v = -KORAK;
                break;
            case 'S':
                i1.v = KORAK;
                break;
            case '&':
                i2.v = -KORAK;
                break;
            case '(':
                i2.v = KORAK;
                break;
            default:
                break;
            }
        }
    }
    duz = (int)*keyup;
    if (duz != 0) {
        for (int i = 1; i < duz + 1; i++) {
            switch (keyup[i]) {
            case 'W':
                if (i1.v < 0)
                    i1.v = 0;
                break;
            case 'S':
                if (i1.v > 0)
                    i1.v = 0;
                break;
            case '&':
                if (i2.v < 0)
                    i2.v = 0;
                break;
            case '(':
                if (i2.v > 0)
                    i2.v = 0;
                break;
            default:
                break;
            }
        }
    }
}

/*
python -m http.server 8080

emcc .\wasm\sources\igra.c -o .\wasm\binary\test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_test','_puts']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']" 
emcc -I .\wasm\sources .\wasm\sources\igra.c .\wasm\sources\engine.c -o .\wasm\binary\test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_petlja','_init','_puts']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']"

emcc -I ./wasm/sources ./wasm/sources/igra.c ./wasm/sources/engine.c -o ./wasm/binary/test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_petlja','_init','_puts']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']" 
*/

// gore-'&'
// dole-'('