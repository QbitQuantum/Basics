HRESULT HvSetSendTimeOut(const HV_SOCKET_HANDLE& hSocket, int iMS)
{
    struct timeval uTime;
    uTime.tv_sec = iMS / 1000;
    uTime.tv_usec = (iMS % 1000) * 1000;
    int iRet = SetSockOpt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&uTime, sizeof(timeval));
    return (0 == iRet) ? S_OK : E_FAIL;
}