CNetDataImpl* CNetRequestImpl::sendStream(common::InputStream* bodyStream)
{
    CNetDataImpl* pNetData = new CNetDataImpl;

    do
    {
        if ( isError() )
            break;

        if ( !HttpAddRequestHeaders( hRequest, szMultipartContType, -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE ) )
        {
            pszErrFunction = L"HttpAddRequestHeaders";
            break;
        }

	    INTERNET_BUFFERS BufferIn;
        memset(&BufferIn, 0, sizeof(INTERNET_BUFFERS));
	    BufferIn.dwStructSize = sizeof( INTERNET_BUFFERS ); // Must be set or error will occur
        BufferIn.dwBufferTotal = bodyStream->available() + strlen(szMultipartPrefix) + strlen(szMultipartPostfix);

        if(!HttpSendRequestEx( hRequest, &BufferIn, NULL, 0, 0))
        {
            pszErrFunction = L"HttpSendRequestEx";
            break;
        }

	    DWORD dwBytesWritten = 0;
        if ( !InternetWriteFile( hRequest, szMultipartPrefix, strlen(szMultipartPrefix), &dwBytesWritten) )
        {
            pszErrFunction = L"InternetWriteFile";
            break;
        }

        DWORD dwBufSize = 4096;
        char* pBuf = (char*)malloc(dwBufSize);
        int nReaded = 0;

	    do
	    {
            nReaded = bodyStream->read(pBuf,0,dwBufSize);
            if ( nReaded > 0 )
            {
		        if ( !InternetWriteFile( hRequest, pBuf, nReaded, &dwBytesWritten) )
                {
                    pszErrFunction = L"InternetWriteFile";
                    break;
                }
            }
	    }while(nReaded > 0);

        free(pBuf);

        if ( !InternetWriteFile( hRequest, szMultipartPostfix, strlen(szMultipartPostfix), &dwBytesWritten) )
        {
            pszErrFunction = L"InternetWriteFile";
            break;
        }

        if ( !HttpEndRequest(hRequest, NULL, 0, 0) )
        {
            pszErrFunction = L"HttpEndRequest";
            break;
        }

        if ( isError() )
            break;

        readResponse(pNetData);
    }while(0);

    return pNetData;
}