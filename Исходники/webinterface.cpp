void handleScan(){
  String body = wifi_helper->GetAPList();
  server.send(200, "application/json", body);
}