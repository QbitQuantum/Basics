/////////
//
//	primec(): 
//		fetch the current character from the input stream
//		set inchar to the character or zero on EOF
//
void primec(void) {
	switch (fetchtype) {
		case SCRIPT_RAM:		inchar = *(char *) fetchptr;		break;
		case SCRIPT_PROGMEM:	inchar = pgm_read_byte(fetchptr); 	break;
		case SCRIPT_EEPROM:		inchar = eeread((int) fetchptr);	break;

#if defined(SDFILE) || defined(UNIX_BUILD)
		case SCRIPT_FILE:		inchar = scriptread();				break;
#endif

		default:				unexpected(M_oops);
	}

#ifdef PARSER_TRACE
	if (trace) {
		spb('<'); 
		if (inchar >= 0x20) spb(inchar);
		else { spb('\\'); printInteger(inchar, 0, ' '); }
		spb('>');
	}
#endif

}