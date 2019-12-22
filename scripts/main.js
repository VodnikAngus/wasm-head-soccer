var i = 0;
var keydown = [];
var keyup = [];
var lastTime;
function mainLoop() {
  loop();
}

function loop(time) {
  if (!lastTime) lastTime = time;
  console.log(time - lastTime);
  lastTime = time;
  clearCanvas();
  img = drawImage(20 + i, 20 + i, 200, 200, 0);
  i++;
  keydown = [];
  keyup = [];
  if (i < 10) window.requestAnimationFrame(loop);
}

eventTarget.addEventListener("keydown", event => {
  keydown.push(event.keyCode);
});

eventTarget.addEventListener("keyup", event => {
  keyup.push(event.keyCode);
});
