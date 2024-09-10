void updateDB_Door(){	
	Serial.println("connecting for DB update");
	if (client.connect(server, 80)) {
		client.print("GET http://153.42.193.63/ardi_db_update.php?door=");
		if(clientDoor)
			client.print(clientDoor,BIN);
		else
			client.print("'0'");
			
		client.print(" HTTP/1.0");
		client.println("Host: http://153.42.193.63");
		client.println();
		doorChanged = 1;
	} 
	else {  //connection failed
		Serial.println("connection failed");
		doorChanged = 0;
	}
	client.stop();
	client.flush();
}