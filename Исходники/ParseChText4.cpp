BOOL CParseChText4::SaveChText(LPCWSTR filePath)
{
	wstring loadFilePath = L"";
	if( filePath == NULL ){
		loadFilePath = this->filePath;
	}else{
		loadFilePath = filePath;
	}

	if( loadFilePath.size() == 0 ){
		return FALSE;
	}

/*
	std::wregex re(L".+\\(.+)\(.+\)\.ChSet4\.txt$");
	
	
	std::wstring text(str);
	std::wsmatch m;

	if( std::regex_search(text, m, re) ) this->mpStartTimeShifting = m[1];
*/



	HANDLE hFile = _CreateFile2( loadFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE ){
		return FALSE;
	}

	multimap<LONGLONG, CH_DATA4> sortList;
	multimap<LONGLONG, CH_DATA4>::iterator itr;
	for( itr = this->chList.begin(); itr != this->chList.end(); itr++ ){
		LONGLONG Key = ((LONGLONG)itr->second.space)<<32 | ((LONGLONG)itr->second.ch)<<16 | (LONGLONG)itr->second.serviceID;
		sortList.insert(pair<LONGLONG, CH_DATA4>(Key, itr->second));
	}

	for( itr = sortList.begin(); itr != sortList.end(); itr++ ){
		string chName="";
		WtoA(itr->second.chName, chName);
		string serviceName="";
		WtoA(itr->second.serviceName, serviceName);
		string networkName="";
		WtoA(itr->second.networkName, networkName);

		string strBuff;
		Format(strBuff, "%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n",
			chName.c_str(),
			serviceName.c_str(),
			networkName.c_str(),
			itr->second.space,
			itr->second.ch,
			itr->second.originalNetworkID,
			itr->second.transportStreamID,
			itr->second.serviceID,
			itr->second.serviceType,
			itr->second.partialFlag,
			itr->second.useViewFlag,
			itr->second.remoconID
			);
		DWORD dwWrite = 0;
		WriteFile(hFile, strBuff.c_str(), (DWORD)strBuff.length(), &dwWrite, NULL);
	}

	CloseHandle(hFile);
	return TRUE;
}