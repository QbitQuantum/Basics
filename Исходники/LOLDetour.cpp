DWORD WINAPI ccvva(){
	DWORD dwThreadID;
	hGame_LOL=FindWindowA("RiotWindowClass","League of Legends (TM) Client");
	if(!hGame_LOL) return NULL;
	dwThreadID=GetWindowThreadProcessId(hGame_LOL,NULL);
	g_hLOLGetMsg=SetWindowsHookEx(WH_GETMESSAGE,GetMsgProc,(HINSTANCE)hInstance,dwThreadID);
	if(!g_hLOLGetMsg) return NULL;
	PostMessageA(hGame_LOL,0x803,0,(LPARAM)g_hLOLGetMsg);
	return (DWORD)g_hLOLGetMsg;
}