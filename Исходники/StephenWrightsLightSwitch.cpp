void handleConsoleInput() {
    uint8_t retval;
	uint8_t index=0;
	uint8_t ch='0';
    switch (console.keyValue()) {
        case _NSC_:  
			console.printf("SOD:\r\n");
			retval=networkScan();
			console.printf("EOD:\r\n");
            console.printf("\nDBG: found=%d\r\n",retval);
            break;
        case _NJN_:  
			//console.printf("SOD:\r\n");
			retval=networkJoin(console.arguments());
			//console.printf("EOD:\r\n");
            console.printf("\nDBG: joined=%s\r\n",retval?"TRUE":"FALSE");
            break;
        case _NPW_:  
			//console.printf("SOD:\r\n");
			retval=networkSetPassword(console.arguments());
			//console.printf("EOD:\r\n");
            console.printf("\nDBG: pwd set=%s\r\n",retval?"TRUE":"FALSE");
            break;
        case _NST_:  
			retval=networkStatus();
            console.printf("NST: %s\r\n",retval?"CONNECTED":"NOT CONNECTED");
            break;
            
		case _TPT_:
			toTheEthers(1, console.arguments());
			break;
        case _TX2_:
            radio.printf("%s",console.arguments());
            index=0;
            // delay(1000);
            while (radio.available()) {
                inBuffer[index++]=ch=radio.read();
				if( index>= 99 || ((ch== '\n') || ch !='\r')) {
					inBuffer[index]='\0';
					console.puts(inBuffer);
					index=0; 
					delay(100);
				}
            } 
            inBuffer[index]='\0';
            console.puts(inBuffer);
			console.puts((char *) "\r\n");
            break;
        case _PKY_:
            strncpy(pachubeKey, console.arguments(), MAX_PATCHUBE_KEY_LENGHT-1);
            stripcrlf(pachubeKey);
            break;
        default:
            console.printf("DBG: forwarding (%s) to device\r\n",console.key());
            //device.puts("\r\n");
            break;
    }
    
    
}