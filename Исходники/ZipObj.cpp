bool CZipObj::ZipFile(CString strSrcPath, CString strDstPath, CString strExtName /*= _T(".zip")*/)
{
	USES_CONVERSION;
	//	CString modelName = strSrcPath.Right(strSrcPath.GetLength() - strSrcPath.ReverseFind('\\') - 1);
	CString zipName = strDstPath + strExtName;
	std::string strUtf8ZipName = CMyCodeConvert::Gb2312ToUtf8(T2A(zipName));

	try
	{
		Poco::File p(strUtf8ZipName);	//T2A(zipName)
		if (p.exists())
			p.remove(true);
	}
	catch (Poco::Exception)
	{
	}

	//	std::string strModelPath = T2A(strSrcPath);
	std::string strUtf8ModelPath = CMyCodeConvert::Gb2312ToUtf8(T2A(strSrcPath));
	try
	{
		Poco::File p2(strUtf8ModelPath);	//T2A(zipName)
		if (!p2.exists())
		{
			std::string strErr = Poco::format("需要压缩的原文件夹(%s)不存在。", T2A(strSrcPath));
			RecordLog(strErr);
			return false;
		}
	}
	catch (Poco::Exception)
	{
	}

	HZIP hz = CreateZip(zipName, _strPwd.c_str());

	Poco::DirectoryIterator it(strUtf8ModelPath);	//strModelPath
	Poco::DirectoryIterator end;
	while (it != end)
	{
		Poco::Path p(it->path());
		//		std::string strZipFileName = p.getFileName();
		std::string strPath = CMyCodeConvert::Utf8ToGb2312(p.toString());
		std::string strZipFileName = CMyCodeConvert::Utf8ToGb2312(p.getFileName());
		CString strZipPath = A2T(strPath.c_str());
		CString strName = A2T(strZipFileName.c_str());
		//		ZipAdd(hz, A2T(strZipFileName.c_str()), A2T(p.toString().c_str()));
		ZipAdd(hz, strName, strZipPath);
		it++;
	}
	CloseZip(hz);

	return true;
}