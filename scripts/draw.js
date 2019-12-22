function drawRectangle(x, y, w, h) {
  let ctx = gameCanvas.getContext("2d");
  ctx.beginPath();
  ctx.fillStyle = "white";
  ctx.rect(x, y, w, h);
  ctx.fill();

  return ctx;
}

function drawCircle(x, y, r) {
  let ctx = gameCanvas.getContext("2d");
  ctx.beginPath();
  ctx.fillStyle = "white";
  ctx.arc(x, y, r, 0, 2 * Math.PI);
  ctx.fill();

  return ctx;
}

function drawImage(x, y, w, h, assetIndex) {
  let ctx = gameCanvas.getContext("2d");
  ctx.drawImage(assets[assetIndex], x, y, w, h);

  return ctx;
}

function clearCanvas() {
  const ctx = gameCanvas.getContext("2d");
  ctx.clearRect(0, 0, gameCanvas.width, gameCanvas.height);
}
