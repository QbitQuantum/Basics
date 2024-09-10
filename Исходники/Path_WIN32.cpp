std::string PathImpl::systemImpl()
{
	char buffer[MAX_PATH];
	DWORD n = GetSystemDirectoryA(buffer, sizeof(buffer));
	if (n > 0 && n < sizeof(buffer))
	{
		std::string result(buffer, n);
		if (result[n - 1] != '\\')
			result.append("\\");
		return result;
	}
	else throw SystemException("Cannot get system directory");
}