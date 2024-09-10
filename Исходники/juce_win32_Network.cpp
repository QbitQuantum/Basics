    void openHTTPConnection (URL_COMPONENTS& uc, URL::OpenStreamProgressCallback* progressCallback,
                             void* progressCallbackContext)
    {
        const TCHAR* mimeTypes[] = { _T("*/*"), 0 };

        DWORD flags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_NO_COOKIES;

        if (address.startsWithIgnoreCase ("https:"))
            flags |= INTERNET_FLAG_SECURE;  // (this flag only seems necessary if the OS is running IE6 -
                                            //  IE7 seems to automatically work out when it's https)

        request = HttpOpenRequest (connection, isPost ? _T("POST") : _T("GET"),
                                   uc.lpszUrlPath, 0, 0, mimeTypes, flags, 0);

        if (request != 0)
        {
            INTERNET_BUFFERS buffers = { 0 };
            buffers.dwStructSize = sizeof (INTERNET_BUFFERS);
            buffers.lpcszHeader = headers.toWideCharPointer();
            buffers.dwHeadersLength = (DWORD) headers.length();
            buffers.dwBufferTotal = (DWORD) postData.getSize();

            if (HttpSendRequestEx (request, &buffers, 0, HSR_INITIATE, 0))
            {
                int bytesSent = 0;

                for (;;)
                {
                    const int bytesToDo = jmin (1024, (int) postData.getSize() - bytesSent);
                    DWORD bytesDone = 0;

                    if (bytesToDo > 0
                         && ! InternetWriteFile (request,
                                                 static_cast <const char*> (postData.getData()) + bytesSent,
                                                 (DWORD) bytesToDo, &bytesDone))
                    {
                        break;
                    }

                    if (bytesToDo == 0 || (int) bytesDone < bytesToDo)
                    {
                        if (HttpEndRequest (request, 0, 0, 0))
                            return;

                        break;
                    }

                    bytesSent += bytesDone;

                    if (progressCallback != nullptr
                          && ! progressCallback (progressCallbackContext, bytesSent, (int) postData.getSize()))
                        break;
                }
            }
        }

        close();
    }