void display_pushemail(void) 
{
	folder Room;
	int Done = 0;
	StrBuf *Buf;
	long vector[8] = {8, 0, 0, 1, 2, 3, 4, 5};
	WCTemplputParams SubTP;
	char mobnum[20];

	StackContext(NULL, &SubTP, &vector, CTX_LONGVECTOR, 0, NULL);
	vector[0] = 16;

	/* Find any existing settings*/
	Buf = NewStrBuf();
	memset(&Room, 0, sizeof(folder));
	if (goto_config_room(Buf, &Room) == 0) {
		int msgnum = 0;
		serv_puts("MSGS ALL|0|1");
		StrBuf_ServGetln(Buf);
		if (GetServerStatus(Buf, NULL) == 8) {
			serv_puts("subj|__ Push email settings __");
			serv_puts("000");
			while (!Done &&
			       StrBuf_ServGetln(Buf) >= 0) {
				if ( (StrLength(Buf)==3) && 
				     !strcmp(ChrPtr(Buf), "000")) {
					Done = 1;
					break;
				}
				msgnum = StrTol(Buf);
			}
		}
		if (msgnum > 0L) {
		serv_printf("MSG0 %d", msgnum);
		StrBuf_ServGetln(Buf);
		if (GetServerStatus(Buf, NULL) == 1) {
			int i =0;
			Done = 0;
			while (!Done &&
			       StrBuf_ServGetln(Buf) >= 0) {
				if (( (StrLength(Buf)==3) && 
				      !strcmp(ChrPtr(Buf), "000"))||
				    ((StrLength(Buf)==4) && 
				     !strcmp(ChrPtr(Buf), "text")))
				{
					Done = 1;
					break;
				}
			}
			if (!strcmp(ChrPtr(Buf), "text")) {
				Done = 0;
				while (!Done &&
				       StrBuf_ServGetln(Buf) >= 0) {
					if ( (StrLength(Buf)==3) && 
					     !strcmp(ChrPtr(Buf), "000")) {
						Done = 1;
						break;
					}
					if (strncasecmp(ChrPtr(Buf), "none", 4) == 0) {
						vector[1] = 0;
					} else if (strncasecmp(ChrPtr(Buf), "textmessage", 11) == 0) {
						vector[1] = 1;
						i++;
					} else if (strncasecmp(ChrPtr(Buf), "funambol", 8) == 0) {
						vector[1] = 2;
					} else if (strncasecmp(ChrPtr(Buf), "httpmessage", 12) == 0) {
						vector[1] = 3;
					} else if (i == 1) {
						strncpy(mobnum, ChrPtr(Buf), 20);
						i++;
					}
				}	
			}
		}
		}
		serv_printf("GOTO %s", ChrPtr(WC->CurRoom.name));
		StrBuf_ServGetln(Buf);
		GetServerStatus(Buf, NULL);
	}
	FlushFolder(&Room);
	output_headers(1, 1, 1, 0, 0, 0);
	DoTemplate(HKEY("prefs_pushemail"), NULL, &SubTP);
	wDumpContent(1);
	UnStackContext(&SubTP);
	FreeStrBuf(&Buf);
}