LRESULT CIdlePreventDlg::SendWakeEvent(WPARAM wparam, LPARAM lparam)
{
    // This ensures we only send wake events while the machine isn't locked. Seems Windows queues some events and sometimes they happen at once as soon as you unlock the computer.
	HDESK test = OpenInputDesktop(DF_ALLOWOTHERACCOUNTHOOK, TRUE,DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |DESKTOP_SWITCHDESKTOP |GENERIC_WRITE);
	if (test != NULL)
	{
        if(RDPFriendlyWakeEnabled) 
        {      
            keybd_event(VK_RSHIFT,0xB6, KEYEVENTF_KEYUP,  0);
        }
        else
        {
            INPUT mouseInput[1];
            mouseInput[0].mi.dx = 0;
            mouseInput[0].mi.dy = 0;
            mouseInput[0].mi.mouseData = 0;
            mouseInput[0].mi.dwFlags = MOUSEEVENTF_MOVE;
            mouseInput[0].mi.time = 0;
            mouseInput[0].mi.dwExtraInfo = NULL;
            SendInput(1, mouseInput, sizeof(mouseInput));
            SetThreadExecutionState(ES_DISPLAY_REQUIRED);
        }
	}
	CloseDesktop(test);
	return 0;
}