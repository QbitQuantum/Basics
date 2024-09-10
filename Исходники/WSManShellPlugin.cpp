/*------------------------------------------------------------------------
typedef VOID (WINAPI *WSMAN_PLUGIN_COMMAND)(
    __in WSMAN_PLUGIN_REQUEST *requestDetails,
    __in DWORD flags,
    __in PVOID shellContext,
    __in PCWSTR commandLine,
    __in_opt WSMAN_COMMAND_ARG_SET *arguments
    );

A plug-in that supports the Shell operations and needs to create commands
that are associated with the shell needs to implement this callback.
The plug-in must call WSManPluginReportContext to 
report the command context.  Once the command is completed or when it is closed
via the operationClosed boolean value or operationClosedHandle in the 
requestDetails the plug-in needs to call WSManPluginOperationComplete.
The command is active until this time.
  ------------------------------------------------------------------------*/
extern "C" VOID WINAPI WSManPluginCommand(__in WSMAN_PLUGIN_REQUEST * requestDetails,
                                          __in DWORD flags,
                                          __in PVOID shellContext,
                                          __in PCWSTR commandLine,
                                          __in_opt WSMAN_COMMAND_ARG_SET * arguments)
{
    // Verify input parameters
    if (NULL == shellContext)
    { 
        WSManPluginOperationComplete(requestDetails, 
                                     0, 
                                     ERROR_INVALID_PARAMETER, 
                                     L"Parameter cannot be NULL");
        return;
    }

    // Command
    CShellContext * shell = (CShellContext *) shellContext;
    shell->Command(requestDetails,
                   flags,
                   commandLine,
                   arguments);

    return;
}