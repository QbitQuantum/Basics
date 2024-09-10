/////////////////////////////////////////////////////////////////////////////
// Destroys the LNR window and unregisters from TS session change
//  notifications.
/////////////////////////////////////////////////////////////////////////////
static gboolean plugin_unload(PurplePlugin *plugin)
{
    if(lnr_hwnd != NULL)
    {
        WTSUnRegisterSessionNotification(lnr_hwnd);
        DestroyWindow(lnr_hwnd);
        lnr_hwnd = NULL;
    }
    UnregisterClass("pidgin_lockonaway", NULL);
    return TRUE;
}