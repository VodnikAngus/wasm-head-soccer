var i = 0;
var keydown = [];
var keyup = [];
var lastTime;
var delta=0.00001;

function mainLoop() {
  inicijalizacija();
  loop();
}

function loop(time) {
  if (!lastTime){ 
    lastTime = time;
  } else {
    delta=time - lastTime;
  } 
  lastTime = time;
  petlja();
  keydown = [];
  keyup = [];
  window.requestAnimationFrame(loop);
}

document.addEventListener("keydown", event => {
  keydown.push(event.keyCode);
});

document.addEventListener("keyup", event => {
  keyup.push(event.keyCode);
});
