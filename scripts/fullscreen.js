function fullscreen() {
  if (
    document.fullscreenElement ||
    document.webkitFullscreenElement ||
    document.mozFullScreenElement ||
    document.msFullscreenElement
  ) {
    if (document.exitFullscreen) {
      document.exitFullscreen();
    } else if (document.mozCancelFullScreen) {
      document.mozCancelFullScreen();
    } else if (document.webkitExitFullscreen) {
      document.webkitExitFullscreen();
    } else if (document.msExitFullscreen) {
      document.msExitFullscreen();
    }
  } else {
    if (gameDiv.requestFullscreen) {
      gameDiv.requestFullscreen();
    } else if (gameDiv.mozRequestFullScreen) {
      gameDiv.mozRequestFullScreen();
    } else if (gameDiv.webkitRequestFullscreen) {
      gameDiv.webkitRequestFullscreen(Element.ALLOW_KEYBOARD_INPUT);
    } else if (gameDiv.msRequestFullscreen) {
      gameDiv.msRequestFullscreen();
    }
  }
}
