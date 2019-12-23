#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "engine.h"

#define SIRINA 1920
#define VISINA 1080

#define KORAK 9
#define LKORAK 10
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define IZMEDJU(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define MAXPOENI 7

int x, y, rnd, poeni1, poeni2, brigraca = 1, delta;
void init(int rand, int nigr, int delta);

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
    p->y = IZMEDJU(p->y + p->v * delta / 16, 0, VISINA - p->vis);
    //p->y = max(min(p->y + p->v, VISINA - p->vis), 0);
}

void automatskipomeri(pravougaonik *p) {
    p->y = IZMEDJU(((p->y + p->vis / 2 - l.y) > 0 ? p->y - KORAK * delta / 16 : p->y + KORAK * delta / 16), 0, VISINA - p->vis);
    //p->y = max(min(p->y + p->v, VISINA - p->vis), 0);
}

void lpomeri(lopta *l) {
    if (l->y + l->vy + l->r > VISINA || l->y + l->vy - l->r < 0)
        l->vy = -l->vy;

    if ((l->x + l->vx - l->r < i1.x + i1.sir && l->x + l->vx - l->r > i1.x && l->y > i1.y && l->y < i1.y + i1.vis))
        l->vx = -l->vx;
    if ((l->x + l->vx + l->r > i2.x && l->x + l->vx + l->r < i2.x + i2.sir && l->y > i2.y && l->y < i2.y + i2.vis))
        l->vx = -l->vx;

    l->y += l->vy * delta / 16;
    l->x += l->vx * delta / 16;
}

void pnum(int x, int y, int n, int ci) {
    EM_ASM({
        let ctx = gameCanvas.getContext("2d");
        ctx.font = "50px Arial";
        ctx.fillStyle = colors[$3];
        ctx.textAlign = "center";
        ctx.fillText($2, $0, $1);
    },
           x, y, n, ci);
}

void reset() {
    rnd++;

    l.x = SIRINA / 2;
    l.y = VISINA / 2;
    l.r = i1.sir / 2;

    switch (rnd % 4) {
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

void poen(int i) {
    switch (i) {
    case 0:
        poeni2 += 1;
        reset();
        if (poeni2 >= MAXPOENI) {
            printf("pobedio je drugi\n");
            init(++rnd, brigraca, delta);
        }
        break;

    case 1:
        poeni1 += 1;
        reset();
        if (poeni1 >= MAXPOENI) {
            printf("pobedio je prvi\n");
            init(++rnd, brigraca, delta);
        }
        break;

    default:
        break;
    }
}

//INICIJALIZACIJA IGRICE
void init(int rand, int nigr, int dlt) {
    poeni1 = poeni2 = 0;
    delta = dlt;

    brigraca = nigr;

    rnd = rand;
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

int main() {
    EM_ASM({
        load();
    });
    return 0;
}

void petlja(char *keydown, char *keyup, int dlt) {
    delta = dlt;
    cls();
    pomeri(&i1);
    if (brigraca == 1)
        automatskipomeri(&i2);
    else
        pomeri(&i2);

    lpomeri(&l);

    if (l.x < 0)
        poen(0);

    if (l.x > SIRINA)
        poen(1);

    pnum(SIRINA / 4, VISINA / 10, poeni1, 0);
    pnum(SIRINA * 3 / 4, VISINA / 10, poeni2, 0);

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
            case 'R':
                init(++rnd, brigraca, delta);
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
emcc -I .\wasm\sources .\wasm\sources\igra.c .\wasm\sources\engine.c -o .\wasm\binary\wasm.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_petlja','_init','_puts','_main']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']"

emcc -I ./wasm/sources ./wasm/sources/igra.c ./wasm/sources/engine.c -o ./wasm/binary/wasm.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_petlja','_init','_puts','_main']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']" 
*/

// gore-'&'
// dole-'('