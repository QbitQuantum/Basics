HRESULT GRF_File::Load(LPCWSTR fileName)
{
	HRESULT  hr   = S_OK;
	STATSTG  rGrfStat;
	CComPtr<IStorage> pGrfFile;
	CComPtr<IStream> pGrfData;

	Clear();

	TRACE(trace_open(NULL,zFalse));

	TRACE(trace(TEXT("*** StgOpenStorage(L\"%") TRACEWSTR TEXT("\")...\n"), fileName));
	if(S_OK != (hr = StgOpenStorage(fileName,NULL,STGM_DIRECT|STGM_READ|STGM_SHARE_DENY_WRITE,NULL,DWRESERVED,&pGrfFile))) 
		return hr;

	TRACE(trace(TEXT("*** OpenStream(L\"ActiveMovieGraph\")...\n")));
	if(S_OK != (hr = pGrfFile->OpenStream(L"ActiveMovieGraph",LPRESERVED,STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE,DWRESERVED,&pGrfData))) 
		return hr;

	TRACE(trace(TEXT("*** Stat()...\n")));
	if(S_OK != (hr = pGrfData->Stat(&rGrfStat,STATFLAG_NONAME))) 
		return hr;

	int cb = (int)rGrfStat.cbSize.QuadPart;
	TRACE(trace(TEXT("*** new BYTE[%d]...\n"),cb));

	const int EXTRA = 32 * sizeof(WCHAR);		// add safety margin to end of buffer
	CStringA data('\0', cb + EXTRA);

	char* const pb  = data.GetBufferSetLength(cb + EXTRA);
	if	(!pb)		
		return E_POINTER;

	TRACE(trace(TEXT("*** Read(%d)...\n"),cb));
	if(S_OK != (hr = pGrfData->Read(pb,(ULONG)cb,NULL))) 
		return hr;

	LPCWSTR p = (LPCWSTR)pb;
	LPCWSTR s1 = p, s2 = p;
	const LPCWSTR end = p + 1 + (cb/sizeof(WCHAR));	// round up to next WCHAR after cb bytes

	p = token(p,end,&s1,&s2);
	if (p >= end)
		return E_NOT_SUFFICIENT_BUFFER;
	TRACE(trace(TEXT(">>> version = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));

	const long format_version = wcstol(s1, NULL, 10);
	ASSERT(format_version == 3);

	p = token(p,end,&s1,&s2);
	if (p >= end)
		return E_NOT_SUFFICIENT_BUFFER;
	if(0 == wcsnicmp(s1,L"FILTERS",s2-s1)) {

		int filter_index = 1;
		TRACE(trace(TEXT(">>> FILTERS\n")));
		while (p < end) {

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			if(0 == wcsnicmp(s1,L"CONNECTIONS",s2-s1)) 
				break;

			GRF_Filter grf_filter;

			TRACE(trace(TEXT(">>>   %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));
			grf_filter.index = wcstol(s1, NULL, 10);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     name .... = L\"%.*") TRACEWSTR TEXT("\"\n"), (INT) (s2 - s1), s1));
			grf_filter.name = CString(s1, (int) (s2-s1));

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     class_id  = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));

			GUID clsid = {0};
			const CString clsid_str(s1, (int) (s2-s1));
			hr = CLSIDFromString(clsid_str, &grf_filter.clsid);

			// TODO is it possible for filter to be both source and sink?
			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			const bool source_file = 0 == wcsnicmp(s1,L"SOURCE",s2-s1);
			const bool sink_file = 0 == wcsnicmp(s1,L"SINK",s2-s1);
			if (source_file || sink_file) {
				TRACE(trace(TEXT(">>>     file .... = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));

				p = token(p,end,&s1,&s2);
				if (p >= end)
					return E_NOT_SUFFICIENT_BUFFER;
				TRACE(trace(TEXT(">>>     file_name = L\"%.*") TRACEWSTR TEXT("\"\n"), (INT) (s2 - s1), s1));

				CStringW filename = CString(s1, (int) (s2-s1));

				if (source_file) {
					grf_filter.source_filename = filename;
				} else {
					grf_filter.sink_filename = filename;
				}
				p = token(p,end,&s1,&s2);
				if (p >= end)
					return E_NOT_SUFFICIENT_BUFFER;
			}

			TRACE(trace(TEXT(">>>     length .. = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));

			int filter_data_length = 0;
			const char* filter_data = (const char*)(p + 1);
			if(S_OK != (hr = skip(s1, &p, filter_data_length))) 
				return hr;
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;

			grf_filter.ipersiststream_data = CStringA(filter_data, filter_data_length);
			ASSERT(filter_data_length == grf_filter.ipersiststream_data.GetLength());

			grf_filters.Add(grf_filter);
		}
	}

	if(0 == wcsnicmp(s1,L"CONNECTIONS",s2-s1)) {

		TRACE(trace(TEXT(">>> CONNECTIONS\n")));
		while(p < end) {
			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			if(0 == wcsnicmp(s1,L"CLOCK",s2-s1)) 
				break;
			if(0 == wcsnicmp(s1,L"END",s2-s1)) 
				break;

			GRF_Connection grf_connection;

			TRACE(trace(TEXT(">>>   %.*") TRACEWSTR, (INT) (s2 - s1), s1));
			grf_connection.output_filter_index = wcstol(s1, NULL, 10);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(" [L\"%.*") TRACEWSTR TEXT("\"]"), (INT) (s2 - s1), s1));
			grf_connection.output_pin_id = CString(s1, (int) (s2-s1));

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(" -> %.*") TRACEWSTR, (INT) (s2 - s1), s1));
			grf_connection.input_filter_index = wcstol(s1, NULL, 10);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(" [L\"%.*") TRACEWSTR TEXT("\"]\n"), (INT) (s2 - s1), s1));
			grf_connection.input_pin_id = CString(s1, (int) (s2-s1));

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     sample_size ........ = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));
			grf_connection.flags = wcstol(s1, NULL, 10);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     major_type ......... = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));
			CString guid_str(s1, (int) (s2-s1));
			hr = CLSIDFromString(guid_str, &grf_connection.media_type.majortype);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     subtype ............ = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));
			guid_str = CString(s1, (int) (s2-s1));
			hr = CLSIDFromString(guid_str, &grf_connection.media_type.subtype);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     fixed_sample_size .. = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));
			grf_connection.media_type.bFixedSizeSamples = wcstol(s1, NULL, 10);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     temporal_compression = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));
			grf_connection.media_type.bTemporalCompression = wcstol(s1, NULL, 10);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     length(?) .......... = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));
			grf_connection.media_type.lSampleSize = wcstol(s1, NULL, 10);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     format_type ........ = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));
			guid_str = CString(s1, (int) (s2-s1));
			hr = CLSIDFromString(guid_str, &grf_connection.media_type.formattype);

			p = token(p,end,&s1,&s2);
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;
			TRACE(trace(TEXT(">>>     length ............. = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));

			int format_length = 0;
			BYTE* format_data = (BYTE *)(p + 1);
			if(S_OK != (hr = skip(s1, &p, format_length))) 
				return hr;
			if (p >= end)
				return E_NOT_SUFFICIENT_BUFFER;

			if (format_length > 0)
				grf_connection.media_type.SetFormat(format_data, format_length);

			grf_connections.Add(grf_connection);

			p++; /// where is this L'\0' terminator documented??
		}
	}
	if(0 == wcsnicmp(s1,L"CLOCK",s2-s1)) {
		TRACE(trace(TEXT(">>> CLOCK\n")));

		p = token(p,end,&s1,&s2);
		if (p >= end)
			return E_NOT_SUFFICIENT_BUFFER;
		TRACE(trace(TEXT(">>>   required = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));

		clock_flags = wcstol(s1, NULL, 10);

		p = token(p,end,&s1,&s2);
		if (p >= end)
			return E_NOT_SUFFICIENT_BUFFER;
		TRACE(trace(TEXT(">>>   clock_id = %.*") TRACEWSTR TEXT("\n"), (INT) (s2 - s1), s1));

		clock_index = wcstol(s1, NULL, 10);
	}
	if(0 == wcsnicmp(s1,L"END",s2-s1)) {
		TRACE(trace(TEXT(">>> END\n")));
	}

	TRACE(trace(TEXT("*** hr = ") TRACEHR_STR TEXT("\n"),TRACEHR_REF(hr)));
	TRACE(trace_close());
	return hr;
}