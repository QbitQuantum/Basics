bool 
GetFileCount(
	const LPCWSTR& in_lpszPathW, 
	DWORD& io_iCount,
	std::vector<std::wstring>& io_VecFiles,
	std::list<std::wstring>&   in_SkippedExtensions,
	const bool in_bDontRecurse = false)
{
	_ASSERT(in_lpszPathW);

	std::wstring strPathW(in_lpszPathW);
	
	_ASSERT( strPathW.length() );

	if(!PathIsDirectoryW(in_lpszPathW)) return false;

	if( strPathW.length())
	{
		if( strPathW[ strPathW.length() - 1 ] == L'\\' )
		{
			strPathW += L"*.*";
		}
		else
		{
			strPathW += L"\\*.*";
		}
	}
	
	TRACEW2(L"Doing a findfile on [%s] count is [%d]\n", strPathW.c_str(), io_iCount);

	WIN32_FIND_DATAW fileData={0};	
	
	//The first handle returns a valid file handle which is not the case with CFileFind::FindFile() 
	HANDLE hFind = FindFirstFileW(strPathW.c_str(), &fileData);

	if(hFind != INVALID_HANDLE_VALUE)
	{
		BOOL bWorking = true;
		std::wstring filePath = ExtractDirectoryW(strPathW);
		while(bWorking)
		{
			const std::wstring fileName(fileData.cFileName);

			if( ( (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && IsDots(fileName) ) || (fileData.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
			{
				bWorking = FindNextFileW(hFind, &fileData);
				continue;
			}

			if(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(!in_bDontRecurse)
				{
					TRACEW2(L"Doing a recursive GetFileCount on [%s] count is [%d]\n", fileData.cFileName, io_iCount);
					GetFileCount( (filePath + fileName).c_str(), io_iCount, io_VecFiles, in_SkippedExtensions);
				}
				else
				{
					TRACE0("Not doing a recurse, in_bDontRecurse is true");
				}
			}
			else
			{
				if(in_SkippedExtensions.size())
				{
					// There's something in the list
					// Look for the current extension in the list, if it's there do not increment the counter

					const std::wstring extension (getExtensionW(fileName).c_str());

					TRACEW2(L"Gonna look for extension [%s] of file [%s] in the list of excluded extension\n", extension.c_str(), fileName.c_str());
					
					std::list<std::wstring>::const_iterator i = std::find(in_SkippedExtensions.begin(), in_SkippedExtensions.end(), extension);

					if(i == in_SkippedExtensions.end()) // extension not in list
					{
						io_VecFiles.push_back(filePath + fileName);
						++io_iCount;
					}
					else
					{
						TRACEW1(L"Skipped file [%s], it matched a skipped extension\n", fileName.c_str());
					}
				}
				else
				{
					io_VecFiles.push_back(filePath + fileName);
					++io_iCount;
				}
			}			
			bWorking = FindNextFileW(hFind,&fileData);
		}
		FindClose(hFind);
	}

	return true;
}