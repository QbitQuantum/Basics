void ESP8266::callSerialResponseMethod(uint8_t serialResponseStatus){
	uint8_t lastState = state;

	state = STATE_IDLE;


	switch (lastState) {

	case STATE_joinAP: ProcessResponse_joinAP(serialResponseStatus);
		break;
	case STATE_createTCP: ProcessResponse_createTCP(serialResponseStatus);
		break;
	}

	strcpy(buffer, "");
	bufferCursor = 0; 	

	Serial.print("state ");
	Serial.println(state);

	if(state == STATE_IDLE){
		waitMessage();
	}
}