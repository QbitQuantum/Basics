void handleNotFound() {
  webServer.send(404, "text/plain", "404 - Page Not Found");
}