function scaleFactor(w, h) {
  return w / 16 < h / 9 ? w / SIRINA : h / VISINA;
}

function resized() {
  scale = `scale(${scaleFactor(
    gameDiv.offsetWidth,
    gameDiv.offsetHeight
  )}) translate(-50%, -50%)`;

  gameCanvas.style.transform = scale;
  gameUI.style.transform = scale;
}
