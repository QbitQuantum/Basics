std::wstring CVarManager::getWinUser()
{
	wchar_t username[255] = {0};
#ifdef WIN32
	DWORD size = 255;
	GetUserNameW(username, &size);
#endif
	return username;
}