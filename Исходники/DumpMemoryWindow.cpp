void DumpMemoryWindow::changeMode(HWND hwnd, Mode newMode)
{
	char buffer[128];
	selectedMode = newMode;
	
	SendMessage(GetDlgItem(hwnd,IDC_DUMP_USERMEMORY),BM_SETCHECK,selectedMode == MODE_RAM ? BST_CHECKED : BST_UNCHECKED,0);
	SendMessage(GetDlgItem(hwnd,IDC_DUMP_VRAM),BM_SETCHECK,selectedMode == MODE_VRAM ? BST_CHECKED : BST_UNCHECKED,0);
	SendMessage(GetDlgItem(hwnd,IDC_DUMP_SCRATCHPAD),BM_SETCHECK,selectedMode == MODE_SCRATCHPAD ? BST_CHECKED : BST_UNCHECKED,0);
	SendMessage(GetDlgItem(hwnd,IDC_DUMP_CUSTOMRANGE),BM_SETCHECK,selectedMode == MODE_CUSTOM ? BST_CHECKED : BST_UNCHECKED,0);

	if (selectedMode == MODE_CUSTOM)
	{
		EnableWindow(GetDlgItem(hwnd,IDC_DUMP_STARTADDRESS),TRUE);
		EnableWindow(GetDlgItem(hwnd,IDC_DUMP_SIZE),TRUE);

		if (filenameChosen == false)
			SetWindowTextA(GetDlgItem(hwnd,IDC_DUMP_FILENAME),"Custom.dump");
	} else {
		u32 start, size;
		const char* defaultFileName;

		switch (selectedMode)
		{
		case MODE_RAM:
			start = PSP_GetUserMemoryBase();
			size = PSP_GetUserMemoryEnd()-start;
			defaultFileName = "RAM.dump";
			break;
		case MODE_VRAM:
			start = PSP_GetVidMemBase();
			size = PSP_GetVidMemEnd()-start;
			defaultFileName = "VRAM.dump";
			break;
		case MODE_SCRATCHPAD:
			start = PSP_GetScratchpadMemoryBase();
			size = PSP_GetScratchpadMemoryEnd()-start;
			defaultFileName = "Scratchpad.dump";
			break;
		}
		
		sprintf(buffer,"0x%08X",start);
		SetWindowTextA(GetDlgItem(hwnd,IDC_DUMP_STARTADDRESS),buffer);
		EnableWindow(GetDlgItem(hwnd,IDC_DUMP_STARTADDRESS),FALSE);

		sprintf(buffer,"0x%08X",size);
		SetWindowTextA(GetDlgItem(hwnd,IDC_DUMP_SIZE),buffer);
		EnableWindow(GetDlgItem(hwnd,IDC_DUMP_SIZE),FALSE);
		
		if (filenameChosen == false)
			SetWindowTextA(GetDlgItem(hwnd,IDC_DUMP_FILENAME),defaultFileName);
	}
}