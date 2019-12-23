#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "engine.h"

#define SIRINA 1920
#define VISINA 1080

#define KORAK 10

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
} lopta;

int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a > b) ? a : b; }

void ctrprv(pravougaonik p) {
  // printf("%d %d %d %d\n", p.x,p.y,p.sir,p.vis);
  rect(p.x, p.y, p.sir, p.vis, 0);
}

void crtlpt(lopta l) { circ(l.x, l.y, l.r, 0); }

pravougaonik i1, i2;
lopta l;

void init() {
  i1.v = i2.v = 0;
  i1.sir = i2.sir = SIRINA / 100;
  i1.vis = i2.vis = VISINA / 10;
  i1.x = SIRINA / 10 - i1.sir;
  i2.x = SIRINA * 9 / 10 - i2.sir;
  i1.y = i2.y = (VISINA - i1.vis) / 2;

  l.x = SIRINA / 2;
  l.y = VISINA / 2;
  l.r = i1.sir / 2;
}

void move(pravougaonik *p) { p->y = max(min(p->y + p->v, VISINA - p->vis), 0); }

void petlja(char *keydown, char *keyup) {
  cls();
  move(&i1);
  move(&i2);

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
          if (i1.v < 0) i1.v = 0;
          break;
        case 'S':
          if (i1.v > 0) i1.v = 0;
          break;
        case '&':
          if (i2.v < 0) i2.v = 0;
          break;
        case '(':
          if (i2.v > 0) i2.v = 0;
          break;
        default:
          break;
      }
    }
  }
}
/*
emcc .\wasm\sources\igra.c -o .\wasm\binary\test.js -s WASM=1 -s
EXPORTED_FUNCTIONS="['_test','_puts']" -s
EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']" emcc -I .\wasm\sources
.\wasm\sources\igra.c .\wasm\sources\engine.c -o .\wasm\binary\test.js -s WASM=1
-s EXPORTED_FUNCTIONS="['_petlja','_init','_puts']" -s
EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']"

emcc -I ./wasm/sources ./wasm/sources/igra.c ./wasm/sources/engine.c -o
./wasm/binary/test.js -s WASM=1 -s
EXPORTED_FUNCTIONS="['_petlja','_init','_puts']" -s
EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']"
*/

// gore-'&'
// dole-'('