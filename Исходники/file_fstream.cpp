bool File::OpenTemporaryFile(const std::wstring &dir)
{
	return Open(tmpnam(NULL), MODE_TEMP);
} 