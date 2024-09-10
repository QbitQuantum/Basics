void JabberDBAddAuthRequest(char *jid, char *nick)
{
	char *s, *p, *q;
	DBEVENTINFO dbei = {0};
	PBYTE pCurBlob;
	HANDLE hContact;

	// strip resource if present
	s = mir_strdup(jid);
	if ((p=strchr(s, '@')) != NULL) {
		if ((q=strchr(p, '/')) != NULL)
			*q = '\0';
	}
	_strlwr(s);

	if ((hContact=JabberHContactFromJID(jid)) == NULL) {
		hContact = (HANDLE) CallService(MS_DB_CONTACT_ADD, 0, 0);
		CallService(MS_PROTO_ADDTOCONTACT, (WPARAM) hContact, (LPARAM) jabberProtoName);
		DBWriteContactSettingString(hContact, jabberProtoName, "jid", s);
	}
	else {
		DBDeleteContactSetting(hContact, jabberProtoName, "Hidden");
	}
	DBWriteContactSettingString(hContact, jabberProtoName, "Nick", nick);

	//blob is: uin(DWORD), hContact(HANDLE), nick(ASCIIZ), first(ASCIIZ), last(ASCIIZ), email(ASCIIZ), reason(ASCIIZ)
	//blob is: 0(DWORD), hContact(HANDLE), nick(ASCIIZ), ""(ASCIIZ), ""(ASCIIZ), email(ASCIIZ), ""(ASCIIZ)
	dbei.cbSize = sizeof(DBEVENTINFO);
	dbei.szModule = jabberProtoName;
	dbei.timestamp = (DWORD) time(NULL);
	dbei.flags = 0;
	dbei.eventType = EVENTTYPE_AUTHREQUEST;
	dbei.cbBlob = sizeof(DWORD) + sizeof(HANDLE) + strlen(nick) + strlen(jid) + 5;
	pCurBlob = dbei.pBlob = (PBYTE) mir_alloc(dbei.cbBlob);
	*((PDWORD) pCurBlob) = 0; pCurBlob += sizeof(DWORD);
	*((PHANDLE) pCurBlob) = hContact; pCurBlob += sizeof(HANDLE);
	strcpy((char *) pCurBlob, nick); pCurBlob += strlen(nick)+1;
	*pCurBlob = '\0'; pCurBlob++;		//firstName
	*pCurBlob = '\0'; pCurBlob++;		//lastName
	strcpy((char *) pCurBlob, jid); pCurBlob += strlen(jid)+1;
	*pCurBlob = '\0';					//reason

	CallService(MS_DB_EVENT_ADD, (WPARAM) (HANDLE) NULL, (LPARAM) &dbei);
	JabberLog("Setup DBAUTHREQUEST with nick='%s' jid='%s'", nick, jid);
}