int GCEventHook(WPARAM wParam,LPARAM lParam) {
	GCHOOK *gch = (GCHOOK*) lParam;
	gchat_contacts *gc = GetChat(gch->pDest->ptszID);

	UNREFERENCED_PARAMETER(wParam);

	if(gch) {
		if (!_stricmp(gch->pDest->pszModule, SKYPE_PROTONAME)) {

			switch (gch->pDest->iType) {
			case GC_SESSION_TERMINATE: {
				MCONTACT hContact;

				if (gc->mJoinedCount == 1) {
					// switch back to normal session
                    // I don't know if this behaviour isn't a bit annoying, therefore, we
					// don't do this now, until a user requests this feature :)
                    
					// open up srmm dialog when quit while 1 person left
//					CallService(MS_MSG_SENDMESSAGE, (WPARAM)gc->mJoinedContacts[0].hContact, 0);

					RemChatContact(gc, gc->mJoinedContacts[0].who);
				}
				// Delete Chatroom from Contact list, as we don't need it anymore...?
				if (hContact = find_chat(gc->szChatName))
					CallService(MS_DB_CONTACT_DELETE, hContact, 0); 
				RemChat(gc->szChatName);

				break;
			}
			case GC_USER_MESSAGE:
				if(gch && gch->ptszText && _tcslen(gch->ptszText) > 0) {
					DBVARIANT dbv, dbv2;
					CCSDATA ccs = {0};
					TCHAR *pEnd;

					// remove the ending linebreak
					for (pEnd = &gch->ptszText[_tcslen(gch->ptszText) - 1];
						 *pEnd==_T('\r') || *pEnd==_T('\n'); pEnd--) *pEnd=0;
                    // Send message to the chat-contact    
					if (ccs.hContact = find_chat(gch->pDest->ptszID)) {
#ifdef _UNICODE
						// If PREF_UTF is supported, just convert it to UTF8 and pass the buffer to PSS_MESSAGE
						if (mirandaVersion >= 0x070000) {
							ccs.lParam = (LPARAM)make_utf8_string(gch->ptszText);
							ccs.wParam = PREF_UTF;
							CallProtoService (SKYPE_PROTONAME, PSS_MESSAGE, 0, (LPARAM)&ccs);
							free ((void*)ccs.lParam);
						} else {
						// Otherwise create this strange dual miranda-format
							ccs.lParam = (LPARAM)calloc(3, _tcslen(gch->ptszText)+1);
							wcstombs ((char*)ccs.lParam, gch->ptszText, _tcslen(gch->ptszText)+1);
							_tcscpy ((TCHAR*)((char*)ccs.lParam+strlen((char*)ccs.lParam)+1), gch->ptszText);
							ccs.wParam = PREF_UNICODE;
							CallProtoService (SKYPE_PROTONAME, PSS_MESSAGE, 0, (LPARAM)&ccs);
							free ((void*)ccs.lParam);
						}
#else
						ccs.lParam = (LPARAM)gch->ptszText;
						ccs.wParam = PREF_TCHAR;
						CallProtoService (SKYPE_PROTONAME, PSS_MESSAGE, 0, (LPARAM)&ccs);
#endif
					}

					// Add our line to the chatlog	
					GCDEST gcd = { gch->pDest->pszModule, gch->pDest->ptszID, 0 };
					GCEVENT gce = { sizeof(gce), &gcd };
					if ( _tcsncmp(gch->ptszText, _T("/me "), 4)==0 && _tcslen(gch->ptszText)>4) {
						gce.ptszText = gch->ptszText+4;
						gcd.iType = GC_EVENT_ACTION;
					}
					else {
						gce.ptszText = gch->ptszText;
						gcd.iType = GC_EVENT_MESSAGE;
					}

					if (db_get_ts(NULL, SKYPE_PROTONAME, "Nick", &dbv))
						gce.ptszNick = TranslateT("Me");
					else
						gce.ptszNick = dbv.ptszVal;
					db_get_ts(NULL, SKYPE_PROTONAME, SKYPE_NAME, &dbv2);
					gce.ptszUID = dbv2.ptszVal;
					gce.time = (DWORD)time(NULL);
					gce.dwFlags = GCEF_ADDTOLOG;
					gce.bIsMe = TRUE;
					CallService(MS_GC_EVENT, 0, (LPARAM)&gce);
					if (dbv.pszVal) db_free(&dbv);
					if (dbv2.pszVal) db_free(&dbv2);
				}
				break;
			case GC_USER_CHANMGR:
				InviteUser(gch->pDest->ptszID);
				break;
			case GC_USER_PRIVMESS: {
				MCONTACT hContact = find_contactT(gch->ptszUID);
				if (hContact) CallService(MS_MSG_SENDMESSAGE, hContact, 0);
				break;

			}
			case GC_USER_LOGMENU:
				switch(gch->dwData) {
				case 10: InviteUser(gch->pDest->ptszID); break;
				case 20: KillChatSession(gch->pDest); break;
                case 30: 
					{
						TCHAR *ptr, buf[MAX_BUF];

						ptr = SkypeGetT ("CHAT", (TCHAR*)gch->pDest->ptszID, "TOPIC");
						_tcscpy(buf, ptr);
						free(ptr);
						if (DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_INPUTBOX), NULL, InputBoxDlgProc, (LPARAM)&buf))
							SetChatTopic(gch->pDest->ptszID, buf, TRUE);
						break;
					}
				}
				break;
			case GC_USER_NICKLISTMENU: {
				MCONTACT hContact = find_contactT(gch->ptszUID);

				switch(gch->dwData) {
				case 10:CallService(MS_USERINFO_SHOWDIALOG, hContact, 0); break;
				case 20:CallService(MS_HISTORY_SHOWCONTACTHISTORY, hContact, 0); break;
				case 30: KickUser(hContact, gch); break;
				case 110: KillChatSession(gch->pDest); break;
				}
				break;
			}			
			default:
				break;
			}
		}

	}
	return 0;
}