//Only for types from LSI_VAR_SSL_VERSION to LSI_VAR_PATH_TRANSLATED which are defined in ls.h
int RequestVars::getReqVar2(HttpSession *pSession, int type, char *&pValue,
                            int bufLen)
{
    HttpReq *pReq = pSession->getReq();
    int ret = 0;

    if (type >= LSI_VAR_SSL_VERSION && type <= LSI_VAR_SSL_CLIENT_CERT)
    {
        if (!pSession->isSSL())
            return 0;

        SslConnection *pSSL = pSession->getSSL();
        if (type == LSI_VAR_SSL_VERSION)
        {
            pValue = (char *)pSSL->getVersion();
            ret = strlen(pValue);
            return ret;
        }
        else if (type == LSI_VAR_SSL_SESSION_ID)
        {
            SSL_SESSION *pSession = pSSL->getSession();
            if (pSession)
            {
                int idLen = SslConnection::getSessionIdLen(pSession);
                ret = idLen * 2;
                if (ret > bufLen)
                    ret = bufLen;
                StringTool::hexEncode((char *)SslConnection::getSessionId(pSession),
                                      ret / 2, pValue);
            }
            return ret;
        }
        else if (type == LSI_VAR_SSL_CLIENT_CERT)
        {
            X509 *pClientCert = pSSL->getPeerCertificate();
            if (pClientCert)
                ret = SslCert::PEMWriteCert(pClientCert, pValue, bufLen);

            return ret;
        }
        else
        {
            const SSL_CIPHER *pCipher = pSSL->getCurrentCipher();
            if (pCipher)
            {
                if (type == LSI_VAR_SSL_CIPHER)
                {
                    pValue = (char *)pSSL->getCipherName();
                    ret = strlen(pValue);
                }
                else
                {
                    int algkeysize;
                    int keysize = SslConnection::getCipherBits(pCipher, &algkeysize);
                    if (type == LSI_VAR_SSL_CIPHER_USEKEYSIZE)
                        ret = ls_snprintf(pValue, 20, "%d", keysize);
                    else //LSI_VAR_SSL_CIPHER_ALGKEYSIZE
                        ret = ls_snprintf(pValue, 20, "%d", algkeysize);
                }
            }
            return ret;
        }
    }
    else if (type == LSI_VAR_GEOIP_ADDR)
    {
        ret = pSession->getPeerAddrStrLen();
        pValue = (char *)pSession->getPeerAddrString();
        return ret;
    }
    else if (type == LSI_VAR_PATH_TRANSLATED)
    {
        int n = pReq->getPathInfoLen();
        if (n > 0)
            ret =  pReq->translatePath(pReq->getPathInfo(), n, pValue, bufLen);
        return ret;
    }
    else
        return 0;
}