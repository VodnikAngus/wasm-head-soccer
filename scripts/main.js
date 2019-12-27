var i = 0;
var keydown = [0];
var keyup = [0];
var lastTime;
var delta = 16;
var brigraca = 1;
var dodirY = -1;

function ms(n) {
  setInterval(() => console.log(delta), n);
}

function brigr(brigraca) {
  inicijalizacija(Math.random() * 4, brigraca, 16);
}

function mainLoop() {
  inicijalizacija(Math.random() * 4, brigraca, 16);
  loop();
}

function pmem(ptr) {
  console.log(Module.HEAP8[ptr]);
}

function pmemn(ptr, n) {
  for (var i = 0; i < n; i++) console.log(i, ": ", Module.HEAP8[ptr + i]);
}

function loop(time) {
  if (!lastTime) {
    lastTime = time;
  } else {
    delta = time - lastTime;
  }
  lastTime = time;

  //POCETAK C
  let ptr1 = Module._malloc(keydown.length);
  let ptr2 = Module._malloc(keyup.length);
  Module.HEAPU8.set(keydown, ptr1);
  Module.HEAPU8.set(keyup, ptr2);
  //pmemn(ptr1,keydown.length);
  petlja(ptr1, ptr2, dodirY, delta);
  Module._free(ptr1);
  Module._free(ptr2);
  //KRAJ C

  keydown = [0];
  keyup = [0];
  window.requestAnimationFrame(loop);
}

document.addEventListener("keydown", event => {
  keydown[0]++;
  keydown.push(event.keyCode);
});

document.addEventListener("keyup", event => {
  keyup[0]++;
  keyup.push(event.keyCode);
});

function nadodir(event) {
  if (event.touches.length == 1) {
    dodirY =
      (event.touches[0].pageY - gameUI.getBoundingClientRect().top) /
      scaleFactor(gameDiv.offsetWidth, gameDiv.offsetHeight);
  } else {
    dodirY = -1;
  }
}

function napomeraj(event) {
  if (event.touches.length == 1) {
    let dodirYTest =
      (event.touches[0].pageY - gameUI.getBoundingClientRect().top) /
      scaleFactor(gameDiv.offsetWidth, gameDiv.offsetHeight);
    if (dodirYTest <= 1080) {
      dodirY = dodirYTest;
    } else {
      dodirY = -1;
    }
  } else {
    dodirY = -1;
  }
}

function nadodirstop() {
  dodirY = -1;
}
