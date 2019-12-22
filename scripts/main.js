function mainLoop() {
  i = 0;
  setInterval(function() {
    clearCanvas();
    img = drawImage(20 + i, 20 + i, 200, 200, 0);
    i++;
  }, 15);
}
