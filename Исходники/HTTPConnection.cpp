int HttpConnection::sendData(const char* data, int data_len)
{
    int totalBytesRead = 0;
    int ret = 0;
    DWORD bytesWritten = 0;
    DWORD errorCode = 0;

    if (!InternetWriteFile(req, data, data_len, &bytesWritten)) {
        errorCode = GetLastError();

        char* tmp = createHttpErrorMessage(errorCode);
        setErrorF(errorCode, "InternetWriteFile error %d: %s", errorCode, tmp);
        LOG.info("%s", getLastErrorMsg());
        delete [] tmp; tmp = NULL;
        //
        // The certificate is not trusted. Send the right error code to the
        // client
        //
        if (errorCode == ERROR_INTERNET_INVALID_CA) {
            setError(ERR_HTTPS_INVALID_CA, "The certificate is invalid");
            LOG.error("%s", getLastErrorMsg());

            // try to understand a bit more on the certificate
            INTERNET_CERTIFICATE_INFO   certificateInfo;
            DWORD                       certInfoLength = sizeof(INTERNET_CERTIFICATE_INFO);                
            if (TRUE == InternetQueryOption(req, INTERNET_OPTION_SECURITY_CERTIFICATE_STRUCT, 
                &certificateInfo, &certInfoLength)) {

                    char* subj   = (char*)certificateInfo.lpszSubjectInfo;
                    char* issuer = (char*)certificateInfo.lpszIssuerInfo;    
                    LOG.debug("Cert Subject %s", subj);
                    LOG.debug("Cert Issuer %s",  issuer);

            } else {                        
                LOG.debug("Cannot retrieve info about the certificate");
            }     
        } else if (errorCode == ERROR_INTERNET_OFFLINE_MODE) {                     // 00002 -> retry
            LOG.debug("Offline mode detected: go-online and retry...");
            WCHAR* wurl = toWideChar(url.fullURL);
            InternetGoOnline(wurl, NULL, NULL);
            delete [] wurl;
        } else if (errorCode == ERROR_INTERNET_TIMEOUT ||                     // 12002 -> out code 2007
            errorCode == ERROR_INTERNET_INCORRECT_HANDLE_STATE) {      // 12019 -> out code 2007
                setError(ERR_HTTP_TIME_OUT, "Network error: the request has timed out -> exit.");
                LOG.debug("%s", getLastErrorMsg());
        } else if (errorCode == ERROR_INTERNET_CANNOT_CONNECT) {              // 12029 -> out code 2001
            setError(ERR_CONNECT, "Network error: the attempt to connect to the server failed -> exit"); 
            LOG.debug("%s", getLastErrorMsg());
        }
        // Other network error: retry.
        LOG.info("Network error writing data from client");
        resetError();
    }

    if (bytesWritten != data_len) {
        LOG.error("[%s] Warning: possible loss of data: %d bytes read, %d bytes written", 
            __FUNCTION__, data_len, bytesWritten);
    }

    return errorCode;
}