PXMLTag CXMLParser::ParseFile(const std::wstring& a_filePath)
{
	std::string l_buf;
	FILE *fFile = NULL;

	if(_wfopen_s(&fFile, a_filePath.c_str(), L"r") != 0)
	{
		throw CXMLException("Unable to open file.", 0);
	}

	while(!feof(fFile))
	{
		char szBuf[4096] = {0};
		size_t l_read = fread_s(szBuf, 4096, sizeof(char), 4096, fFile);

		l_buf.append(szBuf, l_read);
	}

	fclose(fFile);

	return ParseString(l_buf);
}