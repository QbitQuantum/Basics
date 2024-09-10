bool disable(Disable::Request& request, Disable::Response& response) {
  controller.enabled = false;
  controller.reset();
  lastTime.fromSec(0.0);

  return fadeToDefaultColor();
}