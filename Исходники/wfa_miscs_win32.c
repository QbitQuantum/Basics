unsigned int uGetLocalIP()
{
    char szHostName[WFA_BUFF_256];
    struct hostent*	HostData;

    GetHostName(szHostName, WFA_BUFF_256);
    HostData = gethostbyname(szHostName);
    if (HostData == NULL)
        return 0;

    return *((unsigned int*)HostData->h_addr);
}