int main(void)
{
    char *currenttime;	    /* current time/date string	*/
    int	old_sec = 0;
//    int cur_hour = 0;	    /* current hour			*/
//    int cur_day = 0;	    /* current current day		*/
    int result = 0;
    int key = 0;
    Initialise();		// turn outputs on and off for 1 second
    InitDisplay();
    int keepgoing = 1;	    /* tells program to keep running until ESC pressed */
    while ( keepgoing == 1 )
    {

	currenttime = thetime();    /* get the current time	*/
	cur_sec = extract_num(currenttime, 18, 2); /* extract minute	*/
	cur_min = extract_num(currenttime, 15, 2); /* extract minute	*/
	cur_hour = extract_num(currenttime, 12,2); /* extract hour	*/
	//cur_day = extract_num(currenttime, 9, 2);  /* extract day	*/

	if(old_sec != cur_sec) {	/* only update screen once per second	*/
	    ReadAnalogInputs(3);
	    DisplayAnalogValues(3);
	    ReadDigitalInputs(3);
	    DisplayDigitalInputs(3);
	    locate( 25, 56);
	    color(CF_SETTINGS,CB_SETTINGS);
	    cprintf(currenttime);	/* update current time on screen	*/
	    //locate(20,1);cprintf("cur_min=%d",cur_min);
	    old_sec = cur_sec;
	    //  EVENTS (new function)
	    //OutputBit(0,valueInput[0]);
	    //OutputBit(1,valueInput[1]);
	    //OutputBit(2,valueInput[2]);
	    //OutputBit(3,valueInput[3]);

	    if (valueInput[1] == 1) {
		WritePort(1);
		DisplayPort(1,XOUTPUT,YOUTPUT);
	    }
	    if (valueAnalog[0] < 50) {
		WritePort(16);
		DisplayPort(16,XOUTPUT,YOUTPUT);
	    }
	Log("e:\\user\\c\\a_pcio\\logfile.log", currenttime);
	}

	if( kbhit() ) {
	    result = getkeypressed();	/* get a single keypress    */

	    switch (result)  {		/* perform task user pressed	*/
		case 27: {		/* ESC	*/
		    Message( "Do you really want to quit? (Y/n) " , 0);
		    key = getch();
		    if( ( key  == 'Y') || (key =='y') || (key == 13) )
			keepgoing = 0;	/* stop program execution	*/
		    Message("", 0);
		}
		break;

		case 59: {		/* F1	*/
		    Message("Initialising",0);
		    Message("Fast Pulse", 0);
		    Pulse(255, gPulse_fast);
		}
		break;

		case 60: {		/* F2	*/
		    Message("Storage CRO - enter settings", 0);
		    //getch();
		    gotoHiResMode();
		    DrawOscilliscopeScreen(50,0,550,255,50,51);
		    StorageOscilliscope("waiting for trigger", 1, 0, 220, 40, 0, 499);
		    InitDisplay();

		}
		break;

		case 61: {		/* F3	*/
		    gotoHiResMode();
		    DrawOscilliscopeScreen(100,100,355,355,20,32);
		    Oscilliscope();

		    InitDisplay();
		    Message("Oscilliscope", 0);
		     Pulse(255, gPulse_slow);
		}
		break;

		case 62: {		/* F4	*/
		    Message("BinaryCount", 0);
		    BinaryCount(gCounter);
		}
		break;

		case 63: {		/* F5	*/
		    Message("Chase Multiple", 0);
		    ChaseMultiple(gIterations, gSpeed);

		}
		break;
		case 64: {		/* F6	*/
		    Message("Chase Up", 0);
		    Chase(gSpeed, 0, 7);

		}
		break;
		case 65: {		/* F7	*/
		    Message("Chase Down", 0);
		    Chase(gSpeed, 7,0);

		}
		break;
		case 66: {		/* F8	*/
		    Message("Reading Analog inputs", 0);
		    ReadAnalogInputs(3);
		    DisplayAnalogValues(3);
		    ReadDigitalInputs(3);
		    DisplayDigitalInputs(3);
		}
		break;
		case 67: {		/* F9	*/
		    Message("Logging - PRESS A KEY TO STOP", 0);
		    FastAcquisition("e:\\user\\c\\a_pcio\\fastlog.log", currenttime);
		    Message("Done Logging to e:\user\c\a_pcio\fastlog.log", 0);
		}
		break;
		case 68: {		/* F10	*/
		    Message("Setup", 0);
		    //locate(12,65); scanf("%d", &gPORT);   // port change
		    locate(11, 62);
		    color(CF_SETTINGS,CB_SETTINGS);
	//	    color(YELLOW,BLACK);
		    cprintf("Enter new settings");
		    locate(13,75); scanf("%d", &gCounter);   // port change
		    if(gCounter<0||gCounter>999) gCounter=10; else fflush(stdin);
		    locate(14,75); scanf("%d", &gSpeed);   // port change
		    if(gSpeed<0||gSpeed>999) gSpeed=10; else fflush(stdin);
		    locate(15,75); scanf("%d", &gPulse_fast);   // port change
		    if(gPulse_fast<0||gPulse_fast>999) gPulse_fast=10; else fflush(stdin);
		    locate(16,75); scanf("%d", &gPulse_slow);   // port change
		    if(gPulse_slow<0||gPulse_slow>999) gPulse_slow=10; else fflush(stdin);
		    locate(17,75); scanf("%d", &gIterations);   // port change
		    if(gIterations<0||gIterations>999) gIterations=10; else fflush(stdin);

		    DisplaySettings(XSETTINGS,YSETTINGS);
		}
		break;
		case 48: { OutputBit(0,2); DisplayPort(1,XOUTPUT,YOUTPUT); } break;
		case 49: { OutputBit(1,2); DisplayPort(2,XOUTPUT,YOUTPUT); } break;
		case 50: { OutputBit(2,2); DisplayPort(4,XOUTPUT,YOUTPUT); } break;
		case 51: { OutputBit(3,2); DisplayPort(16,XOUTPUT,YOUTPUT); } break;
		case 52: { OutputBit(4,2); DisplayPort(32,XOUTPUT,YOUTPUT); } break;
		case 53: { OutputBit(5,2); DisplayPort(64,XOUTPUT,YOUTPUT); } break;
		case 54: { OutputBit(6,2); DisplayPort(128,XOUTPUT,YOUTPUT); } break;
		case 55: { OutputBit(7,2); DisplayPort(255,XOUTPUT,YOUTPUT); } break;

		case 43: { WritePort(++valueOutput[0]); } break;
		case 45: { WritePort(--valueOutput[0]); } break;

	    }

	}
    }
   return 0;

}