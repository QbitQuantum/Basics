wstring CWaveSession::ExtractChannelResponse(wstring szResponse)
{
	if (!szResponse.empty())
	{
		DWORD dwPos = szResponse.find(L'\n');

		if (dwPos != wstring::npos && dwPos > 0)
		{
			DWORD dwLength = _wtol(szResponse.substr(0, dwPos).c_str());

			if (szResponse.length() >= dwPos + 1 + dwLength)
			{
				return szResponse.substr(dwPos + 1, dwLength);
			}
		}
	}

	return L"";
}