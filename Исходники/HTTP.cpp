bool
CHttp::Authorize (unsigned long *num)
{
    INT						count=0;
    DWORD					numsize = sizeof(DWORD);
	DWORD					lasterr=0;
	DWORD					flags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_KEEP_CONNECTION;
	HINTERNET				authrequest = NULL;

	/* set the flags for internet connection  and check if SSL required */
	if (wcsicmp (m_Protocol, L"https" ) == 0 )
		flags |= INTERNET_FLAG_SECURE;

	/* create a temporary internet request for proxy handling */
	authrequest = HttpOpenRequest(m_InternetConnect, L"POST", m_FileName, NULL, NULL, NULL, flags, 0L );
	if (!authrequest )
		return false;

retry:

    /* post a dummy request to check for auth */
	if (!yog_HttpSendRequest(&lasterr, authrequest, NULL, 0, NULL, 0) ) {

        if (lasterr == ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED ) {

            // Return ERROR_SUCCESS regardless of clicking on OK or Cancel
            if(lasterr = InternetErrorDlg(GetDesktopWindow(), 
                                    authrequest,
                                    ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED,
                                    FLAGS_ERROR_UI_FILTER_FOR_ERRORS       |
                                    FLAGS_ERROR_UI_FLAGS_GENERATE_DATA     |
                                    FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, 
                                    NULL) != ERROR_SUCCESS )
            {
                goto cleanup;
            } else
			{
                goto retry;
			}
        }
		if ((lasterr == ERROR_INTERNET_INVALID_CA) ||
            (lasterr == ERROR_INTERNET_SEC_CERT_CN_INVALID) || 
            (lasterr == ERROR_INTERNET_SEC_CERT_DATE_INVALID )) {

                DWORD flags;
                DWORD flaglen = sizeof(flags);
			
			/*  this means the HTTP site is not authorised by a valid certification so we ignore it and
				move ahead */	
            InternetQueryOption (authrequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)&flags, &flaglen);
			flags |= IGNORE_CERT;
            if (!InternetSetOption (authrequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)&flags, sizeof (flags) ) )
				goto cleanup;
			else 
			{
				goto retry;
			}
        }
    }

    if ( !HttpQueryInfo ( authrequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,  (LPVOID)num, &numsize, NULL))
        goto cleanup;

	if ( *num == HTTP_STATUS_DENIED || *num == HTTP_STATUS_PROXY_AUTH_REQ )
	{
        count++;

        if (count > 3 )
            goto cleanup;

        if (SetAuthDetails ( authrequest, *num ))
		{
            goto retry;
		}
        else
            goto cleanup;
    }

    InternetCloseHandle (authrequest );
    // We don't want to descard the output

	return true;

cleanup:
	InternetCloseHandle (authrequest );
	return false;
}