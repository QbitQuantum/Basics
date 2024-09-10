void handleRoot() {
  if (server.hasArg("redon")) {
    digitalWrite(15, HIGH);
  } else if (server.hasArg("redoff")) {
    digitalWrite(15, LOW);
  } else if (server.hasArg("greenon")) {
    digitalWrite(12, HIGH);
  } else if (server.hasArg("greenoff")) {
    digitalWrite(12, LOW);
  } else if (server.hasArg("blueon")) {
    digitalWrite(13, HIGH);
  } else if (server.hasArg("blueoff")) {
    digitalWrite(13, LOW);
  } else if (server.hasArg("off")) {
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(15, LOW);
  }

  int sensorValue = analogRead(LDR);
  char lightSensorValue[30];
  dtostrf(sensorValue, 4, 3, lightSensorValue);

  int buttonValue = digitalRead(BUTTON);
  char buttonSensorValue[30];
  dtostrf(buttonValue, 4, 3, buttonSensorValue);

  char request[1024];
  strcpy(request, "<html><head>");
  strcat(request, "<title>ESP8266 WittyCloud ESP12 Board</title>");
  strcat(request, "<meta name=\"viewport\" content=\"width=device-width, "
                  "initial-scale=1.0\"/>");
  strcat(request, "</head><body><ul>");
  strcat(request, "<li>Light sensor: ");
  strcat(request, lightSensorValue);
  strcat(request, "</li>");
  strcat(request, "<li>Button: ");
  strcat(request, buttonSensorValue);
  strcat(request, "</li><hr />");
  strcat(request, "<li>All: <a href=\"?off=1\">Off</a></li>");
  strcat(request, "<li>Red: <a href=\"?redon=1\">On</a> <a "
                  "href=\"?redoff=1\">Off</a></li>");
  strcat(request, "<li>Green: <a href=\"?greenon=1\">On</a> <a "
                  "href=\"?greenoff=1\">Off</a></li>");
  strcat(request, "<li>Blue: <a href=\"?blueon=1\">On</a> <a "
                  "href=\"?blueoff=1\">Off</a></li>");
  strcat(request, "</body></html>");
  server.send(200, "text/html", request);
}