char *PakReader::extractFileIntoMemory(std::wstring fileName, std::string& filePath, std::wstring& destination, bool preservePath, unsigned long *fileSize) {
	if (fileSize == 0) {
		return 0;
	}
	HEADER_PAK_FILEINFO_LSPK *info = getHeaderForFileLspk(filePath);
	if (info != 0) {
		boost::filesystem::ifstream input(getFileNameByPakNumber(fileName, info->pakNumber).c_str(), std::ios_base::binary);
		long fileStart = dataOffsetToAbsolute(info->dataSectionOffset, info->pakNumber);
		input.seekg(fileStart);
		char *alloc = new char[info->fileSize];
		input.read(alloc, info->fileSize);
		if (!input) {
			delete []alloc;
			input.close();
			return 0;
		}
		long cwdSize = 1024;
		wchar_t cwd[cwdSize];
		_wgetcwd(cwd, cwdSize);
		std::wstringstream ss;
		if (!preservePath) {
			long fileNameSize = strlen(info->fileName) + 1;
			std::wstring extractFileName;
			{
				wchar_t alloc[fileNameSize];
				mbstowcs(alloc, info->fileName, fileNameSize);
				extractFileName = alloc;
			}
			long lastPathDelimiter = extractFileName.find_last_of(L'/');
			if (lastPathDelimiter == std::string::npos) {
				ss<<destination<<(destination[destination.size() - 1] == L'/' ? L"" : L"/")<<extractFileName;
			}
			else {
				ss<<destination<<(destination[destination.size() - 1] == L'/' ? L"" : L"/")<<extractFileName.substr(lastPathDelimiter + 1);
			}
		} else {
			boost::char_separator<wchar_t> sep(L"\\/");
			typedef boost::tokenizer<boost::char_separator<wchar_t> , std::wstring::const_iterator, std::wstring> PathTokenizer;
			long fileNameSize = strlen(info->fileName) + 1;
			std::wstring name;
			{
				wchar_t alloc[fileNameSize];
				mbstowcs(alloc, info->fileName, fileNameSize);
				name = alloc;
			}
			PathTokenizer tok(name, sep);
			std::wstring lastToken = L"";
			_wchdir(destination.c_str());
			ss<<destination<<(destination[destination.size() - 1] == '/' ? "" : "/");
			for (PathTokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
				std::wstring token = *it;
				if (lastToken.length() != 0) {
					_wmkdir(lastToken.c_str());
					_wchdir(lastToken.c_str());
					ss<<lastToken<<L"/";
				}
				lastToken = token;
			}
			ss<<lastToken;
		}
		lastExtractPath = ss.str();
		if (info->decompressedSize > 0) {
			char *decompressionBuffer = new char[info->decompressedSize];
			int result = compressor.decompress((char *)decompressionBuffer, (char *)alloc, info->fileSize, info->decompressedSize);
			if (result > 0) {
				*fileSize = info->decompressedSize;
				delete[] alloc;
				alloc = decompressionBuffer;
			}
		} else {
			*fileSize = info->fileSize;
		}

		input.close();
		_wchdir(cwd);
		return alloc;
	}
	return 0;
}