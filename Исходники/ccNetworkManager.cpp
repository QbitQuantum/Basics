bool ccNetworkManager::GetLocalIP(std::string& strIP)
{
    std::string strHostName;

    if (GetHostName(strHostName) == false)
        return false;

    struct hostent *host = ::gethostbyname((char*)strHostName.c_str());

    if (host == NULL)
        return false;

    //  Obtain the computer's IP
#if defined(WIN32)
    ccString::format(strIP, 
        "%d.%d.%d.%d",
        ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1,
        ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2,
        ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3,
        ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4);
#else
    strIP = inet_ntoa(*(struct in_addr *)*host->h_addr_list);
#endif

    return true;
}