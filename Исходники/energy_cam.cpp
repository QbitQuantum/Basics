void EC_Connect(void)
{
#ifdef USE_RS485
 #if _DEBUG_>0
	Serial.println(F("Connected to EnergyCam via RS485."));
 #endif
	RS485_ENABLE_TX;
	ec_state = EC_OK;
#else

#define EC_CONNECT_TIMEOUT	5000	// millis
	int reply;
	byte ec_ip[] = {192,168,100,48};
	int ec_port = 8088;
//  int8_t repl = 0;
#if _DEBUG_>0
	Serial.print(F("Connecting to EnergyCam ... "));
#endif
	// if you get a connection, report back via serial:
	timeout = millis();  // time within to get reply
	while (1) {
		if ( (millis()-timeout)>EC_CONNECT_TIMEOUT ) {  // if no answer received within the prescribed time
			//time_client.stop();
#if _DEBUG_>0
			Serial.print(F("timed out..."));
#endif
			break;
		}
		WDG_RST;
		reply = ec_client.connect(ec_ip, ec_port);
		if ( reply>0 ) break;
		else  delay(100);
	}
	if ( reply<=0 ) {
#if _DEBUG_>0
		// if you didn't get a connection to the server:
		Serial.print(F("failed: "));
		if ( reply==-1 ) Serial.println(F("timed out."));
		else if ( reply==-2 ) Serial.println(F("invalid server."));
		else if ( reply==-3 ) Serial.println(F("truncated."));
		else if ( reply==-4 ) Serial.println(F("invalid response"));
		else Serial.println(reply);
#endif
		ec_state = CONNECTION_TIMEOUT;  // to avoid error code 0
	} else {
    // connection was successful.
#if _DEBUG_>0
		Serial.println(F("done."));
#endif
		ec_state = EC_OK;
	}
	
#endif	// #ifdef USE_RS485
}