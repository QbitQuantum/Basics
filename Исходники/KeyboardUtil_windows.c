void generateSymbol(const char* symbol, jboolean pressed)
{
    /* on Windows AltGr correspond to CTRL-ALT */
    if(!strcmp(symbol, "altgr"))
    {
        int scancode = MapVirtualKey(VK_CONTROL, 0);
        keybd_event(VK_CONTROL, scancode, pressed ? 0 : KEYEVENTF_KEYUP, 0); 
        scancode = MapVirtualKey(VK_MENU, 0);
        keybd_event(VK_MENU, scancode, pressed ? 0 : KEYEVENTF_KEYUP, 0); 
    }
    else if(!strcmp(symbol, "shift"))
    {
        int scancode = MapVirtualKey(VK_SHIFT, 0);
        keybd_event(VK_SHIFT, scancode, pressed ? 0 : KEYEVENTF_KEYUP, 0); 
    }
    else if(!strcmp(symbol, "ctrl"))
    {
        int scancode = MapVirtualKey(VK_CONTROL, 0);
        keybd_event(VK_CONTROL, scancode, pressed ? 0 : KEYEVENTF_KEYUP, 0); 
    }
    else if(!strcmp(symbol, "alt"))
    {
        int scancode = MapVirtualKey(VK_MENU, 0);
        keybd_event(VK_MENU, scancode, pressed ? 0 : KEYEVENTF_KEYUP, 0); 
    }
    else if(!strcmp(symbol, "hankaku"))
    {
        /* XXX constant name for HANKAKU ? */
        /* 
        int scancode = MapVirtualKey(VK_HANKAKU, 0);
        keybd_event(VK_HANKAKU, scancode, pressed ? 0 : KEYEVENTF_KEYUP, 0); 
        */
    }
}