/* DllMain is invoked by every process in the entire system that is hooked
 * by our window hooks, notably the tty processes' context, and by the user
 * who wants tty messages (the app).  Keep it light and simple.
 */
BOOL __declspec(dllexport) APIENTRY DllMain(HINSTANCE hModule, ULONG ulReason, 
                                            LPVOID pctx)
{
    if (ulReason == DLL_PROCESS_ATTACH) 
    {
        //hmodThis = hModule;
        if (!hookwndmsg) {
            origwndprop = MAKEINTATOM(GlobalAddAtom("Win9xConHookOrigProc"));
            hookwndprop = MAKEINTATOM(GlobalAddAtom("Win9xConHookThunkWnd"));
            hookwndmsg = RegisterWindowMessage("Win9xConHookMsg");
        }
#ifdef DBG
//        DbgPrintf("H ProcessAttach:%8.8x\r\n", 
//                  GetCurrentProcessId());
#endif
    }
    else if ( ulReason == DLL_PROCESS_DETACH ) 
    {
#ifdef DBG
//        DbgPrintf("H ProcessDetach:%8.8x\r\n", GetCurrentProcessId());                
#endif
        if (monitor_hwnd)
            SendMessage(monitor_hwnd, WM_DESTROY, 0, 0);
        if (is_subclassed) 
            SendMessage(hwtty, hookwndmsg, 0, (LPARAM)hwtty);
        if (hmodHook)
        {
            if (hhkGetMessage) {
                UnhookWindowsHookEx(hhkGetMessage);
                hhkGetMessage = NULL;
            }
            //if (hhkCallWndProc) {
            //    UnhookWindowsHookEx(hhkCallWndProc);
            //    hhkCallWndProc = NULL;
            //}
            FreeLibrary(hmodHook);
            hmodHook = NULL;
        }
        if (is_service)
            RegisterWindows9xService(FALSE);
        if (hookwndmsg) {
            GlobalDeleteAtom((ATOM)origwndprop);
            GlobalDeleteAtom((ATOM)hookwndprop);
            hookwndmsg = 0;
        }
    }
    return TRUE;
}