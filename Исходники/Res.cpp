bool CRes::PackFiles(CStringArray& FilesList, CString PackName /* = _T */)
{
	RESHEADER Header; ZeroMemory(&Header, RHSize);
	CFile File, tmpFile;
	DWORD dwFilesCount = FilesList.GetCount();
	DWORD dwTableSize = dwFilesCount * RESize, dwFreeOffset = RHSize;
	unique_ptr<BYTE[]> upTable(new BYTE[dwTableSize]);
	auto pTable = upTable.get();

	memmove_s(Header.Header, 3, "PRF", 3);
	Header.FilesCount = dwFilesCount;
	Header.TableSize = dwTableSize;
	File.Open(PackName, CFile::modeCreate|CFile::modeReadWrite);
	File.Write(&Header, RHSize);

	for (DWORD i = 0; i < dwFilesCount; i++)
	{
		CString FileName;
		unique_ptr<BYTE> upBuffer, upzBuffer;
		RESENTRY Table; ZeroMemory(&Table, RESize);

		tmpFile.Open(FilesList[i], CFile::modeRead);
		DWORD dwFileSize = tmpFile.GetLength();
		upBuffer = unique_ptr<BYTE>(new BYTE[dwFileSize+1]);
		auto pBuffer = upBuffer.get();

		tmpFile.Read(pBuffer, dwFileSize);
		DWORD dwzFileSize = compressBound(dwFileSize);
		upzBuffer = unique_ptr<BYTE>(new BYTE[dwzFileSize]);
		auto pzBuffer = upzBuffer.get();
		compress(pzBuffer, &dwzFileSize, pBuffer, dwFileSize);
		File.Write(pzBuffer, dwzFileSize);
		tmpFile.Close();

		FileName = GetName(FilesList[i]);
		size_t iRet = 0;
		wcstombs_s(&iRet, Table.ResName, 32, FileName, FileName.GetLength());
		Table.ResOffset = dwFreeOffset;
		Table.ResSize = dwFileSize;
		Table.zResSize = dwzFileSize;
		dwFreeOffset += dwzFileSize;
		memmove_s(pTable, dwTableSize, &Table, RESize);
		pTable += RESize;
	}

	Header.TableOffset = dwFreeOffset;
	File.Write(upTable.get(), dwTableSize);
	File.SeekToBegin();
	File.Write(&Header, RHSize);
	File.Close();
	return true;
}