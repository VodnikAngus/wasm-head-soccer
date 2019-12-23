var i = 0;
var keydown = [0];
var keyup = [0];
var lastTime;
var delta=0.00001;

function mainLoop() {
  inicijalizacija();
  loop();
}

function pmem(ptr){
  console.log(Module.HEAP8[ptr]);
}

function pmemn(ptr,n){
  for(var i=0;i<n;i++)
    console.log(i,": ",Module.HEAP8[ptr+i]);
}

function loop(time) {
  if (!lastTime){ 
    lastTime = time;
  } else {
    delta=time - lastTime;
  } 
  lastTime = time;

  //POCETAK C
  let ptr1 = Module._malloc(keydown.length);
  let ptr2 = Module._malloc(keyup.length);
  Module.HEAPU8.set(keydown,ptr1);
  Module.HEAPU8.set(keyup,ptr2);
  //pmemn(ptr1,keydown.length);
  petlja(ptr1,ptr2);
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
