BOOL NotifyIMEProc(
    HIMC hImc,
    LONG lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    ImmNotifyIME(hImc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    return TRUE;
}