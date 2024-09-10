void sendValues() { //Send values to www.onms.net server
    if (client.connect(server, 80)) {
        Serial.println("Connected to www.onms.net server...");
        client.print("GET ");
        client.print("/?update_id=");
        client.print(update_id);
        client.print("&key=humidity&value=");
        client.print(humidity);
        client.println(" HTTP/1.1");
        client.println("Host: www.onms.net");
        client.println();
        Serial.println("Disconnecting from www.onms.net server...");
        client.stop();
    } else {
        Serial.println("Connection to www.onms.net failed...");
    }
}