// This method makes an HTTP connection to the server
void httpRequest(String link) {
	//if there is a successful connection
	if (client.connect(server, 80)) {
		client.println("Get " + link + " HTTP/1.0 ");
		client.println();

	} else {
		// You couldn't make the connection
		Serial.println("Connection Failed");
		Serial.println("Disconnecting.");
	}
		client.stop(); }