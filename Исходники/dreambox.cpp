void Dreambox_Connect(void)
{
	int reply;
#if _DEBUG_>0
	Serial.print(F("Connecting to "));
	if (dm_device==DM800SE )
		Serial.print(F("DM800SE ... "));
	else
		Serial.print(F("DM800 ... "));
#endif
	// if you get a connection, report back via serial:
	long timeout = millis() + 3000;  // time within to get reply
	while (1) {
		if ( millis()>timeout ) {  // if no answer received within the prescribed time
			//time_client.stop();
#if _DEBUG_>0
			Serial.print(F("timed out..."));
#endif
			break;
		}
		WDG_RST;
		reply = dm_client.connect(dm_ip[dm_device], dm_port);
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
		dm_state[dm_device] = CONNECTION_TIMEOUT;
	} else {
    // connection was successful.
#if _DEBUG_>0
		Serial.println(F("done."));
#endif
		dm_state[dm_device] = DM_OK;
	}
}