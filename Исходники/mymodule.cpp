REQUEST_NOTIFICATION_STATUS
CMyHttpModule::OnBeginRequest(
    IN IHttpContext * pHttpContext,
    IN IHttpEventProvider * pProvider
)
{
    HRESULT                         hr                  = S_OK;
    IHttpRequest*                   pRequest            = NULL;
	MODSECURITY_STORED_CONTEXT*		pConfig = NULL;
    
    UNREFERENCED_PARAMETER ( pProvider );

	EnterCriticalSection(&m_csLock);

    if ( pHttpContext == NULL ) 
    {
        hr = E_UNEXPECTED;
        goto Finished;
    }

    pRequest = pHttpContext->GetRequest();

    if ( pRequest == NULL )
    {
        hr = E_UNEXPECTED;
        goto Finished;
    }

    hr = MODSECURITY_STORED_CONTEXT::GetConfig(pHttpContext, &pConfig );
    
    if ( FAILED( hr ) )
    {
        //hr = E_UNEXPECTED;
		hr = S_OK;
        goto Finished;
    }

	// If module is disabled, dont go any further
	//
	if( pConfig->GetIsEnabled() == false )
	{
        goto Finished;
	}

	// every 3 seconds we check for changes in config file
	//
	DWORD ctime = GetTickCount();

	if(pConfig->m_Config == NULL || (ctime - pConfig->m_dwLastCheck) > 3000)
	{
		char *path;
		USHORT pathlen;

		hr = pConfig->GlobalWideCharToMultiByte(pConfig->GetPath(), wcslen(pConfig->GetPath()), &path, &pathlen);

		if ( FAILED( hr ) )
		{
			hr = E_UNEXPECTED;
			goto Finished;
		}

		WIN32_FILE_ATTRIBUTE_DATA fdata;
		BOOL ret;

		ret = GetFileAttributesEx(path, GetFileExInfoStandard, &fdata);

		pConfig->m_dwLastCheck = ctime;

		if(pConfig->m_Config == NULL || (ret != 0 && (pConfig->m_LastChange.dwLowDateTime != fdata.ftLastWriteTime.dwLowDateTime ||
			pConfig->m_LastChange.dwHighDateTime != fdata.ftLastWriteTime.dwHighDateTime)))
		{
			pConfig->m_LastChange.dwLowDateTime = fdata.ftLastWriteTime.dwLowDateTime;
			pConfig->m_LastChange.dwHighDateTime = fdata.ftLastWriteTime.dwHighDateTime;

			pConfig->m_Config = modsecGetDefaultConfig();

			PCWSTR servpath = pHttpContext->GetApplication()->GetApplicationPhysicalPath();
			char *apppath;
			USHORT apppathlen;

			hr = pConfig->GlobalWideCharToMultiByte((WCHAR *)servpath, wcslen(servpath), &apppath, &apppathlen);

			if ( FAILED( hr ) )
			{
				delete path;
				hr = E_UNEXPECTED;
				goto Finished;
			}

			if(path[0] != 0)
			{
				const char * err = modsecProcessConfig((directory_config *)pConfig->m_Config, path, apppath);

				if(err != NULL)
				{
					WriteEventViewerLog(err, EVENTLOG_ERROR_TYPE);
					delete apppath;
					delete path;
					goto Finished;
				}
			}
			delete apppath;
		}
		delete path;
	}

	conn_rec *c;
	request_rec *r;

	c = modsecNewConnection();

	modsecProcessConnection(c);

	r = modsecNewRequest(c, (directory_config *)pConfig->m_Config);

	// on IIS we force input stream inspection flag, because its absence does not add any performance gain
	// it's because on IIS request body must be restored each time it was read
	//
	modsecSetConfigForIISRequestBody(r);

	REQUEST_STORED_CONTEXT *rsc = new REQUEST_STORED_CONTEXT();

	rsc->m_pConnRec = c;
	rsc->m_pRequestRec = r;
	rsc->m_pHttpContext = pHttpContext;
	rsc->m_pProvider = pProvider;

	pHttpContext->GetModuleContextContainer()->SetModuleContext(rsc, g_pModuleContext);

	StoreIISContext(r, rsc);

	HTTP_REQUEST *req = pRequest->GetRawHttpRequest();

	r->hostname = ConvertUTF16ToUTF8(req->CookedUrl.pHost, req->CookedUrl.HostLength / sizeof(WCHAR), r->pool);
	r->path_info = ConvertUTF16ToUTF8(req->CookedUrl.pAbsPath, req->CookedUrl.AbsPathLength / sizeof(WCHAR), r->pool);

	if(r->hostname == NULL)
	{
		if(req->Headers.KnownHeaders[HttpHeaderHost].pRawValue != NULL)
			r->hostname = ZeroTerminate(req->Headers.KnownHeaders[HttpHeaderHost].pRawValue,
										req->Headers.KnownHeaders[HttpHeaderHost].RawValueLength, r->pool);
	}

	int port = 0;
	char *port_str = NULL;

	if(r->hostname != NULL)
	{
		int k = 0;
		char *ptr = (char *)r->hostname;

		while(*ptr != 0 && *ptr != ':')
			ptr++;

		if(*ptr == ':')
		{
			*ptr = 0;
			port_str = ptr + 1;
			port = atoi(port_str);
		}
	}

	if(req->CookedUrl.pQueryString != NULL && req->CookedUrl.QueryStringLength > 0)
		r->args = ConvertUTF16ToUTF8(req->CookedUrl.pQueryString + 1, (req->CookedUrl.QueryStringLength / sizeof(WCHAR)) - 1, r->pool);

#define _TRANSHEADER(id,str) if(req->Headers.KnownHeaders[id].pRawValue != NULL) \
	{\
		apr_table_setn(r->headers_in, str, \
			ZeroTerminate(req->Headers.KnownHeaders[id].pRawValue, req->Headers.KnownHeaders[id].RawValueLength, r->pool)); \
	}

    _TRANSHEADER(HttpHeaderCacheControl, "Cache-Control");
    _TRANSHEADER(HttpHeaderConnection, "Connection");
    _TRANSHEADER(HttpHeaderDate, "Date");
    _TRANSHEADER(HttpHeaderKeepAlive, "Keep-Alive");             
    _TRANSHEADER(HttpHeaderPragma, "Pragma");                
    _TRANSHEADER(HttpHeaderTrailer, "Trailer");               
    _TRANSHEADER(HttpHeaderTransferEncoding, "Transfer-Encoding");      
    _TRANSHEADER(HttpHeaderUpgrade, "Upgrade");               
    _TRANSHEADER(HttpHeaderVia, "Via");                   
    _TRANSHEADER(HttpHeaderWarning, "Warning");               
    _TRANSHEADER(HttpHeaderAllow, "Allow");                 
    _TRANSHEADER(HttpHeaderContentLength, "Content-Length");         
    _TRANSHEADER(HttpHeaderContentType, "Content-Type");           
    _TRANSHEADER(HttpHeaderContentEncoding, "Content-Encoding");       
    _TRANSHEADER(HttpHeaderContentLanguage, "Content-Language");       
    _TRANSHEADER(HttpHeaderContentLocation, "Content-Location");       
    _TRANSHEADER(HttpHeaderContentMd5, "Content-Md5");            
    _TRANSHEADER(HttpHeaderContentRange, "Content-Range");          
    _TRANSHEADER(HttpHeaderExpires, "Expires");               
    _TRANSHEADER(HttpHeaderLastModified, "Last-Modified");          
    _TRANSHEADER(HttpHeaderAccept, "Accept");                
    _TRANSHEADER(HttpHeaderAcceptCharset, "Accept-Charset");        
    _TRANSHEADER(HttpHeaderAcceptEncoding, "Accept-Encoding");        
    _TRANSHEADER(HttpHeaderAcceptLanguage, "Accept-Language");        
    _TRANSHEADER(HttpHeaderAuthorization, "Authorization");         
    _TRANSHEADER(HttpHeaderCookie, "Cookie");                
    _TRANSHEADER(HttpHeaderExpect, "Expect");                
    _TRANSHEADER(HttpHeaderFrom, "From");                  
    _TRANSHEADER(HttpHeaderHost, "Host");                  
    _TRANSHEADER(HttpHeaderIfMatch, "If-Match");               
    _TRANSHEADER(HttpHeaderIfModifiedSince, "If-Modified-Since");       
    _TRANSHEADER(HttpHeaderIfNoneMatch, "If-None-Match");           
    _TRANSHEADER(HttpHeaderIfRange, "If-Range");               
    _TRANSHEADER(HttpHeaderIfUnmodifiedSince, "If-Unmodified-Since");     
    _TRANSHEADER(HttpHeaderMaxForwards, "Max-Forwards");           
    _TRANSHEADER(HttpHeaderProxyAuthorization, "Proxy-Authorization");    
    _TRANSHEADER(HttpHeaderReferer, "Referer");               
    _TRANSHEADER(HttpHeaderRange, "Range");                 
    _TRANSHEADER(HttpHeaderTe, "TE");                    
    _TRANSHEADER(HttpHeaderTranslate, "Translate");             
    _TRANSHEADER(HttpHeaderUserAgent, "User-Agent");

#undef _TRANSHEADER

	for(int i = 0; i < req->Headers.UnknownHeaderCount; i++)
	{
		apr_table_setn(r->headers_in, 
			ZeroTerminate(req->Headers.pUnknownHeaders[i].pName, req->Headers.pUnknownHeaders[i].NameLength, r->pool), 
			ZeroTerminate(req->Headers.pUnknownHeaders[i].pRawValue, req->Headers.pUnknownHeaders[i].RawValueLength, r->pool));
	}

	r->content_encoding = apr_table_get(r->headers_in, "Content-Encoding");
	r->content_type = apr_table_get(r->headers_in, "Content-Type");

	const char *lng = apr_table_get(r->headers_in, "Content-Languages");

	if(lng != NULL)
	{
		r->content_languages = apr_array_make(r->pool, 1, sizeof(const char *));

		*(const char **)apr_array_push(r->content_languages) = lng;
	}

	switch(req->Verb)
	{
	case HttpVerbUnparsed:
	case HttpVerbUnknown:
	case HttpVerbInvalid:
    case HttpVerbTRACK:  // used by Microsoft Cluster Server for a non-logged trace
    case HttpVerbSEARCH:
	default:
		r->method = "INVALID";
		r->method_number = M_INVALID;
		break;
	case HttpVerbOPTIONS:
		r->method = "OPTIONS";
		r->method_number = M_OPTIONS;
		break;
	case HttpVerbGET:
	case HttpVerbHEAD:
		r->method = "GET";
		r->method_number = M_GET;
		break;
	case HttpVerbPOST:
		r->method = "POST";
		r->method_number = M_POST;
		break;
    case HttpVerbPUT:
		r->method = "PUT";
		r->method_number = M_PUT;
		break;
    case HttpVerbDELETE:
		r->method = "DELETE";
		r->method_number = M_DELETE;
		break;
    case HttpVerbTRACE:
		r->method = "TRACE";
		r->method_number = M_TRACE;
		break;
    case HttpVerbCONNECT:
		r->method = "CONNECT";
		r->method_number = M_CONNECT;
		break;
    case HttpVerbMOVE:
		r->method = "MOVE";
		r->method_number = M_MOVE;
		break;
    case HttpVerbCOPY:
		r->method = "COPY";
		r->method_number = M_COPY;
		break;
    case HttpVerbPROPFIND:
		r->method = "PROPFIND";
		r->method_number = M_PROPFIND;
		break;
    case HttpVerbPROPPATCH:
		r->method = "PROPPATCH";
		r->method_number = M_PROPPATCH;
		break;
    case HttpVerbMKCOL:
		r->method = "MKCOL";
		r->method_number = M_MKCOL;
		break;
    case HttpVerbLOCK:
		r->method = "LOCK";
		r->method_number = M_LOCK;
		break;
    case HttpVerbUNLOCK:
		r->method = "UNLOCK";
		r->method_number = M_UNLOCK;
		break;
	}

	if(HTTP_EQUAL_VERSION(req->Version, 0, 9))
		r->protocol = "HTTP/0.9";
	else if(HTTP_EQUAL_VERSION(req->Version, 1, 0))
		r->protocol = "HTTP/1.0";
	else
		r->protocol = "HTTP/1.1";

	r->request_time = apr_time_now();

	r->parsed_uri.scheme = "http";
	r->parsed_uri.path = r->path_info;
	r->parsed_uri.hostname = (char *)r->hostname;
	r->parsed_uri.is_initialized = 1;
	r->parsed_uri.port = port;
	r->parsed_uri.port_str = port_str;
	r->parsed_uri.query = r->args;
	r->parsed_uri.dns_looked_up = 0;
	r->parsed_uri.dns_resolved = 0;
	r->parsed_uri.password = NULL;
	r->parsed_uri.user = NULL;
	r->parsed_uri.fragment = NULL;

	r->unparsed_uri = ZeroTerminate(req->pRawUrl, req->RawUrlLength, r->pool);
	r->uri = r->unparsed_uri;

	r->the_request = (char *)apr_palloc(r->pool, strlen(r->method) + 1 + req->RawUrlLength + 1 + strlen(r->protocol) + 1);

	strcpy(r->the_request, r->method);
	strcat(r->the_request, " ");
	strcat(r->the_request, r->uri);
	strcat(r->the_request, " ");
	strcat(r->the_request, r->protocol);

	HTTP_REQUEST_ID httpRequestID;
	char *pszValue = (char *)apr_palloc(r->pool, 24);

	httpRequestID = pRequest->GetRawHttpRequest()->RequestId;

	_ui64toa(httpRequestID, pszValue, 10);

	apr_table_setn(r->subprocess_env, "UNIQUE_ID", pszValue);

	PSOCKADDR pAddr = pRequest->GetRemoteAddress();

#if AP_SERVER_MAJORVERSION_NUMBER > 1 && AP_SERVER_MINORVERSION_NUMBER < 3
    c->remote_addr = CopySockAddr(r->pool, pAddr);
    c->remote_ip = GetIpAddr(r->pool, pAddr);
#else
    c->client_addr = CopySockAddr(r->pool, pAddr);
	c->client_ip = GetIpAddr(r->pool, pAddr);
#endif
	c->remote_host = NULL;

	int status = modsecProcessRequest(r);

	if(status != DECLINED)
	{
		pHttpContext->GetResponse()->SetStatus(status, "ModSecurity Action");
		pHttpContext->SetRequestHandled();

		hr = E_FAIL;
		goto Finished;
	}

Finished:
	LeaveCriticalSection(&m_csLock);

    if ( FAILED( hr )  )
    {
        return RQ_NOTIFICATION_FINISH_REQUEST;
    }
	return RQ_NOTIFICATION_CONTINUE;
}