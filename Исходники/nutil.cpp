HRESULT
CInterface::Initialize (
    )
{
    SOCKET  sock ;
    DWORD   retval ;
    WSADATA wsadata ;
    ULONG   size ;

    //  can't initialize twice
    if (m_pNIC) {
        return HRESULT_FROM_WIN32 (ERROR_GEN_FAILURE) ;
    }

    //  initialize local variables
    sock = INVALID_SOCKET ;

    m_hHeap = GetProcessHeap () ;
    if (m_hHeap == NULL) {
        retval = GetLastError () ;
        return HRESULT_FROM_WIN32 (retval) ;
    }

    if (WSAStartup (MAKEWORD(2, 0), & wsadata)) {
        retval = WSAGetLastError () ;
        return HRESULT_FROM_WIN32 (retval) ;
    }

    sock = WSASocket (AF_INET,
                      SOCK_RAW,
                      IPPROTO_RAW,
                      NULL,
                      0,
                      NULL) ;
    if (sock == INVALID_SOCKET) {
        retval = WSAGetLastError () ;
        goto error ;
    }

    for (m_cNIC = NUM_NIC_FIRST_GUESS;; m_cNIC++) {

        size = m_cNIC * sizeof INTERFACE_INFO ;

        __try {

            m_pNIC = reinterpret_cast <INTERFACE_INFO *> (m_pNIC ? HeapReAlloc (m_hHeap, HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, m_pNIC, size) :
                                                                   HeapAlloc (m_hHeap, HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, size)) ;

        } __except (EXCEPTION_EXECUTE_HANDLER) {

            retval = ERROR_NOT_ENOUGH_MEMORY ;
            goto error ;
        }

        // make the call
        if (WSAIoctl (sock,
                      SIO_GET_INTERFACE_LIST,
                      NULL,
                      0,
                      m_pNIC,
                      size,
                      & size,
                      NULL,
                      NULL) == 0) {

            //  call succeeded
            m_cNIC = size / sizeof INTERFACE_INFO ;
            break ;
        }

        // have we reached MAX_SUPPORTED_IFC
        if (m_cNIC == MAX_SUPPORTED_IFC) {

            m_cNIC = 0 ;
            retval = ERROR_GEN_FAILURE ;
            goto error ;
        }
    }

    WSACleanup () ;
    return S_OK ;

error :

    if (m_pNIC) {
        ASSERT (m_hHeap) ;
        HeapFree (m_hHeap, NULL, m_pNIC) ;
        m_pNIC = NULL ;
    }

    if (sock != INVALID_SOCKET) {
        closesocket (sock) ;
    }

    WSACleanup () ;

    return HRESULT_FROM_WIN32 (retval) ;
}