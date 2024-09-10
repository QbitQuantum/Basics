uint8_t marqueeSendByte(MARQUEE* marquee, uint8_t byte){
	marquee_init(marquee);
	if(marquee->txt){

		if(byte=='\n'){
			// Start writing at the beginning of the line
			marquee->txt[marquee->writePos] = '\0';
			marquee->writePos = 0;
			CRITICAL_SECTION_START;
			if(!marquee->active){
				marquee->active = TRUE;
				marquee->blink = FALSE;
				marquee->readPos=0;
				scheduleJob(&marqueeUpdate,(SchedulerData)marquee,clockGetus(),marquee->delayChar);
			}
			CRITICAL_SECTION_END;
		}else if(byte!='\r'){
			// Now put the character to the buffer
			if(marquee->writePos < marquee->txtSize){
				char* put = marquee->txt + marquee->writePos;
				CRITICAL_SECTION_START;
				*put++ = byte;
				*put = '\0';
				marquee->writePos += 1;
				marquee->readPos = 0;
				CRITICAL_SECTION_END;
			}
		}
	}
	return byte;
}