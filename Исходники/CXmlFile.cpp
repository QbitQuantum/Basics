	Bool CXmlFile::ParseFile(const AString& sFile, PVoid pDoc)
	{
		CDiskFile xFile;
		if (!pDoc || !xFile.Open(sFile))
			return false;

		Size_t iSize = (Size_t)(xFile.GetFileSize() + 8);
		Char* pData	 = (Char*)UtilMalloc(iSize);
		CScope::CMallocPtr scope(pData);
		memset(pData, 0, iSize);
		iSize = (Size_t)xFile.Read(pData, xFile.GetFileSize());
		xFile.Close();

		//解析文档
		return ParseDocument(pDoc, pData);
	}