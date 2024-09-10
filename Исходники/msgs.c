int LoadSendRecvMessageModule(void)
{
	if (LoadLibraryA("riched20.dll") == NULL) {
		if (IDYES !=
			MessageBoxA(0,
						Translate
						("Miranda could not load the built-in message module, riched20.dll is missing. If you are using Windows 95 or WINE please make sure you have riched20.dll installed. Press 'Yes' to continue loading Miranda."),
						Translate("Information"), MB_YESNO | MB_ICONINFORMATION))
			return 1;
		return 0;
	}
	hDLL = LoadLibraryA("user32");
	pSetLayeredWindowAttributes = (PSLWA) GetProcAddress(hDLL,"SetLayeredWindowAttributes");
	InitGlobals();
	RichUtil_Load();
	OleInitialize(NULL);
	InitREOleCallback();
	InitOptions();
	hEventDbEventAdded = HookEvent(ME_DB_EVENT_ADDED, MessageEventAdded);
	hEventDbSettingChange = HookEvent(ME_DB_CONTACT_SETTINGCHANGED, MessageSettingChanged);
	hEventContactDeleted = HookEvent(ME_DB_CONTACT_DELETED, ContactDeleted);
	HookEvent(ME_SYSTEM_MODULESLOADED, SplitmsgModulesLoaded);
	HookEvent(ME_SKIN_ICONSCHANGED, IconsChanged);
	HookEvent(ME_PROTO_CONTACTISTYPING, TypingMessage);
	HookEvent(ME_SYSTEM_PRESHUTDOWN, PreshutdownSendRecv);
	CreateServiceFunction(MS_MSG_SENDMESSAGE, SendMessageCommand);
#if defined(_UNICODE)
	CreateServiceFunction(MS_MSG_SENDMESSAGE "W", SendMessageCommand);
#endif
	CreateServiceFunction(MS_MSG_GETWINDOWAPI, GetWindowAPI);
	CreateServiceFunction(MS_MSG_GETWINDOWCLASS, GetWindowClass);
	CreateServiceFunction(MS_MSG_GETWINDOWDATA, GetWindowData);
	CreateServiceFunction("SRMsg/ReadMessage", ReadMessageCommand);
	CreateServiceFunction("SRMsg/TypingMessage", TypingMessageCommand);
	hHookWinEvt=CreateHookableEvent(ME_MSG_WINDOWEVENT);
	SkinAddNewSoundEx("RecvMsgActive", Translate("Messages"), Translate("Incoming (Focused Window)"));
	SkinAddNewSoundEx("RecvMsgInactive", Translate("Messages"), Translate("Incoming (Unfocused Window)"));
	SkinAddNewSoundEx("AlertMsg", Translate("Messages"), Translate("Incoming (New Session)"));
	SkinAddNewSoundEx("SendMsg", Translate("Messages"), Translate("Outgoing"));
	hCurSplitNS = LoadCursor(NULL, IDC_SIZENS);
	hCurSplitWE = LoadCursor(NULL, IDC_SIZEWE);
	hCurHyperlinkHand = LoadCursor(NULL, IDC_HAND);
	if (hCurHyperlinkHand == NULL)
		hCurHyperlinkHand = LoadCursor(g_hInst, MAKEINTRESOURCE(IDC_HYPERLINKHAND));
	hDragCursor = LoadCursor(g_hInst,  MAKEINTRESOURCE(IDC_DRAGCURSOR));
	return 0;
}