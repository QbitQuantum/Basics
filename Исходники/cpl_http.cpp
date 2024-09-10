/**
 * \brief Fetch a document from an url and return in a string.
 *
 * @param pszURL valid URL recognized by underlying download library (libcurl)
 * @param papszOptions option list as a NULL-terminated array of strings. May be NULL.
 *                     The following options are handled :
 * <ul>
 * <li>TIMEOUT=val, where val is in seconds. This is the maximum delay for the whole
 *     request to complete before being aborted.</li>
 * <li>LOW_SPEED_TIME=val, where val is in seconds. This is the maximum time where the
 *      transfer speed should be below the LOW_SPEED_LIMIT (if not specified 1b/s),
 *      before the transfer to be considered too slow and aborted. (GDAL >= 2.1)</li>
 * <li>LOW_SPEED_LIMIT=val, where val is in bytes/second. See LOW_SPEED_TIME. Has only
 *     effect if LOW_SPEED_TIME is specified too. (GDAL >= 2.1)</li>
 * <li>HEADERS=val, where val is an extra header to use when getting a web page.
 *                  For example "Accept: application/x-ogcwkt"
 * <li>HTTPAUTH=[BASIC/NTLM/GSSNEGOTIATE/ANY] to specify an authentication scheme to use.
 * <li>USERPWD=userid:password to specify a user and password for authentication
 * <li>POSTFIELDS=val, where val is a nul-terminated string to be passed to the server
 *                     with a POST request.
 * <li>PROXY=val, to make requests go through a proxy server, where val is of the
 *                form proxy.server.com:port_number
 * <li>PROXYUSERPWD=val, where val is of the form username:password
 * <li>PROXYAUTH=[BASIC/NTLM/DIGEST/ANY] to specify an proxy authentication scheme to use.
 * <li>NETRC=[YES/NO] to enable or disable use of $HOME/.netrc, default YES.
 * <li>CUSTOMREQUEST=val, where val is GET, PUT, POST, DELETE, etc.. (GDAL >= 1.9.0)
 * <li>COOKIE=val, where val is formatted as COOKIE1=VALUE1; COOKIE2=VALUE2; ...
 * <li>MAX_RETRY=val, where val is the maximum number of retry attempts if a 503 or
 *               504 HTTP error occurs. Default is 0. (GDAL >= 2.0)
 * <li>RETRY_DELAY=val, where val is the number of seconds between retry attempts.
 *                 Default is 30. (GDAL >= 2.0)
 * </ul>
 *
 * Alternatively, if not defined in the papszOptions arguments, the TIMEOUT,
 * LOW_SPEED_TIME, LOW_SPEED_LIMIT, PROXY, PROXYUSERPWD, PROXYAUTH, NETRC,
 * MAX_RETRY and RETRY_DELAY values are searched in the configuration 
 * options named GDAL_HTTP_TIMEOUT, GDAL_HTTP_LOW_SPEED_TIME, GDAL_HTTP_LOW_SPEED_LIMIT,
 * GDAL_HTTP_PROXY, GDAL_HTTP_PROXYUSERPWD, GDAL_PROXY_AUTH, 
 * GDAL_HTTP_NETRC, GDAL_HTTP_MAX_RETRY and GDAL_HTTP_RETRY_DELAY.
 *
 * @return a CPLHTTPResult* structure that must be freed by 
 * CPLHTTPDestroyResult(), or NULL if libcurl support is disabled
 */
CPLHTTPResult *CPLHTTPFetch( const char *pszURL, char **papszOptions )

{
    if( strncmp(pszURL, "/vsimem/", strlen("/vsimem/")) == 0 &&
        /* Disabled by default for potential security issues */
        CSLTestBoolean(CPLGetConfigOption("CPL_CURL_ENABLE_VSIMEM", "FALSE")) )
    {
        CPLString osURL(pszURL);
        const char* pszCustomRequest = CSLFetchNameValue( papszOptions, "CUSTOMREQUEST" );
        if( pszCustomRequest != NULL )
        {
            osURL += "&CUSTOMREQUEST=";
            osURL += pszCustomRequest;
        }
        const char* pszPost = CSLFetchNameValue( papszOptions, "POSTFIELDS" );
        if( pszPost != NULL ) /* Hack: we append post content to filename */
        {
            osURL += "&POSTFIELDS=";
            osURL += pszPost;
        }
        vsi_l_offset nLength = 0;
        CPLHTTPResult* psResult = (CPLHTTPResult* )CPLCalloc(1, sizeof(CPLHTTPResult));
        GByte* pabyData = VSIGetMemFileBuffer( osURL, &nLength, FALSE );
        if( pabyData == NULL )
        {
            CPLDebug("HTTP", "Cannot find %s", osURL.c_str());
            psResult->nStatus = 1;
            psResult->pszErrBuf = CPLStrdup(CPLSPrintf("HTTP error code : %d", 404));
            CPLError( CE_Failure, CPLE_AppDefined, "%s", psResult->pszErrBuf );
        }
        else if( nLength != 0 )
        {
            psResult->nDataLen = (size_t)nLength;
            psResult->pabyData = (GByte*) CPLMalloc((size_t)nLength + 1);
            memcpy(psResult->pabyData, pabyData, (size_t)nLength);
            psResult->pabyData[(size_t)nLength] = 0;
        }

        if( psResult->pabyData != NULL &&
            strncmp((const char*)psResult->pabyData, "Content-Type: ",
                    strlen("Content-Type: ")) == 0 )
        {
            const char* pszContentType = (const char*)psResult->pabyData + strlen("Content-type: ");
            const char* pszEOL = strchr(pszContentType, '\r');
            if( pszEOL )
                pszEOL = strchr(pszContentType, '\n');
            if( pszEOL )
            {
                int nLength = pszEOL - pszContentType;
                psResult->pszContentType = (char*)CPLMalloc(nLength + 1);
                memcpy(psResult->pszContentType, pszContentType, nLength);
                psResult->pszContentType[nLength] = 0;
            }
        }

        return psResult;
    }

#ifndef HAVE_CURL
    (void) papszOptions;
    (void) pszURL;

    CPLError( CE_Failure, CPLE_NotSupported,
              "GDAL/OGR not compiled with libcurl support, remote requests not supported." );
    return NULL;
#else

/* -------------------------------------------------------------------- */
/*      Are we using a persistent named session?  If so, search for     */
/*      or create it.                                                   */
/*                                                                      */
/*      Currently this code does not attempt to protect against         */
/*      multiple threads asking for the same named session.  If that    */
/*      occurs it will be in use in multiple threads at once which      */
/*      might have bad consequences depending on what guarantees        */
/*      libcurl gives - which I have not investigated.                  */
/* -------------------------------------------------------------------- */
    CURL *http_handle = NULL;

    const char *pszPersistent = CSLFetchNameValue( papszOptions, "PERSISTENT" );
    const char *pszClosePersistent = CSLFetchNameValue( papszOptions, "CLOSE_PERSISTENT" );
    if (pszPersistent)
    {
        CPLString osSessionName = pszPersistent;
        CPLMutexHolder oHolder( &hSessionMapMutex );

        if( poSessionMap == NULL )
            poSessionMap = new std::map<CPLString,CURL*>;
        if( poSessionMap->count( osSessionName ) == 0 )
        {
            (*poSessionMap)[osSessionName] = curl_easy_init();
            CPLDebug( "HTTP", "Establish persistent session named '%s'.",
                      osSessionName.c_str() );
        }

        http_handle = (*poSessionMap)[osSessionName];
    }
/* -------------------------------------------------------------------- */
/*      Are we requested to close a persistent named session?          */
/* -------------------------------------------------------------------- */
    else if (pszClosePersistent)
    {
        CPLString osSessionName = pszClosePersistent;
        CPLMutexHolder oHolder( &hSessionMapMutex );

        if( poSessionMap )
        {
            std::map<CPLString,CURL*>::iterator oIter = poSessionMap->find( osSessionName );
            if( oIter != poSessionMap->end() )
            {
                curl_easy_cleanup(oIter->second);
                poSessionMap->erase(oIter);
                if( poSessionMap->size() == 0 )
                {
                    delete poSessionMap;
                    poSessionMap = NULL;
                }
                CPLDebug( "HTTP", "Ended persistent session named '%s'.",
                        osSessionName.c_str() );
            }
            else
            {
                CPLDebug( "HTTP", "Could not find persistent session named '%s'.",
                        osSessionName.c_str() );
            }
        }

        return NULL;
    }
    else
        http_handle = curl_easy_init();

/* -------------------------------------------------------------------- */
/*      Setup the request.                                              */
/* -------------------------------------------------------------------- */
    char szCurlErrBuf[CURL_ERROR_SIZE+1];
    CPLHTTPResult *psResult;
    struct curl_slist *headers=NULL; 

    const char* pszArobase = strchr(pszURL, '@');
    const char* pszSlash = strchr(pszURL, '/');
    const char* pszColon = (pszSlash) ? strchr(pszSlash, ':') : NULL;
    if (pszArobase != NULL && pszColon != NULL && pszArobase - pszColon > 0)
    {
        /* http://user:[email protected] */
        char* pszSanitizedURL = CPLStrdup(pszURL);
        pszSanitizedURL[pszColon-pszURL] = 0;
        CPLDebug( "HTTP", "Fetch(%s:#password#%s)", pszSanitizedURL, pszArobase );
        CPLFree(pszSanitizedURL);
    }
    else
    {
        CPLDebug( "HTTP", "Fetch(%s)", pszURL );
    }

    psResult = (CPLHTTPResult *) CPLCalloc(1,sizeof(CPLHTTPResult));

    curl_easy_setopt(http_handle, CURLOPT_URL, pszURL );

    CPLHTTPSetOptions(http_handle, papszOptions);

    // turn off SSL verification, accept all servers with ssl
    curl_easy_setopt(http_handle, CURLOPT_SSL_VERIFYPEER, FALSE);

    /* Set Headers.*/
    const char *pszHeaders = CSLFetchNameValue( papszOptions, "HEADERS" );
    if( pszHeaders != NULL ) {
        CPLDebug ("HTTP", "These HTTP headers were set: %s", pszHeaders);
        headers = curl_slist_append(headers, pszHeaders);
        curl_easy_setopt(http_handle, CURLOPT_HTTPHEADER, headers);
    }

    // are we making a head request
    const char* pszNoBody = NULL;
    if ((pszNoBody = CSLFetchNameValue( papszOptions, "NO_BODY" )) != NULL)
    {
        if (CSLTestBoolean(pszNoBody)) 
        {
            CPLDebug ("HTTP", "HEAD Request: %s", pszURL);
            curl_easy_setopt(http_handle, CURLOPT_NOBODY, 1L);           
        }
    }

    // capture response headers
    curl_easy_setopt(http_handle, CURLOPT_HEADERDATA, psResult);
    curl_easy_setopt(http_handle, CURLOPT_HEADERFUNCTION, CPLHdrWriteFct);

    curl_easy_setopt(http_handle, CURLOPT_WRITEDATA, psResult );
    curl_easy_setopt(http_handle, CURLOPT_WRITEFUNCTION, CPLWriteFct );

    szCurlErrBuf[0] = '\0';

    curl_easy_setopt(http_handle, CURLOPT_ERRORBUFFER, szCurlErrBuf );

    static bool bHasCheckVersion = false;
    static bool bSupportGZip = false;
    if (!bHasCheckVersion)
    {
        bSupportGZip = strstr(curl_version(), "zlib/") != NULL;
        bHasCheckVersion = true;
    }
    int bGZipRequested = false;
    if (bSupportGZip && CSLTestBoolean(CPLGetConfigOption("CPL_CURL_GZIP", "YES")))
    {
        bGZipRequested = true;
        curl_easy_setopt(http_handle, CURLOPT_ENCODING, "gzip");
    }

/* -------------------------------------------------------------------- */
/*      If 502, 503 or 504 status code retry this HTTP call until max        */
/*      retry has been rearched                                         */
/* -------------------------------------------------------------------- */
    const char *pszRetryDelay = CSLFetchNameValue( papszOptions, "RETRY_DELAY" );
    if( pszRetryDelay == NULL )
        pszRetryDelay = CPLGetConfigOption( "GDAL_HTTP_RETRY_DELAY", "30" );
    const char *pszMaxRetries = CSLFetchNameValue( papszOptions, "MAX_RETRY" );
    if( pszMaxRetries == NULL )
        pszMaxRetries = CPLGetConfigOption( "GDAL_HTTP_MAX_RETRY", "0" );
    int nRetryDelaySecs = atoi(pszRetryDelay);
    int nMaxRetries = atoi(pszMaxRetries);
    int nRetryCount = 0;
    bool bRequestRetry;

    do
    {
        bRequestRetry = false;

/* -------------------------------------------------------------------- */
/*      Execute the request, waiting for results.                       */
/* -------------------------------------------------------------------- */
        psResult->nStatus = (int) curl_easy_perform( http_handle );

/* -------------------------------------------------------------------- */
/*      Fetch content-type if possible.                                 */
/* -------------------------------------------------------------------- */
        psResult->pszContentType = NULL;
        curl_easy_getinfo( http_handle, CURLINFO_CONTENT_TYPE,
                           &(psResult->pszContentType) );
        if( psResult->pszContentType != NULL )
            psResult->pszContentType = CPLStrdup(psResult->pszContentType);

/* -------------------------------------------------------------------- */
/*      Have we encountered some sort of error?                         */
/* -------------------------------------------------------------------- */
        if( strlen(szCurlErrBuf) > 0 )
        {
            bool bSkipError = false;

            /* Some servers such as http://115.113.193.14/cgi-bin/world/qgis_mapserv.fcgi?VERSION=1.1.1&SERVICE=WMS&REQUEST=GetCapabilities */
            /* invalidly return Content-Length as the uncompressed size, with makes curl to wait for more data */
            /* and time-out finally. If we got the expected data size, then we don't emit an error */
            /* but turn off GZip requests */
            if (bGZipRequested &&
                strstr(szCurlErrBuf, "transfer closed with") &&
                strstr(szCurlErrBuf, "bytes remaining to read"))
            {
                const char* pszContentLength =
                    CSLFetchNameValue(psResult->papszHeaders, "Content-Length");
                if (pszContentLength && psResult->nDataLen != 0 &&
                    atoi(pszContentLength) == psResult->nDataLen)
                {
                    const char* pszCurlGZIPOption = CPLGetConfigOption("CPL_CURL_GZIP", NULL);
                    if (pszCurlGZIPOption == NULL)
                    {
                        CPLSetConfigOption("CPL_CURL_GZIP", "NO");
                        CPLDebug("HTTP", "Disabling CPL_CURL_GZIP, because %s doesn't support it properly",
                                 pszURL);
                    }
                    psResult->nStatus = 0;
                    bSkipError = true;
                }
            }
            if (!bSkipError)
            {
                psResult->pszErrBuf = CPLStrdup(szCurlErrBuf);
                CPLError( CE_Failure, CPLE_AppDefined,
                        "%s", szCurlErrBuf );
            }
        }
        else
        {
            /* HTTP errors do not trigger curl errors. But we need to */
            /* propagate them to the caller though */
            long response_code = 0;
            curl_easy_getinfo(http_handle, CURLINFO_RESPONSE_CODE, &response_code);

            if (response_code >= 400 && response_code < 600)
            {
                /* If HTTP 502, 503 or 504 gateway timeout error retry after a pause */
                if ((response_code >= 502 && response_code <= 504) && nRetryCount < nMaxRetries)
                {
                    CPLError(CE_Warning, CPLE_AppDefined,
                             "HTTP error code: %d - %s. Retrying again in %d secs",
                             (int)response_code, pszURL, nRetryDelaySecs);
                    CPLSleep(nRetryDelaySecs);
                    nRetryCount++;

                    CPLFree(psResult->pszContentType);
                    psResult->pszContentType = NULL;
                    CSLDestroy(psResult->papszHeaders);
                    psResult->papszHeaders = NULL;
                    CPLFree(psResult->pabyData);
                    psResult->pabyData = NULL;
                    psResult->nDataLen = 0;
                    psResult->nDataAlloc = 0;

                    bRequestRetry = true;
                }
                else
                {
                    psResult->pszErrBuf = CPLStrdup(CPLSPrintf("HTTP error code : %d", (int)response_code));
                    CPLError( CE_Failure, CPLE_AppDefined, "%s", psResult->pszErrBuf );
                }
            }
        }
    }
    while (bRequestRetry);

    if (!pszPersistent)
        curl_easy_cleanup( http_handle );

    curl_slist_free_all(headers);

    return psResult;
#endif /* def HAVE_CURL */
}