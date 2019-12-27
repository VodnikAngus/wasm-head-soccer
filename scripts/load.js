var gameCanvas;
var gameDiv;
var gameUI;
var fullScreenToggle;
var assets = [];
var inicijalizacija;
var petlja;

const SIRINA=1920;
const VISINA=1080;

function load() {
  inicijalizacija = Module.cwrap("init", null, ["number", "number", "number"]);
  petlja = Module.cwrap("petlja", null, ["number", "number", "number", "number"]);
  pozovif = Module.cwrap("pozovif", null, ["number"]);
  gameDiv = document.getElementById("gameDiv");
  gameUI = document.getElementById("gameUI");
  fullScreenToggle = document.getElementById("fullScreenToggle");

  gameCanvas = document.createElement("canvas");
  gameCanvas.width = SIRINA;
  gameCanvas.height = VISINA;
  gameUI.style.width = `${SIRINA}px`;
  gameUI.style.height = `${VISINA}px`;
  resized();
  gameDiv.appendChild(gameCanvas);
  assets = document.getElementById("assets").children;

  gameUI.addEventListener("touchstart", nadodir, false);
  gameUI.addEventListener("touchmove", napomeraj, false);
  gameUI.addEventListener("touchend", nadodirstop, false);

  mainLoop();
}
