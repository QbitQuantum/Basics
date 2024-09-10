int HttpCgiTool::buildCommonEnv(IEnv *pEnv, HttpSession *pSession)
{
    int count = 0;
    HttpReq *pReq = pSession->getReq();
    const char *pTemp;
    int n;
    char buf[128];
    RadixNode *pNode;

    pTemp = pReq->getAuthUser();
    if (pTemp)
    {
        //NOTE: only Basic is support now
        pEnv->add("AUTH_TYPE", 9, "Basic", 5);
        pEnv->add("REMOTE_USER", 11, pTemp, strlen(pTemp));
        count += 2;
    }
    //ADD_ENV("REMOTE_IDENT", "" )        //TODO: not supported yet
    //extensions of CGI/1.1
    const AutoStr2 *pDocRoot = pReq->getDocRoot();
    pEnv->add("DOCUMENT_ROOT", 13,
              pDocRoot->c_str(), pDocRoot->len() - 1);
    pEnv->add("REMOTE_ADDR", 11, pSession->getPeerAddrString(),
              pSession->getPeerAddrStrLen());

    n = ls_snprintf(buf, 10, "%hu", pSession->getRemotePort());
    pEnv->add("REMOTE_PORT", 11, buf, n);

    n = pSession->getServerAddrStr(buf, 128);

    pEnv->add("SERVER_ADDR", 11, buf, n);

    pEnv->add("SERVER_NAME", 11, pReq->getHostStr(),  pReq->getHostStrLen());
    const AutoStr2 &sPort = pReq->getPortStr();
    pEnv->add("SERVER_PORT", 11, sPort.c_str(), sPort.len());
    pEnv->add("REQUEST_URI", 11, pReq->getOrgReqURL(),
              pReq->getOrgReqURLLen());
    count += 7;

    n = pReq->getPathInfoLen();
    if (n > 0)
    {
        int m;
        char achTranslated[10240];
        m =  pReq->translatePath(pReq->getPathInfo(), n,
                                 achTranslated, sizeof(achTranslated));
        if (m != -1)
        {
            pEnv->add("PATH_TRANSLATED", 15, achTranslated, m);
            ++count;
        }
        pEnv->add("PATH_INFO", 9, pReq->getPathInfo(), n);
        ++count;
    }

    //add geo IP env here
    if (pReq->isGeoIpOn())
    {
        GeoInfo *pInfo = pSession->getClientInfo()->getGeoInfo();
        if (pInfo)
        {
            pEnv->add("GEOIP_ADDR", 10, pSession->getPeerAddrString(),
                      pSession->getPeerAddrStrLen());
            count += pInfo->addGeoEnv(pEnv) + 1;
        }
    }
    n = pReq->getEnvCount();
    count += n;
    if ((pNode = (RadixNode *)pReq->getEnvNode()) != NULL)
        pNode->for_each2(addEnv, pEnv);

    if (pSession->getStream()->isSpdy())
    {
        const char *pProto = HioStream::getProtocolName((HiosProtocol)
                             pSession->getStream()->getProtocol());
        pEnv->add("X_SPDY", 6, pProto, strlen(pProto));
        ++count;
    }

    if (pSession->isSSL())
    {
        SslConnection *pSSL = pSession->getSSL();
        pEnv->add("HTTPS", 5, "on",  2);
        const char *pVersion = pSSL->getVersion();
        n = strlen(pVersion);
        pEnv->add("SSL_VERSION", 11, pVersion, n);
        count += 2;
        SSL_SESSION *pSession = pSSL->getSession();
        if (pSession)
        {
            int idLen = SslConnection::getSessionIdLen(pSession);
            n = idLen * 2;
            assert(n < (int)sizeof(buf));
            StringTool::hexEncode(
                (char *)SslConnection::getSessionId(pSession),
                idLen, buf);
            pEnv->add("SSL_SESSION_ID", 14, buf, n);
            ++count;
        }

        const SSL_CIPHER *pCipher = pSSL->getCurrentCipher();
        if (pCipher)
        {
            const char *pName = pSSL->getCipherName();
            n = strlen(pName);
            pEnv->add("SSL_CIPHER", 10, pName, n);
            int algkeysize;
            int keysize = SslConnection::getCipherBits(pCipher, &algkeysize);
            n = ls_snprintf(buf, 20, "%d", keysize);
            pEnv->add("SSL_CIPHER_USEKEYSIZE", 21, buf, n);
            n = ls_snprintf(buf, 20, "%d", algkeysize);
            pEnv->add("SSL_CIPHER_ALGKEYSIZE", 21, buf, n);
            count += 3;
        }

        int i = pSSL->getVerifyMode();
        if (i != 0)
        {
            char achBuf[4096];
            X509 *pClientCert = pSSL->getPeerCertificate();
            if (pSSL->isVerifyOk())
            {
                if (pClientCert)
                {
                    //IMPROVE: too many deep copy here.
                    //n = SslCert::PEMWriteCert( pClientCert, achBuf, 4096 );
                    //if ((n>0)&&( n <= 4096 ))
                    //{
                    //    pEnv->add( "SSL_CLIENT_CERT", 15, achBuf, n );
                    //    ++count;
                    //}
                    n = snprintf(achBuf, sizeof(achBuf), "%lu",
                                 X509_get_version(pClientCert) + 1);
                    pEnv->add("SSL_CLIENT_M_VERSION", 20, achBuf, n);
                    ++count;
                    n = lookup_ssl_cert_serial(pClientCert, achBuf, 4096);
                    if (n != -1)
                    {
                        pEnv->add("SSL_CLIENT_M_SERIAL", 19, achBuf, n);
                        ++count;
                    }
                    X509_NAME_oneline(X509_get_subject_name(pClientCert), achBuf, 4096);
                    pEnv->add("SSL_CLIENT_S_DN", 15, achBuf, strlen(achBuf));
                    ++count;
                    X509_NAME_oneline(X509_get_issuer_name(pClientCert), achBuf, 4096);
                    pEnv->add("SSL_CLIENT_I_DN", 15, achBuf, strlen(achBuf));
                    ++count;
                    if (SslConnection::isClientVerifyOptional(i))
                    {
                        strcpy(achBuf, "GENEROUS");
                        n = 8;
                    }
                    else
                    {
                        strcpy(achBuf, "SUCCESS");
                        n = 7;
                    }
                }
                else
                {
                    strcpy(achBuf, "NONE");
                    n = 4;
                }
            }
            else
                n = pSSL->buildVerifyErrorString(achBuf, sizeof(achBuf));
            pEnv->add("SSL_CLIENT_VERIFY", 17, achBuf, n);
            ++count;
        }

    }
    return count;
}