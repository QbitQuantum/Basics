bool CConnection::SendRequest(XMLMemoryWriter& xml_memory_writer,Buffer &buffer,IEventListener* event_listener)
{
	CHAR   buffer_tmp[1024];
	DWORD  bytes_read;
	const WCHAR* lplpszAcceptTypes[] = { L"*/*", NULL };
	m_request = HttpOpenRequest(m_connection, L"POST", L"/xml-rpc", NULL, 0, lplpszAcceptTypes, 0, 0);
	if (m_request)
	{
		if (HttpSendRequest(m_request, 0, 0, xml_memory_writer.xml_data, xml_memory_writer.xml_data_size))
		{
			DWORD content_len;
			DWORD content_len_size = sizeof(content_len);
			if (HttpQueryInfo(m_request, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &content_len, &content_len_size, 0))
			{
				if (buffer.Allocate(content_len))
				{
					while (InternetReadFile(m_request, buffer_tmp, sizeof(buffer_tmp), &bytes_read) && bytes_read)
					{
						memcpy(buffer.buffer_in + buffer.buffer_in_total, buffer_tmp, bytes_read);
						buffer.buffer_in_total += bytes_read;
					}
					return true;
				}
				else
					event_listener->OnError(L"failed to allocate memory");
			}
			else
				event_listener->OnError(L"failed to query http info");
		}
		else
			event_listener->OnError(L"failed to send http request");
	    InternetCloseHandle(m_request);
	}
	else
		event_listener->OnError(L"failed creating http request");
	return false;
}