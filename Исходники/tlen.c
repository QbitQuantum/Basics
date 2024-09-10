int __declspec(dllexport) Load(PLUGINLINK *link)
{
	PROTOCOLDESCRIPTOR pd;
	HANDLE hContact;
	char text[_MAX_PATH];
	char *p, *q;
	char *szProto;
	CLISTMENUITEM mi, clmi;
	DBVARIANT dbv;
	GetModuleFileName(hInst, text, sizeof(text));
	p = strrchr(text, '\\');
	p++;
	q = strrchr(p, '.');
	*q = '\0';
	jabberProtoName = _strdup(p);
	_strupr(jabberProtoName);

	jabberModuleName = _strdup(jabberProtoName);
	_strlwr(jabberModuleName);
	jabberModuleName[0] = toupper(jabberModuleName[0]);

	JabberLog("Setting protocol/module name to '%s/%s'", jabberProtoName, jabberModuleName);

	pluginLink = link;
	DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &hMainThread, THREAD_SET_CONTEXT, FALSE, 0);
	jabberMainThreadId = GetCurrentThreadId();
	//hLibSSL = NULL;
//	hWndListGcLog = (HANDLE) CallService(MS_UTILS_ALLOCWINDOWLIST, 0, 0);

	HookEvent(ME_OPT_INITIALISE, TlenOptInit);
	HookEvent(ME_SYSTEM_MODULESLOADED, ModulesLoaded);
	HookEvent(ME_SYSTEM_PRESHUTDOWN, PreShutdown);

	// Register protocol module
	ZeroMemory(&pd, sizeof(PROTOCOLDESCRIPTOR));
	pd.cbSize = sizeof(PROTOCOLDESCRIPTOR);
	pd.szName = jabberProtoName;
	pd.type = PROTOTYPE_PROTOCOL;
	CallService(MS_PROTO_REGISTERMODULE, 0, (LPARAM) &pd);


	memset(&mi, 0, sizeof(CLISTMENUITEM));
	mi.cbSize = sizeof(CLISTMENUITEM);
	memset(&clmi, 0, sizeof(CLISTMENUITEM));
	clmi.cbSize = sizeof(CLISTMENUITEM);
	clmi.flags = CMIM_FLAGS | CMIF_GRAYED;

	mi.pszPopupName = jabberModuleName;
	mi.popupPosition = 500090000;

	// "Multi-User Conference"
	wsprintf(text, "%s/MainMenuMUC", jabberModuleName);
	CreateServiceFunction(text, TlenMUCMenuHandleMUC);
	mi.pszName = Translate("Multi-User Conference");
	mi.position = 2000050001;
	mi.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_TLEN));
	mi.pszService = text;
	hMenuMUC = (HANDLE) CallService(MS_CLIST_ADDMAINMENUITEM, 0, (LPARAM) &mi);
	CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM) hMenuMUC, (LPARAM) &clmi);

	wsprintf(text, "%s/MainMenuChats", jabberModuleName);
	CreateServiceFunction(text, TlenMUCMenuHandleChats);
	mi.pszName = Translate("Tlen Chats...");
	mi.position = 2000050002;
	mi.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_TLEN));
	mi.pszService = text;
	hMenuChats = (HANDLE) CallService(MS_CLIST_ADDMAINMENUITEM, 0, (LPARAM) &mi);
	CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM) hMenuChats, (LPARAM) &clmi);

	// "Invite to MUC"
	sprintf(text, "%s/ContactMenuMUC", jabberModuleName);
	CreateServiceFunction(text, TlenMUCContactMenuHandleMUC);
	mi.pszName = Translate("Multi-User Conference");
	mi.position = -2000020000;
	mi.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_MUC));
	mi.pszService = text;
	mi.pszContactOwner = jabberProtoName;
	hMenuContactMUC = (HANDLE) CallService(MS_CLIST_ADDCONTACTMENUITEM, 0, (LPARAM) &mi);

	// "Invite to voice chat"
	sprintf(text, "%s/ContactMenuVoice", jabberModuleName);
	CreateServiceFunction(text, TlenVoiceContactMenuHandleVoice);
	mi.pszName = Translate("Voice Chat");
	mi.position = -2000018000;
	mi.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_MICROPHONE));
	mi.pszService = text;
	mi.pszContactOwner = jabberProtoName;
	hMenuContactVoice = (HANDLE) CallService(MS_CLIST_ADDCONTACTMENUITEM, 0, (LPARAM) &mi);


	// "Request authorization"
	sprintf(text, "%s/RequestAuth", jabberModuleName);
	CreateServiceFunction(text, TlenContactMenuHandleRequestAuth);
	mi.pszName = Translate("Request authorization");
	mi.position = -2000001001;
	mi.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_REQUEST));
	mi.pszService = text;
	mi.pszContactOwner = jabberProtoName;
	hMenuContactRequestAuth = (HANDLE) CallService(MS_CLIST_ADDCONTACTMENUITEM, 0, (LPARAM) &mi);

	// "Grant authorization"
	sprintf(text, "%s/GrantAuth", jabberModuleName);
	CreateServiceFunction(text, TlenContactMenuHandleGrantAuth);
	mi.pszName = Translate("Grant authorization");
	mi.position = -2000001000;
	mi.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_GRANT));
	mi.pszService = text;
	mi.pszContactOwner = jabberProtoName;
	hMenuContactGrantAuth = (HANDLE) CallService(MS_CLIST_ADDCONTACTMENUITEM, 0, (LPARAM) &mi);


	HookEvent(ME_CLIST_PREBUILDCONTACTMENU, TlenPrebuildContactMenu);

	if (!DBGetContactSetting(NULL, jabberProtoName, "LoginServer", &dbv)) {
		DBFreeVariant(&dbv);
	} else {
		DBWriteContactSettingString(NULL, jabberProtoName, "LoginServer", "tlen.pl");
	}
	if (!DBGetContactSetting(NULL, jabberProtoName, "ManualHost", &dbv)) {
		DBFreeVariant(&dbv);
	} else {
		DBWriteContactSettingString(NULL, jabberProtoName, "ManualHost", "s1.tlen.pl");
	}

	// Set all contacts to offline
	hContact = (HANDLE) CallService(MS_DB_CONTACT_FINDFIRST, 0, 0);
	while (hContact != NULL) {
		szProto = (char *) CallService(MS_PROTO_GETCONTACTBASEPROTO, (WPARAM) hContact, 0);
		if(szProto!=NULL && !strcmp(szProto, jabberProtoName)) {
			if (DBGetContactSettingWord(hContact, jabberProtoName, "Status", ID_STATUS_OFFLINE) != ID_STATUS_OFFLINE) {
				DBWriteContactSettingWord(hContact, jabberProtoName, "Status", ID_STATUS_OFFLINE);
			}
		}
		hContact = (HANDLE) CallService(MS_DB_CONTACT_FINDNEXT, (WPARAM) hContact, 0);
	}

	streamId = NULL;
	jabberThreadInfo = NULL;
	jabberConnected = FALSE;
	jabberOnline = FALSE;
	jabberStatus = ID_STATUS_OFFLINE;
	jabberVcardPhotoFileName = NULL;
	jabberVcardPhotoType = NULL;
	memset((char *) &modeMsgs, 0, sizeof(JABBER_MODEMSGS));
	//jabberModeMsg = NULL;
	jabberCodePage = CP_ACP;

	InitializeCriticalSection(&mutex);
	InitializeCriticalSection(&modeMsgMutex);

	TlenIconInit();
	srand((unsigned) time(NULL));
	JabberSerialInit();
	JabberIqInit();
	JabberListInit();
	JabberSvcInit();

	return 0;
}