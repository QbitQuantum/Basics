void CWinHTTPUtil::StatusHeadersAvailable()
{
	DWORD size = sizeof(DWORD);

	//HTTPのステータスコード確認
	WinHttpQueryHeaders( this->request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &this->responseStatusCode, &size, NULL );

	//レスポンスヘッダを全部取得
	WinHttpQueryHeaders( this->request, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &size, WINHTTP_NO_HEADER_INDEX);
	WCHAR* rawHeader = new WCHAR[size/sizeof(WCHAR) + 1];
	ZeroMemory(rawHeader, sizeof(WCHAR) * (size/sizeof(WCHAR) + 1));
	if( WinHttpQueryHeaders( this->request, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, rawHeader, &size, WINHTTP_NO_HEADER_INDEX) == TRUE ){
		this->responseHTTPHeader = rawHeader;
	}else{
		this->responseHTTPHeader = L"";
	}
	SAFE_DELETE_ARRAY(rawHeader)

	//ContentLengthを取得してみる
	DWORD fileLength = 0;
	size = sizeof(DWORD);
	if( WinHttpQueryHeaders( this->request, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER , NULL, &fileLength, &size, NULL ) == TRUE ){
		this->responseContentSize = fileLength;
	}else{
		this->responseContentSize = 0;
	}

	if( this->responseStatusCode == 200 || this->responseStatusCode == 201){
		//サイズ０のファイル作成
		if( this->saveFilePath.size() > 0 ){
			HANDLE file = CreateFile( this->saveFilePath.c_str(), GENERIC_READ|GENERIC_WRITE , FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
			if( file != INVALID_HANDLE_VALUE){
				CloseHandle(file);
			}
		}
	}else{
		this->errEndCode = ERR_NW_FALSE;
	}

	WinHttpQueryDataAvailable( this->request, NULL);

}