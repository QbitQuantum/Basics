AnsiString PathUtil::GetUserDirectory() {
	AnsiString userDir = "./";

#ifdef __WIN32__
	char buffer[MAX_PATH];
	buffer[0] = '\0';
	LPITEMIDLIST pidl = NULL;
	LPMALLOC pMalloc;
	if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
		SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidl);
		if (pidl) {
			SHGetPathFromIDList(pidl, buffer);
		}
		pMalloc->Free(pidl);
		userDir = AnsiString(buffer);
	}
#elif __MACOSX__
	FSRef fileRef;
	OSStatus error = FSFindFolder(kUserDomain, kApplicationSupportFolderType, true, &fileRef);
	if (error == noErr) {
		char buffer[MAX_PATH];
		error = FSRefMakePath(&fileRef, (UInt8 *)buffer, sizeof(buffer));
		if (error == noErr)
			userDir = buffer;

	}
#elif __IPHONEOS__
	char path[MAX_PATH];
	IOS_GetDataDir(path);
	userDir = AnsiString(path);
#endif

	return userDir;
}