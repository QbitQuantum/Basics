int32_t C4Network2Res::OpenFileWrite()
{
	CStdLock FileLock(&FileCSec);
	// FIXME: Use standard OC file access api here
#ifdef _WIN32
	return _wopen(GetWideChar(szStandalone), _O_BINARY | O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
#else
	return open(szStandalone, _O_BINARY | O_CLOEXEC | O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
#endif
}