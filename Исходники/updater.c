static BOOL ConnectionAvailable(
    VOID
    )
{
    if (WindowsVersion > WINDOWS_XP)
    {
        INetworkListManager *pNetworkListManager;

        // Create an instance of the INetworkListManger COM object.
        if (SUCCEEDED(CoCreateInstance(&CLSID_NetworkListManager, NULL, CLSCTX_ALL, &IID_INetworkListManager, &pNetworkListManager)))
        {
            VARIANT_BOOL isConnected = VARIANT_FALSE;
            VARIANT_BOOL isConnectedInternet = VARIANT_FALSE;

            // Query the relevant properties.
            INetworkListManager_get_IsConnected(pNetworkListManager, &isConnected);
            INetworkListManager_get_IsConnectedToInternet(pNetworkListManager, &isConnectedInternet);

            // Cleanup the INetworkListManger COM object.
            INetworkListManager_Release(pNetworkListManager);
            pNetworkListManager = NULL;

            // Check if Windows is connected to a network and it's connected to the internet.
            if (isConnected == VARIANT_TRUE && isConnectedInternet == VARIANT_TRUE)
            {
                // We're online and connected to the internet.
                return TRUE;
            }

            // We're not connected to anything.
            return FALSE;
        }

        // If we reached here, we were unable to init the INetworkListManager, fall back to InternetGetConnectedState.
        goto NOT_SUPPORTED;
    }
    else
NOT_SUPPORTED:
    {
        DWORD dwType;

        if (InternetGetConnectedState(&dwType, 0))
        {
            return TRUE;
        }
        else
        {
            LogEvent(NULL, PhFormatString(L"Updater: (ConnectionAvailable) InternetGetConnectedState failed to detect an active Internet connection (%d)", GetLastError()));
        }

        //if (!InternetCheckConnection(NULL, FLAG_ICC_FORCE_CONNECTION, 0))
        //{
        // LogEvent(PhFormatString(L"Updater: (ConnectionAvailable) InternetCheckConnection failed connection to Sourceforge.net (%d)", GetLastError()));
        // return FALSE;
        //}
    }

    return FALSE;
}