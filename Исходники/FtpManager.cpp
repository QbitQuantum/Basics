/**
* ReadLocalDirectory
*
* Description: Read files folders from directory.
*
* Param: con - describes connection information
*        dir - path. 
*		 files - output list
*
* Return: bool - true. False if file does not exist, has not been read.
*/
bool CFtpManager::ReadLocalDirectory(CConnection * con, CString &dir, std::vector<CFileContainer> &files)
{
	bool result = true;
	if(con->host.GetLength() == 0)
	{
		return false;
	}

	if(dir.GetAt( dir.GetLength() - 1 ) != '/')
	{
		dir = dir + CString(_T("/"));
	}

	CString localStorePath;
	GetLocalStorePath(con, localStorePath);

	// Read files and folders in directory.
	localStorePath = localStorePath + CString(dir);
	localStorePath.Replace('/', '\\');
	CString localStoreSearchPath = CString(localStorePath + CString(_T("*.*")));
	/*
	CFileFind finder; 
	BOOL bWorking = finder.FindFile(localStoreSearchPath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDirectory())
		{
			CFileContainer f;
			f.dir = 1;
			f.name = finder.GetFileName(); //  .GetFileTitle();
			f.path = CString(dir); //finder.GetFilePath();
			f.localPath = CString(localStorePath);
			if(f.name.Trim().Compare(_T(".")) != 0 && f.name.Trim().Compare(_T("..")) != 0){
				//files.push_back(f);
			}
		} 
		// else sync local file
	}
	finder.Close();
	*/

	// Read file 
	CString dirContentFile(localStorePath + _T(".files.rftp"));

	//char nameBuffer[100];
	//sprintf(nameBuffer, "%S", dirContentFile); // CString to char *
	
	CFileStatus status;
	if(CFile::GetStatus(dirContentFile, status))
	{
		CStdioFile file (dirContentFile, CStdioFile::modeRead | CFile::shareDenyNone);
		CString buffer;
		//CString string;
		while (file.ReadString(buffer))
		{
			CXml xml;

			CString type(_T(""));
			xml.GetTag(buffer, CString(_T("t")), type);
			bool isDir = false;
			if(type.Compare(_T("d")) == 0){
				isDir = true;
			}
			

			CString fileName(_T(""));
			xml.GetTag(buffer, CString(_T("n")), fileName);

			
			// size
			long size = 0;
			CString fileSize(_T(""));
			if(xml.GetTag(buffer, CString(_T("s")), fileSize)){
				fileSize = fileSize.Trim();
				if(fileSize.GetLength() > 0){
					size = _wtol(fileSize);
				}
			}

			// Date
			CString fileDate(_T(""));
			xml.GetTag(buffer, CString(_T("d")), fileDate);	
			fileDate = fileDate.Trim();
			

			// permissions
			CString filePermissions(_T(""));
			xml.GetTag(buffer, CString(_T("p")), filePermissions);	
			filePermissions = filePermissions.Trim();

			//TRACE1(" line: %s \n", buffer);
			CFileContainer f;
			if(isDir){
				f.dir = 1;
			} else {
				f.dir = 0;
			}
			f.name = fileName; 
			f.path = CString(dir); 
			f.localPath = CString(localStorePath);
			f.size = size;
			f.remoteDate = CString(fileDate);
			f.host = CString(con->host);
			//TRACE1("filePermissions %s \n " , filePermissions);
			f.permissions = CString(filePermissions);
			
			if(f.name.Trim().Compare(_T(".")) != 0 && f.name.Trim().Compare(_T("..")) != 0 ){
				int i = 0;
				files.push_back(f);
			}
		}
	} 
	else 
	{
		// Directory not read.
		//GetFtpDirectory(con, dir, NULL);
		TRACE1(" ReadLocalDirectory not found: %s \n", dir);
		result = false;
	}
	return result;
}