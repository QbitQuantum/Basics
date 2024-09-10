void web_file::OnHeadersReady( HINTERNET hRequest )
{
	WCHAR buf[2048];
	DWORD len = sizeof(buf);
	if (WinHttpQueryOption(m_hRequest, WINHTTP_OPTION_URL, buf, &len))
	{
		m_realUrl = buf;
	}
}