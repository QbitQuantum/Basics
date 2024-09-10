void DisplayOLEDBErrorRecords(HRESULT hrErr = S_OK)
{
	CDBErrorInfo ErrorInfo;
	ULONG        cRecords;
	HRESULT      hr;
	ULONG        i;
	CComBSTR     bstrDesc, bstrHelpFile, bstrSource;
	GUID         guid;
	DWORD        dwHelpContext;
	WCHAR        wszGuid[40];
	USES_CONVERSION;

  TCERRLOG_BEGIN_SIZE(_MAX_PATH * 8);

	// If the user passed in an HRESULT then trace it
	if (hrErr != S_OK)
  {
		TCERRLOG_PART1("OLE DB Error Record dump for hr = 0x%x\n", hrErr);
  }

	LCID lcLocale = GetSystemDefaultLCID();

	hr = ErrorInfo.GetErrorRecords(&cRecords);
	if (FAILED(hr) && ErrorInfo.m_spErrorInfo == NULL)
	{
		TCERRLOG_PART1("No OLE DB Error Information found: hr = 0x%x\n", hr);
	}
	else
	{
		for (i = 0; i < cRecords; i++)
		{
			hr = ErrorInfo.GetAllErrorInfo(i, lcLocale, &bstrDesc, &bstrSource, &guid,
										&dwHelpContext, &bstrHelpFile);
			if (FAILED(hr))
			{
				TCERRLOG_PART1("OLE DB Error Record dump retrieval failed: hr = 0x%x\n", hr );
				return;
			}
			StringFromGUID2(guid, wszGuid, sizeof(wszGuid) / sizeof(WCHAR));
			TCERRLOG_PART5(
				"Source:\"%ls\"\nDescription:\"%ls\"\nHelp File:\"%ls\"\nHelp Context:%4d\nGUID:%ls\n",
				bstrSource, bstrDesc, bstrHelpFile, dwHelpContext, wszGuid);
			bstrSource.Empty();
			bstrDesc.Empty();
			bstrHelpFile.Empty();
		}
	}
  TCERRLOG_END
}