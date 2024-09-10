static void serioHandler(int fd, int revents, int userValue)
{
	static Bool firstTime = TRUE;
	String line;
	char newStatBits[21];
	static char oldStatBits[21];

	
	
	/* Do non-blocking line read */
	if(serio_nb_line_readcr(serioStuff)){
		/* Got a line or EOF */
		if(serio_ateof(serioStuff)){
			debug(DEBUG_EXPECTED, "EOF detected on serial port, closing port");
			if(!xPL_removeIODevice(serio_fd(serioStuff))) /* Unregister ourself */
				debug(DEBUG_UNEXPECTED,"Could not unregister from poll list");
			serio_close(serioStuff); /* Close serial port */
			serioStuff = NULL;
			serialRetryTimer = SERIAL_RETRY_TIME;
			return; /* Bail */
		}
		lineReceived = TRUE;
		line = serio_line(serioStuff);
		if(line[0] == '['){ /* Parse the status bits */
			confreadStringCopy(newStatBits, line + 1, 21);
			if(firstTime){ /* Set new and old the same on first time */
				firstTime = FALSE;
				confreadStringCopy(oldStatBits, newStatBits, 21);
			}
			if(strcmp(newStatBits, oldStatBits)){
				confreadStringCopy(oldStatBits, newStatBits, 21);
				debug(DEBUG_EXPECTED,"New Status bits: %s", newStatBits);
			}
			
			/* If ready */	
			if(newStatBits[0] == '1')
				stateBits.ready = 1;
			else
				stateBits.ready = 0;
							
			/* If anything is armed */
			if((newStatBits[1] == '1') || (newStatBits[2] == '1') ||
			   (newStatBits[12] == '1') || (newStatBits[15] == '1'))
				stateBits.armed = 1;
			else
				stateBits.armed = 0;
				
			/* If any alarm including one sent from LRR */
			if((newStatBits[10] == '1') || (newStatBits[13] == '1') || alarmLRR)
				stateBits.alarm = 1;
			else
				stateBits.alarm = 0;
			
			/* If AC fail */	
			if(newStatBits[7] == '0')
				stateBits.acfail = 1;
			else
				stateBits.acfail = 0;
			
			/* If low battery */
			if(newStatBits[11] == '1')
					stateBits.lowbatt = 1;
			else
					stateBits.lowbatt = 0;
				
		}
		else if(line[0] == '!'){ /* Other events */
			String p = line + 5;
			if(!strncmp(line + 1, "EXP", 3)){ /* Expander event ? */
				debug(DEBUG_EXPECTED,"Expander event: %s", p);
				doEXPTrigger(p);
			}
			if(!strncmp(line + 1, "LRR", 3)){ /* Long Range radio event ? */
				debug(DEBUG_EXPECTED,"Long Range Radio event: %s", p);
				doLRRTrigger(p);
			}

		}

	} /* End serio_nb_line_read */
}