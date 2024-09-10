std::string PathImpl::systemImpl()
{
	Buffer<wchar_t> buffer(MAX_PATH_LEN);
	DWORD n = GetSystemDirectoryW(buffer.begin(), static_cast<DWORD>(buffer.size()));
	if (n > 0)
	{
		n = GetLongPathNameW(buffer.begin(), buffer.begin(), static_cast<DWORD>(buffer.size()));
		if (n <= 0) throw SystemException("Cannot get system directory long path name");
		std::string result;
		UnicodeConverter::toUTF8(buffer.begin(), result);
		if (result[result.size() - 1] != '\\') result.append("\\");
		return result;
	}
	throw SystemException("Cannot get system directory path");
}