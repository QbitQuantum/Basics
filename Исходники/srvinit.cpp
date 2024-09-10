[[nodiscard]]
HRESULT ConsoleServerInitialization(_In_ HANDLE Server, const ConsoleArguments* const args)
{
    Globals& Globals = ServiceLocator::LocateGlobals();

    try
    {
        Globals.pDeviceComm = new DeviceComm(Server);

        Globals.launchArgs = *args;

        Globals.uiOEMCP = GetOEMCP();
        Globals.uiWindowsCP = GetACP();

        Globals.pFontDefaultList = new RenderFontDefaults();

        FontInfo::s_SetFontDefaultList(Globals.pFontDefaultList);
    }
    CATCH_RETURN();

    // Removed allocation of scroll buffer here.
    return S_OK;
}