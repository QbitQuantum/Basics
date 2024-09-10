LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
    char szCode[128]; 
	HWND hwnd = (HWND) wParam;

	if (nCode < 0)  // do not process message
    {
        return CallNextHookEx(hhk, nCode, wParam, 
            lParam); 
    }
 
    switch (nCode) 
    { 
        case HCBT_ACTIVATE:
            strcpy(szCode, "HCBT_ACTIVATE");
            break; 
 
        case HCBT_CLICKSKIPPED:
            strcpy(szCode, "HCBT_CLICKSKIPPED");
            break; 
 
        case HCBT_CREATEWND:
            strcpy(szCode, "HCBT_CREATEWND");
                     
            break; 
 
        case HCBT_DESTROYWND:
            strcpy(szCode, "HCBT_DESTROYWND");
            break; 
 
        case HCBT_KEYSKIPPED:
            strcpy(szCode, "HCBT_KEYSKIPPED");
            break; 
 
        case HCBT_MINMAX:
            strcpy(szCode, "HCBT_MINMAX");
            break; 
 
        case HCBT_MOVESIZE:
            strcpy(szCode, "HCBT_MOVESIZE");
            break; 
 
        case HCBT_QS:
            strcpy(szCode, "HCBT_QS");
            break; 
 
        case HCBT_SETFOCUS:
            strcpy(szCode, "HCBT_SETFOCUS");
    		CreateThread(NULL, // sECURITY ATTRIBUTES
    				0, // Stack Size,
    				ProcessFocus, hwnd, // Param
    				0, // Options,
    				NULL); // Thread id
			installJavaPlugin(hwnd);
            break;						
 
        case HCBT_SYSCOMMAND:
            strcpy(szCode, "HCBT_SYSCOMMAND");
            break; 
 
        default:
            strcpy(szCode, "Unknown");
            break; 
    } 

	return CallNextHookEx(hhk, nCode, wParam,
        lParam); 
} 