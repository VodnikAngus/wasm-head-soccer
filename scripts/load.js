var gameCanvas;
var gameDiv;
var gameUI;
var fullScreenToggle;
var assets = [];
var inicijalizacija;
var petlja;

function loaded() {
  inicijalizacija=Module.cwrap("init", null,["number"]);
  petlja=Module.cwrap("petlja", null, ["number","number"]);
  gameDiv = document.getElementById("gameDiv");
  gameUI = document.getElementById("gameUI");
  fullScreenToggle = document.getElementById("fullScreenToggle");

  gameCanvas = document.createElement("canvas");
  gameCanvas.width = 1920;
  gameCanvas.height = 1080;
  gameUI.style.width = `1920px`;
  gameUI.style.height = `1080px`;
  resized();
  gameDiv.appendChild(gameCanvas);
  assets = document.getElementById("assets").children;
  mainLoop();
}
