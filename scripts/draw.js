var colors = ["white","black","red","blue"];

function drawRectangle(x, y, w, h, ci) {
  let ctx = gameCanvas.getContext("2d");
  ctx.beginPath();
  ctx.fillStyle = colors[ci];
  ctx.rect(x, y, w, h);
  ctx.fill();
  console.log(x,y,w,h,ci);
  return ctx;
}

function drawCircle(x, y, r, ci) {
  let ctx = gameCanvas.getContext("2d");
  ctx.beginPath();
  ctx.fillStyle = colors[ci];
  ctx.arc(x, y, r, 0, 2 * Math.PI);
  ctx.fill();
}

function drawImage(x, y, w, h, assetIndex) {
  let ctx = gameCanvas.getContext("2d");
  ctx.drawImage(assets[assetIndex], x, y, w, h);
}

function clearCanvas() {
  const ctx = gameCanvas.getContext("2d");
  ctx.clearRect(0, 0, gameCanvas.width, gameCanvas.height);
}
