bool LoadOldXMLData(const Category cat, bool update_age) {
	TCHAR xml_data_filename[MAX_PATH];
	TCHAR *ts;
	mir_sntprintf(xml_data_filename, SIZEOF(xml_data_filename), _T("%s\\%s.xml"),
		options.data_folder, (ts = GetTString(category_files[cat])));
	mir_free(ts);

	if(pData[cat]) free(pData[cat]);
	pData[cat] = 0;
	dataLength[cat] = 0;

	// load 
	HANDLE hDataFile = CreateFile(xml_data_filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if(hDataFile != INVALID_HANDLE_VALUE) {
		dataLength[cat] = GetFileSize(hDataFile, 0);
		if(dataLength[cat]) {
			unsigned long bytes_read;
			pData[cat] = (BYTE *)malloc(dataLength[cat]);
			if(ReadFile(hDataFile, pData[cat], dataLength[cat], &bytes_read, 0))
				dataLength[cat] = bytes_read;
			else {
				free(pData[cat]);
				pData[cat] = 0;
				dataLength[cat] = 0;
			}

		}

		if(update_age) {
			FILETIME ft_now;
			SYSTEMTIME now;
			GetSystemTime(&now);
			SystemTimeToFileTime(&now, &ft_now);
			SetFileTime(hDataFile, 0, 0, &ft_now);
		}

		CloseHandle(hDataFile);
	}
	
	if(pData[cat] && dataLength[cat]) {
		doc[cat] = ezxml_parse_str((char*)pData[cat], dataLength[cat]);
		return doc[cat] != NULL;
	}
	return false;
}