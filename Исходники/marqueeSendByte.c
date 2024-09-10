static void marqueeUpdate(SchedulerData data, TICK_COUNT lastTime, TICK_COUNT overflow){
	MARQUEE* m = (MARQUEE*)data;

	char* readPos = m->txt + m->readPos;
	char  first=*readPos;
	boolean blink = m->blink;

	TICK_COUNT delay = (first=='\0') ? m->delayEnd : m->delayChar;
	TICK_COUNT delayDiv4 = delay >> 2;

	if(blink==FALSE){
		// we are not currently bliking. Check if we should start.
		if(first!='\0'){
			char* pos = readPos;
			char prev = readPos[-1];
			blink = TRUE;
			for(size_t led = 0; led < m->num_leds; led++){
				char ch = *pos++;
				// If we've hit end of line or a different char then no blink
				if(ch=='\0' || ch!=prev){
					blink=FALSE;
					break;
				}
				prev = ch;
			}
		}
	}else{
		// We are already blinking, so turn it off
		blink=FALSE;
	}

	// Set it for next time
	if(blink != m->blink){
		m->blink = blink;
		delay = (blink) ? delayDiv4 : delay - delayDiv4;
	}

	// Write chars to leds
	for(size_t l = 0; l < m->num_leds; l++){
		SEGLED* led = (SEGLED*)pgm_read_word(&m->leds[l]);
		char ch = (blink) ? '\0' : *readPos;
		if(ch!='\0'){
			readPos++;
		}else{
			ch = ' ';
		}
		segled_put_char(led,ch);
	}

	if(first=='\0'){
		// line is finished
		m->readPos = 0;
		if(m->delayEnd==0 || m->txt[0]=='\0'){
			m->active=FALSE;
		}else{
			m->blink = FALSE;
		}
	}else{
		// middle of line
		if(!blink){
			// Show character next time
			m->readPos += 1;
		}
	}

	if(m->active){
		scheduleJob(&marqueeUpdate,data,lastTime,delay);
	}
}