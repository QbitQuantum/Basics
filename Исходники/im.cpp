void CYahooProto::ext_got_im(const char *me, const char *who, int protocol, const char *msg, 
								long tm, int stat, int utf8, int buddy_icon, 
								const char *seqn, int sendn)
{
	char 		*umsg;
	const char	*c = msg;
	int 		oidx = 0;
	CCSDATA 		ccs;
	PROTORECVEVENT 	pre;
	HANDLE 			hContact;


	LOG(("YAHOO_GOT_IM id:%s %s: %s (len: %d) tm:%lu stat:%i utf8:%i buddy_icon: %i", me, who, msg, lstrlenA(msg), tm, stat, utf8, buddy_icon));

	if(stat == 2) {
		char z[1024];

		snprintf(z, sizeof z, "Error sending message to %s", who);
		LOG((z));
		ShowError(Translate("Yahoo Error"), z);
		return;
	}

	if(!msg) {
		LOG(("Empty Incoming Message, exiting."));
		return;
	}

	if (GetByte( "IgnoreUnknown", 0 )) {

		/*
		* Check our buddy list to see if we have it there. And if it's not on the list then we don't accept any IMs.
		*/
		if (getbuddyH(who) == NULL) {
			LOG(("Ignoring unknown user messages. User '%s'. Dropping Message.", who));
			return;
		}
	}

	if ( BuddyIgnored( who )) {
		LOG(("User '%s' on our Ignore List. Dropping Message.", who));
		return;
	}

	// make a bigger buffer for \n -> \r\n conversion (x2)
	umsg = (char *) alloca(lstrlenA(msg) * 2 + 1); 

	while ( *c != '\0') {
		// Strip the font tag
		if (!_strnicmp(c,"<font ",6) || !_strnicmp(c,"</font>",6) ||
			// strip the fade tag
			!_strnicmp(c, "<FADE ",6) || !_strnicmp(c,"</FADE>",7) ||
			// strip the alternate colors tag
			!_strnicmp(c, "<ALT ",5) || !_strnicmp(c, "</ALT>",6)){ 
				while ((*c++ != '>') && (*c != '\0')); 
		} else
			// strip ANSI color combination
			if ((*c == 0x1b) && (*(c+1) == '[')){ 
				while ((*c++ != 'm') && (*c != '\0')); 
			} else

				if (*c != '\0'){
					umsg[oidx++] = *c;

					/* Adding \r to \r\n conversion */
					if (*c == '\r' && *(c + 1) != '\n') 
						umsg[oidx++] = '\n';

					c++;
				}
	}

	umsg[oidx++]= '\0';

	/* Need to strip off formatting stuff first. Then do all decoding/converting */
	LOG(("%s: %s", who, umsg));

	//if(!strcmp(umsg, "<ding>")) 
	//	:P("\a");

	ccs.szProtoService = PSR_MESSAGE;
	ccs.hContact = hContact = add_buddy(who, who, protocol, PALF_TEMPORARY);
	//SetWord(hContact, "yprotoid", protocol);
	Set_Protocol(hContact, protocol);

	ccs.wParam = 0;
	ccs.lParam = (LPARAM) &pre;
	pre.flags = (utf8) ? PREF_UTF : 0;

	if (tm) {
		HANDLE hEvent = (HANDLE)CallService(MS_DB_EVENT_FINDLAST, (WPARAM)hContact, 0);

		if (hEvent) { // contact has events
			DBEVENTINFO dbei;
			DWORD dummy;

			dbei.cbSize = sizeof (DBEVENTINFO);
			dbei.pBlob = (BYTE*)&dummy;
			dbei.cbBlob = 2;
			if (!CallService(MS_DB_EVENT_GET, (WPARAM)hEvent, (LPARAM)&dbei)) 
				// got that event, if newer than ts then reset to current time
				if ((DWORD)tm < dbei.timestamp) tm = (long)time(NULL);
		}

		pre.timestamp = (DWORD)time(NULL);
		
		if ((DWORD)tm < pre.timestamp)
			pre.timestamp = tm;
		
	} else
		pre.timestamp = (DWORD)time(NULL);

	pre.szMessage = umsg;
	pre.lParam = 0;

	// Turn off typing
	CallService(MS_PROTO_CONTACTISTYPING, (WPARAM) hContact, PROTOTYPE_CONTACTTYPING_OFF);
	CallService(MS_PROTO_CHAINRECV, 0, (LPARAM) & ccs);

	// ack the message we just got
	if (seqn)
		yahoo_send_im_ack(m_id, me, who, seqn, sendn);

	if (buddy_icon < 0) return;

	//?? Don't generate floods!!
	DBWriteContactSettingByte(hContact, m_szModuleName, "AvatarType", (BYTE)buddy_icon);
	if (buddy_icon != 2) {
		reset_avatar(hContact);
	} else if (DBGetContactSettingDword(hContact, m_szModuleName,"PictCK", 0) == 0) {
		/* request the buddy image */
		request_avatar(who); 
	} 
}