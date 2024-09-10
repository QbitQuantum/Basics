DWORD GetUserIdleTime()
{
    DWORD dwTickCount=GetTickCount();
    LASTINPUTINFO liiInfo;
    liiInfo.cbSize=sizeof(LASTINPUTINFO);
    GetLastInputInfo(&liiInfo);
    return (dwTickCount-liiInfo.dwTime)/1000;
}