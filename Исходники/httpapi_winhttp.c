HTTPAPI_RESULT HTTPAPI_ExecuteRequest(HTTP_HANDLE handle, HTTPAPI_REQUEST_TYPE requestType, const char* relativePath,
    HTTP_HEADERS_HANDLE httpHeadersHandle, const unsigned char* content,
    size_t contentLength, unsigned int* statusCode,
    HTTP_HEADERS_HANDLE responseHeadersHandle, BUFFER_HANDLE responseContent)
{
    HTTPAPI_RESULT result;
    if (g_HTTPAPIState != HTTPAPI_INITIALIZED)
    {
        LogError("g_HTTPAPIState not HTTPAPI_INITIALIZED");
        result = HTTPAPI_NOT_INIT;
    }
    else
    {
        HTTP_HANDLE_DATA* handleData = (HTTP_HANDLE_DATA*)handle;

        if ((handleData == NULL) ||
            (relativePath == NULL) ||
            (httpHeadersHandle == NULL))
        {
            result = HTTPAPI_INVALID_ARG;
            LogError("NULL parameter detected (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
        }
        else
        {
            wchar_t* requestTypeString = NULL;

            switch (requestType)
            {
            default:
                break;

            case HTTPAPI_REQUEST_GET:
                requestTypeString = L"GET";
                break;

            case HTTPAPI_REQUEST_POST:
                requestTypeString = L"POST";
                break;

            case HTTPAPI_REQUEST_PUT:
                requestTypeString = L"PUT";
                break;

            case HTTPAPI_REQUEST_DELETE:
                requestTypeString = L"DELETE";
                break;

            case HTTPAPI_REQUEST_PATCH:
                requestTypeString = L"PATCH";
                break;
            }

            if (requestTypeString == NULL)
            {
                result = HTTPAPI_INVALID_ARG;
                LogError("requestTypeString was NULL (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
            }
            else
            {
                const char* headers2;
                headers2 = ConstructHeadersString(httpHeadersHandle);
                if (headers2 != NULL)
                {
                    size_t requiredCharactersForRelativePath = MultiByteToWideChar(CP_ACP, 0, relativePath, -1, NULL, 0);
                    wchar_t* relativePathTemp = (wchar_t*)malloc((requiredCharactersForRelativePath+1) * sizeof(wchar_t));
                    result = HTTPAPI_OK; /*legacy code*/

                    if (relativePathTemp == NULL)
                    {
                        result = HTTPAPI_ALLOC_FAILED;
                        LogError("malloc failed (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                    }
                    else
                    {
                        if (MultiByteToWideChar(CP_ACP, 0, relativePath, -1, relativePathTemp, (int)requiredCharactersForRelativePath) == 0)
                        {
                            result = HTTPAPI_STRING_PROCESSING_ERROR;
                            LogError("MultiByteToWideChar was 0. (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                        }
                        else
                        {
                            size_t requiredCharactersForHeaders = MultiByteToWideChar(CP_ACP, 0, headers2, -1, NULL, 0);

                            wchar_t* headersTemp = (wchar_t*)malloc((requiredCharactersForHeaders +1) * sizeof(wchar_t) );
                            if (headersTemp == NULL)
                            {
                                result = HTTPAPI_STRING_PROCESSING_ERROR;
                                LogError("MultiByteToWideChar was 0. (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                            }
                            else
                            {
                                if (MultiByteToWideChar(CP_ACP, 0, headers2, -1, headersTemp, (int)requiredCharactersForHeaders) == 0)
                                {
                                    result = HTTPAPI_STRING_PROCESSING_ERROR;
                                    LogError("MultiByteToWideChar was 0(result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                }
                                else
                                {
                                    HINTERNET requestHandle = WinHttpOpenRequest(
                                        handleData->ConnectionHandle,
                                        requestTypeString,
                                        relativePathTemp,
                                        NULL,
                                        WINHTTP_NO_REFERER,
                                        WINHTTP_DEFAULT_ACCEPT_TYPES,
                                        WINHTTP_FLAG_SECURE);
                                    if (requestHandle == NULL)
                                    {
                                        result = HTTPAPI_OPEN_REQUEST_FAILED;
                                        LogErrorWinHTTPWithGetLastErrorAsString("WinHttpOpenRequest failed (result = %s).", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                    }
                                    else
                                    {
                                        if ((handleData->x509SchannelHandle!=NULL) && 
                                            !WinHttpSetOption(
                                                requestHandle,
                                                WINHTTP_OPTION_CLIENT_CERT_CONTEXT,
                                                (void*)x509_schannel_get_certificate_context(handleData->x509SchannelHandle),
                                                sizeof(CERT_CONTEXT)
                                        ))
                                        {
                                            LogErrorWinHTTPWithGetLastErrorAsString("unable to WinHttpSetOption");
                                            result = HTTPAPI_SET_X509_FAILURE;
                                        }
                                        else
                                        {
                                            if (WinHttpSetTimeouts(requestHandle,
                                                0,                      /*_In_  int dwResolveTimeout - The initial value is zero, meaning no time-out (infinite). */
                                                60000,                  /*_In_  int dwConnectTimeout, -  The initial value is 60,000 (60 seconds).*/
                                                handleData->timeout,    /*_In_  int dwSendTimeout, -  The initial value is 30,000 (30 seconds).*/
                                                handleData->timeout     /* int dwReceiveTimeout The initial value is 30,000 (30 seconds).*/
                                            ) == FALSE)
                                            {
                                                result = HTTPAPI_SET_TIMEOUTS_FAILED;
                                                LogErrorWinHTTPWithGetLastErrorAsString("WinHttpOpenRequest failed (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                            }
                                            else
                                            {
                                                DWORD dwSecurityFlags = 0;

                                                if (!WinHttpSetOption(
                                                    requestHandle,
                                                    WINHTTP_OPTION_SECURITY_FLAGS,
                                                    &dwSecurityFlags,
                                                    sizeof(dwSecurityFlags)))
                                                {
                                                    result = HTTPAPI_SET_OPTION_FAILED;
                                                    LogErrorWinHTTPWithGetLastErrorAsString("WinHttpSetOption failed (result = %s).", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                }
                                                else
                                                {
                                                    if (!WinHttpSendRequest(
                                                        requestHandle,
                                                        headersTemp,
                                                        (DWORD)-1L, /*An unsigned long integer value that contains the length, in characters, of the additional headers. If this parameter is -1L ... */
                                                        (void*)content,
                                                        (DWORD)contentLength,
                                                        (DWORD)contentLength,
                                                        0))
                                                    {
                                                        result = HTTPAPI_SEND_REQUEST_FAILED;
                                                        LogErrorWinHTTPWithGetLastErrorAsString("WinHttpSendRequest: (result = %s).", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                    }
                                                    else
                                                    {
                                                        if (!WinHttpReceiveResponse(
                                                            requestHandle,
                                                            0))
                                                        {
                                                            result = HTTPAPI_RECEIVE_RESPONSE_FAILED;
                                                            LogErrorWinHTTPWithGetLastErrorAsString("WinHttpReceiveResponse: (result = %s).", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                        }
                                                        else
                                                        {
                                                            DWORD dwStatusCode = 0;
                                                            DWORD dwBufferLength = sizeof(DWORD);
                                                            DWORD responseBytesAvailable;

                                                            if (!WinHttpQueryHeaders(
                                                                requestHandle,
                                                                WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                                                                WINHTTP_HEADER_NAME_BY_INDEX,
                                                                &dwStatusCode,
                                                                &dwBufferLength,
                                                                WINHTTP_NO_HEADER_INDEX))
                                                            {
                                                                result = HTTPAPI_QUERY_HEADERS_FAILED;
                                                                LogErrorWinHTTPWithGetLastErrorAsString("WinHttpQueryHeaders failed (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                            }
                                                            else
                                                            {
                                                                BUFFER_HANDLE useToReadAllResponse = (responseContent != NULL) ? responseContent : BUFFER_new();

                                                                if (statusCode != NULL)
                                                                {
                                                                    *statusCode = dwStatusCode;
                                                                }

                                                                if (useToReadAllResponse == NULL)
                                                                {
                                                                    result = HTTPAPI_ERROR;
                                                                    LogError("(result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                                }
                                                                else
                                                                {

                                                                    int goOnAndReadEverything = 1;
                                                                    do
                                                                    {
                                                                        /*from MSDN: If no data is available and the end of the file has not been reached, one of two things happens. If the session is synchronous, the request waits until data becomes available.*/
                                                                        if (!WinHttpQueryDataAvailable(requestHandle, &responseBytesAvailable))
                                                                        {
                                                                            result = HTTPAPI_QUERY_DATA_AVAILABLE_FAILED;
                                                                            LogErrorWinHTTPWithGetLastErrorAsString("WinHttpQueryDataAvailable failed (result = %s).", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                                            goOnAndReadEverything = 0;
                                                                        }
                                                                        else if (responseBytesAvailable == 0)
                                                                        {
                                                                            /*end of the stream, go out*/
                                                                            result = HTTPAPI_OK;
                                                                            goOnAndReadEverything = 0;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (BUFFER_enlarge(useToReadAllResponse, responseBytesAvailable) != 0)
                                                                            {
                                                                                result = HTTPAPI_ERROR;
                                                                                LogError("(result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                                                goOnAndReadEverything = 0;
                                                                            }
                                                                            else
                                                                            {
                                                                                /*Add the read bytes to the response buffer*/
                                                                                size_t bufferSize;
                                                                                const unsigned char* bufferContent;

                                                                                if (BUFFER_content(useToReadAllResponse, &bufferContent) != 0)
                                                                                {
                                                                                    result = HTTPAPI_ERROR;
                                                                                    LogError("(result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                                                    goOnAndReadEverything = 0;
                                                                                }
                                                                                else if (BUFFER_size(useToReadAllResponse, &bufferSize) != 0)
                                                                                {
                                                                                    result = HTTPAPI_ERROR;
                                                                                    LogError("(result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                                                    goOnAndReadEverything = 0;
                                                                                }
                                                                                else
                                                                                {
                                                                                    DWORD bytesReceived;
                                                                                    if (!WinHttpReadData(requestHandle, (LPVOID)(bufferContent + bufferSize - responseBytesAvailable), responseBytesAvailable, &bytesReceived))
                                                                                    {
                                                                                        result = HTTPAPI_READ_DATA_FAILED;
                                                                                        LogErrorWinHTTPWithGetLastErrorAsString("WinHttpReadData failed (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                                                        goOnAndReadEverything = 0;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        /*if for some reason bytesReceived is zero If you are using WinHttpReadData synchronously, and the return value is TRUE and the number of bytes read is zero, the transfer has been completed and there are no more bytes to read on the handle.*/
                                                                                        if (bytesReceived == 0)
                                                                                        {
                                                                                            /*end of everything, but this looks like an error still, or a non-conformance between WinHttpQueryDataAvailable and WinHttpReadData*/
                                                                                            result = HTTPAPI_READ_DATA_FAILED;
                                                                                            LogError("bytesReceived was unexpectedly zero (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                                                            goOnAndReadEverything = 0;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            /*all is fine, keep going*/
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }

                                                                    } while (goOnAndReadEverything != 0);
                                                                }
                                                            }

                                                            if (result == HTTPAPI_OK && responseHeadersHandle != NULL)
                                                            {
                                                                wchar_t* responseHeadersTemp;
                                                                DWORD responseHeadersTempLength = sizeof(responseHeadersTemp);

                                                                (void)WinHttpQueryHeaders(
                                                                    requestHandle,
                                                                    WINHTTP_QUERY_RAW_HEADERS_CRLF,
                                                                    WINHTTP_HEADER_NAME_BY_INDEX,
                                                                    WINHTTP_NO_OUTPUT_BUFFER,
                                                                    &responseHeadersTempLength,
                                                                    WINHTTP_NO_HEADER_INDEX);

                                                                responseHeadersTemp = (wchar_t*)malloc(responseHeadersTempLength + 2);
                                                                if (responseHeadersTemp == NULL)
                                                                {
                                                                    result = HTTPAPI_ALLOC_FAILED;
                                                                    LogError("malloc failed: (result = %s)", ENUM_TO_STRING(HTTPAPI_RESULT, result));
                                                                }
                                                                else
                                                                {
                                                                    if (WinHttpQueryHeaders(
                                                                        requestHandle,
                                                                        WINHTTP_QUERY_RAW_HEADERS_CRLF,
                                                                        WINHTTP_HEADER_NAME_BY_INDEX,
                                                                        responseHeadersTemp,
                                                                        &responseHeadersTempLength,
                                                                        WINHTTP_NO_HEADER_INDEX))
                                                                    {
                                                                        wchar_t *next_token;
                                                                        wchar_t* token = wcstok_s(responseHeadersTemp, L"\r\n", &next_token);
                                                                        while ((token != NULL) &&
                                                                            (token[0] != L'\0'))
                                                                        {
                                                                            char* tokenTemp;
                                                                            size_t tokenTemp_size;

                                                                            tokenTemp_size = WideCharToMultiByte(CP_ACP, 0, token, -1, NULL, 0, NULL, NULL);
                                                                            if (tokenTemp_size == 0)
                                                                            {
                                                                                LogError("WideCharToMultiByte failed");
                                                                            }
                                                                            else
                                                                            {
                                                                                tokenTemp = (char*)malloc(sizeof(char)*tokenTemp_size);
                                                                                if (tokenTemp == NULL)
                                                                                {
                                                                                    LogError("malloc failed");
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (WideCharToMultiByte(CP_ACP, 0, token, -1, tokenTemp, (int)tokenTemp_size, NULL, NULL) > 0)
                                                                                    {
                                                                                        /*breaking the token in 2 parts: everything before the first ":" and everything after the first ":"*/
                                                                                        /* if there is no such character, then skip it*/
                                                                                        /*if there is a : then replace is by a '\0' and so it breaks the original string in name and value*/

                                                                                        char* whereIsColon = strchr(tokenTemp, ':');
                                                                                        if (whereIsColon != NULL)
                                                                                        {
                                                                                            *whereIsColon = '\0';
                                                                                            if (HTTPHeaders_AddHeaderNameValuePair(responseHeadersHandle, tokenTemp, whereIsColon + 1) != HTTP_HEADERS_OK)
                                                                                            {
                                                                                                LogError("HTTPHeaders_AddHeaderNameValuePair failed");
                                                                                                result = HTTPAPI_HTTP_HEADERS_FAILED;
                                                                                                break;
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        LogError("WideCharToMultiByte failed");
                                                                                    }
                                                                                    free(tokenTemp);
                                                                                }
                                                                            }


                                                                            token = wcstok_s(NULL, L"\r\n", &next_token);
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        LogError("WinHttpQueryHeaders failed");
                                                                    }

                                                                    free(responseHeadersTemp);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        (void)WinHttpCloseHandle(requestHandle);
                                    }
                                }
                                free(headersTemp);
                            }
                        }
                        free(relativePathTemp);
                    }
                    free((void*)headers2);
                }
                else
                {
                    result = HTTPAPI_ALLOC_FAILED; /*likely*/
                    LogError("ConstructHeadersString failed");
                }
            }
        }
    }

    return result;
}