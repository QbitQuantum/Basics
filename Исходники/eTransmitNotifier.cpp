// Init this application. Register your
// commands, reactors...
void InitApplication()
{
    if (FAILED(DllRegisterServer()))
        acutPrintf("\nFailed to register.");//dbx safe
    // NOTE: DO NOT edit the following lines.
    //{{AFX_ARX_INIT
    AddCommand("ASDKETRANSMIT", "ADDNOTIFIER", "ADDNOTIFIER", ACRX_CMD_SESSION, AsdkeTransmitAddNotifier);
    AddCommand("ASDKETRANSMIT", "REMOVENOTIFIER", "REMOVENOTIFIER", ACRX_CMD_SESSION, AsdkeTransmitRemoveNotifier);
    //}}AFX_ARX_INIT

    // TODO: add your initialization functions

}