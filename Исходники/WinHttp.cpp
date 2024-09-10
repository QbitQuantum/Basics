StringA WinHttpStream::getReplyHeaders()
{
	setState(stReadResponse);
	AutoArray<char> buffer;
	buffer.resize(1000);
	DWORD size = (DWORD)buffer.length();
	while (!HttpQueryInfoA(hHTTPConn,HTTP_QUERY_RAW_HEADERS_CRLF,
		buffer.data(),&size,0)) {
			DWORD res = GetLastError();
			if (res == ERROR_INSUFFICIENT_BUFFER) {
				buffer.resize(size);
			} else {
				throw ErrNoWithDescException(THISLOCATION,GetLastError(),
					"Cannot retrieve headers from the request");
			}
	}
	buffer.resize(size);
	return buffer;
}