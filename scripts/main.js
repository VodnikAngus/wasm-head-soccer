var i = 0;
var keydown = [];
var keyup = [];
var lastTime;
var delta=0.00001;
function mainLoop() {
  loop();
}

function loop(time) {
  if (!lastTime){ 
    lastTime = time;
  } else {
    delta=time - lastTime;
  } 
  lastTime = time;
  clearCanvas();
  img = drawImage(20 + i, 20 + i, 200, 200, 0);
  i++;
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
