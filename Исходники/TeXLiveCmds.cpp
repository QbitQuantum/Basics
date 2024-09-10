bool HasInternetConnection()
{
    bool bInternetConnected;

    if (g_bIE5) {
        DWORD dwConnectionTypes = INTERNET_CONNECTION_LAN |
            INTERNET_CONNECTION_MODEM |
            INTERNET_CONNECTION_PROXY;
        if (!InternetGetConnectedState(&dwConnectionTypes, 0)) {
            InternetAutodial(INTERNET_AUTODIAL_FORCE_UNATTENDED, 0);
        }
        bInternetConnected = InternetGetConnectedState(&dwConnectionTypes, 0);
    }
    else {
        AfxGetApp()->DoWaitCursor(1);
        bInternetConnected = __IsInternetConnected();
        AfxGetApp()->DoWaitCursor(-1);
    }

    if (bInternetConnected) {
        // Guess which mode !
        g_sInternetMethod = (g_bIE5 ? "ie5" : "direct");
    }
    return bInternetConnected;
}