		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		HttpRequest* HttpRequestSystem::MakeRequest(HttpRequest::Type in_type, const std::string& in_url, const std::string& in_body, const CSCore::ParamDictionary& in_headers, const HttpRequest::Delegate& in_delegate, u32 in_timeoutSecs)
		{
			CS_ASSERT(CSCore::Application::Get()->GetTaskScheduler()->IsMainThread() == true, "Http requests can currently only be made on the main thread");
			CS_ASSERT(in_delegate != nullptr, "Cannot make an http request with a null delegate");
			CS_ASSERT(in_url.empty() == false, "Cannot make an http request to a blank url");

			URL_COMPONENTS urlComps;

			//Initialize the URL_COMPONENTS structure.
			ZeroMemory(&urlComps, sizeof(URL_COMPONENTS));
			urlComps.dwStructSize = sizeof(URL_COMPONENTS);

			//Set required component lengths to non-zero so that they are cracked.
			urlComps.dwSchemeLength    = (DWORD)-1;
			urlComps.dwHostNameLength  = (DWORD)-1;
			urlComps.dwUrlPathLength   = (DWORD)-1;
			urlComps.dwExtraInfoLength = (DWORD)-1;

			//Change the URL to wide string
			std::wstring url(WindowsStringUtils::UTF8ToUTF16(in_url));

			//Crack the URL.
			if (!WinHttpCrackUrl(url.c_str(), (DWORD)url.length(), 0, &urlComps))
			{
				CS_LOG_FATAL("Cannot crack URL: " + in_url);
				return nullptr;
			}

			//Weirdly the cracked URL struct only gives you the ability to crack your own URL
			std::wstring hostName = urlComps.lpszHostName;
			hostName = hostName.substr(0, urlComps.dwHostNameLength);
			HINTERNET connectionHandle = ::WinHttpConnect(m_sessionHandle, hostName.c_str(), INTERNET_DEFAULT_PORT, 0);

			if (!connectionHandle)
			{
				CS_LOG_ERROR("Failed to connect to server: " + in_url);
				return nullptr;
			}

			//Set up the request based on whether it is POST or GET and whether it is SSL
			LPCWSTR type = (in_type == CSNetworking::HttpRequest::Type::k_get ? L"GET" : L"POST");
			HINTERNET requestHandle = 0;

			std::wstring urlPath = urlComps.lpszUrlPath;
			urlPath = urlPath.substr(0, urlComps.dwUrlPathLength);

			if (urlComps.nScheme == INTERNET_SCHEME_HTTPS)
			{
				requestHandle = ::WinHttpOpenRequest(connectionHandle, type, urlPath.c_str(), L"HTTP/1.1", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
				if (requestHandle == nullptr || ApplySSLSettings(requestHandle) == false)
				{
					CS_LOG_ERROR("Failed to open request: " + in_url);
					WinHttpCloseHandle(connectionHandle);
					return nullptr;
				}
			}
			else
			{
				requestHandle = ::WinHttpOpenRequest(connectionHandle, type, urlPath.c_str(), L"HTTP/1.1", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
				if (requestHandle == nullptr)
				{
					CS_LOG_ERROR("Failed to open request: " + in_url);
					WinHttpCloseHandle(connectionHandle);
					return nullptr;
				}
			}

			if (in_headers.empty() == false)
			{
				std::wstring headerBlob = ConvertHeaders(in_headers);

				if (WinHttpAddRequestHeaders(requestHandle, headerBlob.c_str(), DWORD(headerBlob.length()), WINHTTP_ADDREQ_FLAG_ADD) == false)
				{
					CS_LOG_ERROR("Failed to add http headers: " + in_url);
					WinHttpCloseHandle(requestHandle);
					WinHttpCloseHandle(connectionHandle);
					return nullptr;
				}
			}

			HttpRequest* httpRequest = new HttpRequest(in_type, in_url, in_body, in_headers, in_timeoutSecs, requestHandle, connectionHandle, GetMaxBufferSize(), in_delegate);
			m_requests.push_back(httpRequest);
			return httpRequest;
		}