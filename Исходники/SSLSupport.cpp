SSL* SSLMakeSession(SYS_SOCKET SockFD,
                    int iTimeOut,
                    int iIsServerCtx)
{
    char szSessionId[256];
    SYS_INET_ADDR addrInfo;
    const char* pszServerId = "Xmail_Server";
    const char* pszClientId = "Xmail_Client";
    const char* pszId = NULL;
    SSL_CTX* pSSLCtx = NULL;
    SSL* pSSLSession = NULL;

    ZeroData(addrInfo);

    SysGetPeerInfo(SockFD,
                   addrInfo);

    SysInetNToA(addrInfo,
                szSessionId, sizeof(szSessionId)); /* [i_a] */

    if(iSSLInit)
    {
        if(iIsServerCtx)
        {
            pSSLCtx = pSSLSrvCtx;
            pszId = pszServerId;
        }
        else
        {
            pSSLCtx = pSSLCliCtx;
            pszId = pszClientId;
        }

        StrNCat(szSessionId,
                pszId,
                CStringSize(szSessionId) - strlen(szSessionId));

        pSSLSession = SSL_new(pSSLCtx);

        if(pSSLSession != NULL)
        {
#ifdef DEBUG_SSL
            SSL_set_msg_callback(pSSLSession, msg_cb);
#endif
#if SSLEAY_VERSION_NUMBER >= 0x0922
            SSL_set_session_id_context(pSSLSession,
                                       (const unsigned char*)&szSessionId,
                                       (unsigned int)strlen(szSessionId));
#endif
            BIO_set_tcp_ndelay(SockFD, 1); /* [i_a] */
            SSL_set_fd(pSSLSession,
                       SockFD);

            if(iIsServerCtx)
            {
                SSL_set_accept_state(pSSLSession);
            }
            else
            {
                SSL_set_connect_state(pSSLSession);
            }

            time_t tTimeOut = time(NULL) + iTimeOut;

            for(;;)
            {
                int iResult;

                if(iIsServerCtx)
                {
                    iResult = SSL_accept(pSSLSession);
                }
                else
                {
                    iResult = SSL_connect(pSSLSession);
                }

                iResult = SSL_get_error(pSSLSession,
                                        iResult);
                switch(iResult)
                {
                case SSL_ERROR_NONE:

                    break;

                case SSL_ERROR_WANT_READ:
                case SSL_ERROR_WANT_WRITE:
                case SSL_ERROR_WANT_X509_LOOKUP:

                    if(time(NULL) < tTimeOut)
                    {
                        SysMsSleep(1);
                        continue;
                    }

                default:

                    SSL_free(pSSLSession);
                    pSSLSession = NULL;
                }

                break;
            }
        }
    }

    return (pSSLSession);
}