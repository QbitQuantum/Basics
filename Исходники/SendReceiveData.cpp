int SendReceiveData::decodeCommand(char *out) {

	//==================
	UINT outCode;
	char buttonName[32];
	//==================

	outCode = irCode & 0x7F;

	switch(outCode) {
		
		case 12:	strcpy_s(buttonName,"POWER");	break;

		case 63:	strcpy_s(buttonName,"0");	break;
		case 1:		strcpy_s(buttonName,"1");	break;
		case 2:		strcpy_s(buttonName,"2");	break;
		case 3:		strcpy_s(buttonName,"3");	break;
		case 4:		strcpy_s(buttonName,"4");	break;
		case 5:		strcpy_s(buttonName,"5");	break;
		case 6:		strcpy_s(buttonName,"6");	break;
		case 7:		strcpy_s(buttonName,"7");	break;
		case 8:		strcpy_s(buttonName,"8");	break;
		case 9:		strcpy_s(buttonName,"9");	break;

		case 40:	strcpy_s(buttonName,"REC_TV");	break;
		case 38:	strcpy_s(buttonName,"GUIDE");	break;
		case 37:	strcpy_s(buttonName,"LIVE_TV");break;

		case 35:	strcpy_s(buttonName,"BACK");	break;
		case 15:	strcpy_s(buttonName,"MORE");	break;

		case 30:	strcpy_s(buttonName,"UP");		break;
		case 31:	strcpy_s(buttonName,"DOWN");	break;
		case 32:	strcpy_s(buttonName,"LEFT");	break;
		case 33:	strcpy_s(buttonName,"RIGHT");	break;
		case 34:	strcpy_s(buttonName,"OK");		break;

		case 17:	strcpy_s(buttonName,"VOL-");	break;
		case 16:	strcpy_s(buttonName,"VOL+");	break;
		case 19:	strcpy_s(buttonName,"CH/PG-");	break;
		case 18:	strcpy_s(buttonName,"CH/PG+");	break;

		case 23:	strcpy_s(buttonName,"RECORD");	break;
		case 13:	strcpy_s(buttonName,"MCE");	break;
		case 25:	strcpy_s(buttonName,"STOP");	break;
		case 11:	strcpy_s(buttonName,"MENU");	break;

		case 21:	strcpy_s(buttonName,"<<");		break;
		case 24:	strcpy_s(buttonName,"||");		break;
		case 20:	strcpy_s(buttonName,">>");		break;
		case 10:	strcpy_s(buttonName,"ESC");	break;

		case 27:	strcpy_s(buttonName,"|<<");	break;
		case 22:	strcpy_s(buttonName,"PLAY");	break;
		case 26:	strcpy_s(buttonName,">>|");	break;
		case 14:	strcpy_s(buttonName,"MUTE");	break;

		case 93:	strcpy_s(buttonName,"*");		break;
		case 74:	strcpy_s(buttonName,"CLEAR");	break;
		case 92:	strcpy_s(buttonName,"#");		break;

		case 98:	strcpy_s(buttonName,"MOUSE_BUTTON_LEFT");	break;
		case 79:	strcpy_s(buttonName,"MOUSE_BUTTON_RIGHT");break;

		case 94:	strcpy_s(buttonName,"MOUSE_UP");	break;
		case 95:	strcpy_s(buttonName,"MOUSE_DOWN");	break;
		case 96:	strcpy_s(buttonName,"MOUSE_LEFT");	break;
		case 97:	strcpy_s(buttonName,"MOUSE_RIGHT");break;

		case 100:	strcpy_s(buttonName,"HELP");		break;
		case 36:	strcpy_s(buttonName,"DVD_MENU");	break;
		case 99:	strcpy_s(buttonName,"FULLSCREEN");	break;
		case 106:	strcpy_s(buttonName,"ENTER");		break;

		default: {
			irCode	= 0;
			repeats = 0;
			return 0;
		}

	}

	lastValue	= irCode;
	irCode		= 0;

	_snprintf_s(out,PACKET_SIZE+1,PACKET_SIZE+1,"%016llx %02x %s %s\n",__int64(0),repeats,buttonName,"MaxterPlus");

	return 1;

}