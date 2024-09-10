static void __cdecl StartThread(void *vContainer) {
	OleInitialize(NULL);
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_GROUPCHAT_CONTAINER), NULL, ContainerDlgProc, (LPARAM) vContainer);
	//MessageBox(NULL, "ChatContainer dies.", "MW", MB_OK);
	OleUninitialize();

}