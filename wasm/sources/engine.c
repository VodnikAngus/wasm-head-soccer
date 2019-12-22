#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void rect(int x, int y, int sir, int vis, int ci) {
    EM_ASM_INT({
        //console.log($0, $1, $2, $3, $4);
        let ctx = gameCanvas.getContext("2d");
        ctx.beginPath();
        ctx.fillStyle = colors[$4];
        ctx.rect($0, $1, $2, $3);
        ctx.fill();
    },x, y, sir, vis, ci);
}

void circ(int x, int y, int r, int ci) {
    EM_ASM_INT({
        let ctx = gameCanvas.getContext("2d");
        ctx.beginPath();
        ctx.fillStyle = colors[$3];
        ctx.arc($0, $1, $2, 0, 2 * Math.PI);
        ctx.fill();
    },x, y, r, ci);
}

void slika(int x, int y, int sir, int vis, int ind) {
    EM_ASM_INT({
        let ctx = gameCanvas.getContext("2d");
        ctx.drawImage(assets[$4], $0, $1, $2, $3);
    },x, y, sir, vis, ind);
}

void cls() {
    EM_ASM({
        const ctx = gameCanvas.getContext("2d");
        ctx.clearRect(0, 0, gameCanvas.width, gameCanvas.height);
    });
}