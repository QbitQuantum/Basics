// print the current state on the last line of the lcd
void LcdDisplay::printState(void){
	uint16_t time = UINT16_MAX; // init to max
	uint8_t state = tempControl.getDisplayState();
	if(state != stateOnDisplay){ //only print static text when state has changed
		stateOnDisplay = state;
		// Reprint state and clear rest of the line
		const char * part1 = STR_empty_string;
		const char * part2 = STR_empty_string;
		switch (state){
			case IDLE:
				part1 = PSTR("Idl");
				part2 = STR_ing_for;
				break;
			case WAITING_TO_COOL:
				part1 = STR_Wait_to_;
				part2 = STR_Cool;
				break;
			case WAITING_TO_HEAT:
				part1 = STR_Wait_to_;
				part2 = STR_Heat;
				break;
			case WAITING_FOR_PEAK_DETECT:
				part1 = PSTR("Waiting for peak");
				break;
			case COOLING:
				part1 = STR_Cool;
				part2 = STR_ing_for;
				break;
			case HEATING:
				part1 = STR_Heat;
				part2 = STR_ing_for;
				break;
			case COOLING_MIN_TIME:
				part1 = STR_Cool;
				part2 = STR__time_left;
				break;
			case HEATING_MIN_TIME:
				part1 = STR_Heat;
				part2 = STR__time_left;
				break;
			case DOOR_OPEN:
				part1 = PSTR("Door open");
				break;
			case STATE_OFF:
				part1 = PSTR("Temp. control OFF");
				break;
			default:
				part1 = PSTR("Unknown status!");
				break;
		}
		printAt_P(0, 3, part1);
		lcd.print_P(part2);		
		lcd.printSpacesToRestOfLine();
	}
	uint16_t sinceIdleTime = tempControl.timeSinceIdle();
	if(state==IDLE){
		time = 	min(tempControl.timeSinceCooling(), tempControl.timeSinceHeating());
	}
	else if(state==COOLING || state==HEATING){
		time = sinceIdleTime;
	}
	else if(state==COOLING_MIN_TIME){
		time = MIN_COOL_ON_TIME-sinceIdleTime;
	}
	
	else if(state==HEATING_MIN_TIME){
		time = MIN_HEAT_ON_TIME-sinceIdleTime;
	}
	else if(state == WAITING_TO_COOL || state == WAITING_TO_HEAT){
		time = tempControl.getWaitTime();
	}
	if(time != UINT16_MAX){
		char timeString[10];
#if DISPLAY_TIME_HMS  // 96 bytes more space required. 
		unsigned int minutes = time/60;		
		unsigned int hours = minutes/60;
		int stringLength = sprintf_P(timeString, PSTR("%dh%02dm%02d"), hours, minutes%60, time%60);
		char * printString = timeString;
		if(!hours){
			printString = &timeString[2];
			stringLength = stringLength-2;
		}
		printAt(20-stringLength, 3, printString);
#else
		int stringLength = sprintf_P(timeString, STR_FMT_U, (unsigned int)time);
		printAt(20-stringLength, 3, timeString);
#endif		
	}
}