Response * WinHTTPSession::receive(HINTERNET wrequest, const Request & request,
                                   std::basic_string<WCHAR> & redirect) {
	
	
	
	if(!WinHttpReceiveResponse(wrequest, NULL)) {
		return new Response("Error receiving response: " + errorString());
	}
	
	DWORD status = 0;
	DWORD statusSize = sizeof(status);
	
	if(!WinHttpQueryHeaders(wrequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
	                        WINHTTP_HEADER_NAME_BY_INDEX, &status, &statusSize,
	                        WINHTTP_NO_HEADER_INDEX)) {
		return new Response("Error getting status code: " + errorString());
	}
	
	std::string url;
	if(!request.followRedirects()) {
		DWORD urlSize = 0;
		WinHttpQueryHeaders(wrequest, WINHTTP_QUERY_LOCATION, WINHTTP_HEADER_NAME_BY_INDEX,
		                    WINHTTP_NO_OUTPUT_BUFFER, &urlSize, WINHTTP_NO_HEADER_INDEX);
		if(GetLastError() ==  ERROR_INSUFFICIENT_BUFFER && urlSize % sizeof(WCHAR) == 0) {
			platform::WideString redirect;
			redirect.allocate(urlSize / sizeof(WCHAR));
			if(WinHttpQueryHeaders(wrequest, WINHTTP_QUERY_LOCATION, WINHTTP_HEADER_NAME_BY_INDEX,
			                       redirect.data(), &urlSize, WINHTTP_NO_HEADER_INDEX)) {
				redirect.resize(urlSize / sizeof(WCHAR));
				platform::WideString base(request.url());
				platform::WideString wurl;
				wurl.allocate(2 * (base.size() + redirect.size()));
				urlSize = wurl.size();
				if(InternetCombineUrlW(base, redirect, wurl.data(), &urlSize, ICU_BROWSER_MODE)) {
					wurl.resize(urlSize);
					url = wurl.toUTF8();
				}
			}
		}
	} else {
		url = redirect.empty() ? request.url() : platform::WideString::toUTF8(redirect);
	}
	
	std::string data;
	DWORD size;
	for(;;) {
		
		// Check for available data.
		size = 0;
		if(!WinHttpQueryDataAvailable(wrequest, &size)) {
			return new Response("Error reading response: " + errorString());
		}
		if(!size) {
			break;
		}
		
		size_t oldsize = data.size();
		data.resize(oldsize + size);
		
		if(!WinHttpReadData(wrequest, &data[oldsize], size, &size)) {
			return new Response("Error reading response: " + errorString());
		}
		
		data.resize(oldsize + size);
	}
	
	return new Response(status, data, url);
}