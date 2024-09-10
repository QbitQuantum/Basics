//----------------------------------------------------------------
//  CImpIRestrictedProcess::RP_HelperWSALookupServiceBeginW()
//
//----------------------------------------------------------------
STDMETHODIMP
CImpIRestrictedProcess::RP_HelperWSALookupServiceBeginW(
                          IN  RPC_WSAQUERYSETW *pRestrictions,
                          IN  DWORD  dwControlFlags,
                          OUT DWORD *pdwLookupHandle,
                          OUT int   *piRet,
                          OUT int   *piErrno )
    {
    *piRet = SOCKET_ERROR;
    *piErrno = WSAEOPNOTSUPP;

    if ((!pRestrictions)||(!pRestrictions->lpServiceClassId))
       {
       *piErrno = WSAEINVAL;
       return NOERROR;
       }

    if ( (0
          != memcmp(pRestrictions->lpServiceClassId,&HostnameGuid,sizeof(GUID)))
       &&
         (0
          != memcmp(pRestrictions->lpServiceClassId,&AddressGuid,sizeof(GUID))))
       {
       *piErrno = WSAEACCES;  // or WSAEOPNOTSUPP?
       return NOERROR;
       }

    DWORD  dwFlagsMask = ~( LUP_RETURN_NAME
                          | LUP_RETURN_TYPE
                          | LUP_RETURN_VERSION
                          | LUP_RETURN_COMMENT
                          | LUP_RETURN_ADDR
                          | LUP_RETURN_BLOB );

    if (dwFlagsMask & dwControlFlags)
       {
       *piErrno = WSAEACCES;  // or WSAEOPNOTSUPP?
       return NOERROR;
       }

    *piRet = WSALookupServiceBeginW( (WSAQUERYSETW *)pRestrictions,
                                     dwControlFlags,
                                     (HANDLE*)pdwLookupHandle );

    if (*piRet == SOCKET_ERROR)
       {
       *piErrno = WSAGetLastError();
       }
    else
       {
       *piErrno = NO_ERROR;
       }

    return NOERROR;
    }