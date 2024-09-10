// 初始化面向客户端的连接
BOOL KPlayerServer::Init()
{
    BOOL            bResult                 = false;
    int             nRetCode                = false;
    BOOL            bSocketServerInit       = false;
    IIniFile*	    piIniFile               = NULL;
    unsigned long   ulInternalIPAddressMask = 0;
    unsigned long   ulExternalIPAddress     = INADDR_NONE;
    unsigned long   ulInternalIPAddress     = INADDR_NONE;
    //int				nListenPort             = 0;
    int             nNatPort                = 0;
    int 			nMaxConnection          = 0;
    int             nRecvBufferSize         = 0;
    int             nSendBufferSize         = 0;
    int             nClientGM               = 0;
    int             nMaxClientPackPerFrame  = 0;
    char            szNatIP[16];
    char            szInternalIPMask[16];
    unsigned char   byInternalMacAddress[6];
    unsigned char   byExternalMacAddress[6];
    struct          in_addr  InAddr;
    
    assert(g_pSO3World);
    
    piIniFile = g_OpenIniFile(GS_SETTINGS_FILENAME);
	KGLOG_PROCESS_ERROR(piIniFile);

    memset(szNatIP, 0, sizeof(szNatIP));

    piIniFile->GetString("GS-Player", "NatIP", "", szNatIP, sizeof(szNatIP));
    piIniFile->GetInteger("GS-Player", "NatPort", 0, &nNatPort);
    piIniFile->GetString("GS-Player", "InternalIPAddressMask", "192.168.0.0", szInternalIPMask, 16);
	piIniFile->GetInteger("GS-Player", "MaxConnection", 1024, &nMaxConnection);
	piIniFile->GetInteger("GS-Player", "RecvBufferSize", 8000, &nRecvBufferSize);
	piIniFile->GetInteger("GS-Player", "SendBufferSize", 64000, &nSendBufferSize); 
    piIniFile->GetInteger("GS-Player", "PingCycle", 0, &m_nPingCycle);
    piIniFile->GetInteger("GS-Player", "ClientGM", 0, &nClientGM);
    piIniFile->GetInteger("GS-Player", "MaxClientPackPerFrame", 256, &nMaxClientPackPerFrame);

    if (m_szLocalIP[0] != '\0')
    {
         ulExternalIPAddress = (unsigned long)inet_addr(m_szLocalIP);
         if (ulExternalIPAddress == INADDR_NONE)
         {
             KGLogPrintf(KGLOG_ERR, "[KPlayerServerBase] Invalid ip address or format.\n");
             goto Exit0;
         }    
    }
    else
    {
        char* pszInternetAddr = NULL;

        ulInternalIPAddressMask = inet_addr(szInternalIPMask);
        KGLOG_PROCESS_ERROR(ulInternalIPAddressMask != INADDR_NONE);

        nRetCode = gGetMacAndIPAddress(
            byInternalMacAddress, &ulInternalIPAddress, 
            byExternalMacAddress, &ulExternalIPAddress, ulInternalIPAddressMask
        );
        KGLOG_PROCESS_ERROR(nRetCode > 0);

        InAddr.s_addr = ulExternalIPAddress;
        pszInternetAddr = inet_ntoa(InAddr);
        KGLOG_PROCESS_ERROR(pszInternetAddr);

        strcpy(m_szLocalIP, pszInternetAddr);
    }
    
    KGLOG_PROCESS_ERROR(nMaxConnection > 0);
    
    m_dwTimeNow = KG_GetTickCount();
    m_nClientGM = nClientGM;

    ResetPakStat();

	m_nMaxConnection = nMaxConnection;
    m_nMaxClientPackPerFrame = nMaxClientPackPerFrame;

	m_ConnectionDataList = new KConnectionData[nMaxConnection];
	KGLOG_PROCESS_ERROR(m_ConnectionDataList);

    m_ConnectionDataListFreeVector.reserve(nMaxConnection);

    for (int i = 0; i < nMaxConnection; i++)
    {
        m_ConnectionDataListFreeVector.push_back(nMaxConnection - i - 1);
    }

    m_nSocketEventCount = nMaxConnection + KG_MAX_ACCEPT_EACH_WAIT;

    m_pSocketEventArray = new KG_SOCKET_EVENT[m_nSocketEventCount];
    KGLOG_PROCESS_ERROR(m_pSocketEventArray);

    nRetCode = m_SocketServerAcceptor.Init(
        m_szLocalIP, m_nListenPort, KG_MAX_ACCEPT_EACH_WAIT, 
        nRecvBufferSize, nSendBufferSize, KSG_ENCODE_DECODE_NONE, NULL
    );

    KGLogPrintf(
        KGLOG_INFO, "Start service at %s:%d ... ... [%s]",
        m_szLocalIP, m_nListenPort, nRetCode ? "OK" : "Failed"
    );
    
    KGLOG_PROCESS_ERROR(nRetCode);
    bSocketServerInit = true;

	m_dwInternetAddr    = ulExternalIPAddress;
    if (szNatIP[0] != '\0')
    {
        m_nListenPort       = nNatPort;
        m_dwInternetAddr    = (unsigned long)inet_addr(szNatIP);

        KGLogPrintf(KGLOG_INFO, "NAT at %s:%d", szNatIP, nNatPort);
    }

    m_nNextCheckConnection = 0;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bSocketServerInit)
        {
            m_SocketServerAcceptor.UnInit(NULL);
            bSocketServerInit = false;
        }
        KG_DELETE_ARRAY(m_pSocketEventArray);
    	KG_DELETE_ARRAY(m_ConnectionDataList);
    }
    KG_COM_RELEASE(piIniFile);
	return bResult;
}