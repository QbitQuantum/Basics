void
CALLBACK
DebugExtensionNotify(ULONG Notify, ULONG64 Argument)
{
    static BOOL    Connected;

    UNREFERENCED_PARAMETER(Argument);

    // The first time we actually connect to a target
    if ((Notify == DEBUG_NOTIFY_SESSION_ACCESSIBLE) && (!Connected))
    {
        IDebugClient *DebugClient = NULL;
        HRESULT Hr;
        PDEBUG_CONTROL DebugControl = NULL;

        if ((Hr = DebugCreate(__uuidof(IDebugClient),
                              (void **)&DebugClient)) == S_OK)
        {
            //
            // Get the architecture type.
            //
            if ((Hr = DebugClient->QueryInterface(__uuidof(IDebugControl),
                                                  (void **)&DebugControl)) == S_OK)
            {
                ULONG   TargetMachine;
                if ((Hr = DebugControl->GetActualProcessorType(
                              &TargetMachine)) == S_OK)
                {
                    Connected = TRUE;
                }

                //NotifyOnTargetAccessible(DebugControl);
                DebugControl->Release();
            }

            DebugClient->Release();
        }
    }

    // The target is gone
    if (Notify == DEBUG_NOTIFY_SESSION_INACTIVE)
        Connected = FALSE;

    return;
}