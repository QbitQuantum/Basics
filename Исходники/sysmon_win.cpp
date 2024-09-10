// return true if running under remote desktop
// (in which case CUDA and Stream apps don't work)
//
bool is_remote_desktop() {
    LPTSTR pBuf = NULL;
    DWORD dwLength;
    USHORT usProtocol=0, usConnectionState=0;

    if (WTSQuerySessionInformation(
        WTS_CURRENT_SERVER_HANDLE,
        WTS_CURRENT_SESSION,
        WTSClientProtocolType,
        &pBuf,
        &dwLength
    )) {
        usProtocol = *(USHORT*)pBuf;
        WTSFreeMemory(pBuf);
    }

    if (WTSQuerySessionInformation(
        WTS_CURRENT_SERVER_HANDLE,
        WTS_CURRENT_SESSION,
        WTSConnectState,
        &pBuf,
        &dwLength
    )) {
        usConnectionState = *(USHORT*)pBuf;
        WTSFreeMemory(pBuf);
    }

    // RDP Session implies Remote Desktop
    if (usProtocol == 2) return true;

    // Fast User Switching keeps the protocol set to the console but changes
    // the connected state to disconnected.
    if ((usProtocol == 0) && (usConnectionState == 4)) return true;

    return false;
}