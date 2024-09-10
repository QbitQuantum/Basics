NetworkClient::NetworkClient(void)
{
    #ifndef IU_CLI
	_mutex.acquire();
#endif
	if(!_curl_init)
	{
		enableResponseCodeChecking_ = true;
		curl_global_init(CURL_GLOBAL_ALL);
		curl_version_info_data * infoData = curl_version_info(CURLVERSION_NOW);
		_is_openssl =  strstr(infoData->ssl_version, "WinSSL")!=infoData->ssl_version;
#ifdef WIN32
		GetModuleFileNameA(0, CertFileName, 1023);
		int i, len = lstrlenA(CertFileName);
		for(i=len; i>=0; i--)
		{
            if(CertFileName[i] == '\\') {
				CertFileName[i+1] = 0;
				break;
			}
		}
        strcat(CertFileName, "curl-ca-bundle.crt");
#endif
		atexit(&curl_cleanup);
		_curl_init = true;
	}
    #ifndef IU_CLI
	_mutex.release();
#endif
	m_hOutFile = 0;
	chunkOffset_ = -1;
	chunkSize_ = -1;
	chunk_ = 0;
	m_CurrentFileSize = -1;
	m_uploadingFile = NULL;
	*m_errorBuffer = 0;
	m_progressCallbackFunc = NULL;
	curl_handle = curl_easy_init(); // Initializing libcurl
	m_bodyFuncData.funcType = funcTypeBody;
	m_bodyFuncData.nmanager = this;
	m_UploadBufferSize = 65536;
	m_headerFuncData.funcType = funcTypeHeader;
	m_headerFuncData.nmanager = this;
	m_nUploadDataOffset = 0;
	treatErrorsAsWarnings_ = false;
	curl_easy_setopt(curl_handle, CURLOPT_COOKIELIST, "");
	setUserAgent("Mozilla/5.0");

	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, private_static_writer);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &m_bodyFuncData);	
	curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, &m_headerFuncData);
	curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, m_errorBuffer);
	
	curl_easy_setopt(curl_handle, CURLOPT_PROGRESSFUNCTION, &ProgressFunc);
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(curl_handle, CURLOPT_PROGRESSDATA, this);
        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl_handle, CURLOPT_ENCODING, "");
	curl_easy_setopt(curl_handle, CURLOPT_SOCKOPTFUNCTION, &set_sockopts);
	curl_easy_setopt(curl_handle, CURLOPT_SOCKOPTDATA, this);
	 
#ifdef _WIN32
	curl_easy_setopt(curl_handle, CURLOPT_CAINFO, CertFileName);
#endif
	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 1L); 
	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 2L);
	//curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L); 
	//curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0L);

	//We want the referrer field set automatically when following locations
	curl_easy_setopt(curl_handle, CURLOPT_AUTOREFERER, 1L); 
	curl_easy_setopt(curl_handle, CURLOPT_BUFFERSIZE, 32768L);
	   curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
}