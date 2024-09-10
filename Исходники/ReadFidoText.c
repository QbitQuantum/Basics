int getfidoline(char *fidoline,char *buffer,int linelen, int chrs, BPTR fh,char *quotepre,struct NiKomBase *NiKomBase) {
	int anttkn,foo,tmpret,hasquoted=FALSE,donotwordwrap=FALSE;
	UBYTE tmp,*findquotesign,insquotebuf[81];
	strcpy(fidoline,buffer);
	anttkn=strlen(fidoline);
	buffer[0]=0;
	for(;;) {
		tmpret=FGetC(fh);
		if(tmpret==-1) return(FALSE);
		tmp=tmpret;
		if(tmp==0x8d) continue;
		if(tmp==0x0a) continue;
		if(tmp==0x00) continue;
		if(tmp==0x0d) {
			if(quotepre && !hasquoted) {                // Om detta är sant så har ett return kommit
				if(fidoline[0]!=1 && fidoline[0]!=0) {   // men raden var kortare än fem tecken så
					findquotesign=strchr(fidoline,'>');   // den har inte blivit citerad.
					if(findquotesign) {                   // Det kan också vara så att strängen som
						strcpy(insquotebuf,findquotesign); // kommer i buffervariabeln följs direkt av
						findquotesign[1]=0;                // return.
						strcat(fidoline,insquotebuf);
					} else {
						strcpy(insquotebuf,fidoline);
						strcpy(fidoline,quotepre);
						strcat(fidoline,insquotebuf);
					}
				}
			}
			break;
		}
		switch(chrs) {
			case CHRS_CP437 :
				if(tmp<128) fidoline[anttkn++]=tmp;
				else fidoline[anttkn++]=NiKomBase->IbmToAmiga[tmp];
				break;
			case CHRS_SIS7 :
				fidoline[anttkn++]=NiKomBase->SF7ToAmiga[tmp];
				break;
			case CHRS_MAC :
				if(tmp<128) fidoline[anttkn++]=tmp;
				else fidoline[anttkn++]=NiKomBase->MacToAmiga[tmp];
				break;
			case CHRS_LATIN1 :
				fidoline[anttkn++]=tmp;
				break;
			default :
				fidoline[anttkn++]=convnokludge(tmp);
		}
		fidoline[anttkn]=0;
		if(quotepre && !hasquoted && anttkn>=5) {    // När antal tecken överstiger fem är det dags
			hasquoted = TRUE;                         // att kolla om raden redan är ett citat eller
			if(fidoline[0]!=1) {                      // inte. Om det är det ska bara ett extra '>'
				findquotesign=strchr(fidoline,'>');    // in. Annars ska hela quotepre in.
				if(findquotesign) {
					if(linelen<79) linelen = 79;
					donotwordwrap = TRUE;
					strcpy(insquotebuf,findquotesign);
					findquotesign[1]=0;
					strcat(fidoline,insquotebuf);
				} else {
					strcpy(insquotebuf,fidoline);
					strcpy(fidoline,quotepre);
					strcat(fidoline,insquotebuf);
				}
				anttkn=strlen(fidoline);
			}
		}
		if(anttkn>=linelen) {
			for(foo=anttkn;fidoline[foo]!=' ' && foo>0;foo--);
			if(foo!=0) {
				if(quotepre && foo <= strlen(quotepre)); // Om hela citatet är ett ord, wrappa inte
				else if(!donotwordwrap) {
					fidoline[foo]=0;
					strncpy(buffer,&fidoline[foo+1],anttkn-foo-1);
					buffer[anttkn-foo-1]=0;
				}
			}
			break;
		}
	}
	return(TRUE);
}