int FAR PASCAL WEP(
int nParameter)
{
    fLoaded = FALSE;
    UnhookWindowsHook(WH_CBT, (HOOKPROC)CBTHookProc);
    UnhookWindowsHook(WH_KEYBOARD, (HOOKPROC)KBDHookProc);
    return(1);
}