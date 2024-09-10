//builds the url for the api request, connects to the server, and sends the request
boolean serverRequest() {
	//Serial.print(server);
	//Serial.println(page);
	client.stop();

	Serial.println("connecting...");
	if (client.connect(server, 80)) {
		Serial.println("connected");
		client.print("GET /makermanager/index.php?r=api/toolValidate&badge=");
		client.print(rfid_long);
		client.print("&tool=1");
		client.println(" HTTP/1.1");
		client.print("Host: ");
		client.println(server);
		client.println("User-Agent: arduino-ethernet");
		client.println("Connection: close");
		client.println("");
		
		//Serial.println(cmd);
		//client.println(cmd);
		return true;
	}
	else {
		Serial.println("connection failed");
		return false;
	}
}