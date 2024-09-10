int EnumerateVolumes()
{
	HRESULT error;
    WCHAR volname[MAX_PATH+1];
	auto hFind = FindFirstVolume(volname, ARRAYSIZE(volname));
	if (hFind==INVALID_HANDLE_VALUE)
		return Usage(GetLastError(), L"FindFirstVolume() failed");
	while(true)
	{
		auto len = wcslen(volname);
		volname[len] = 0;
		auto v = new Volume();
		v->Init(volname, len);
		g_volumes.push_back(shared_ptr<Volume>(v));
		auto hasNext = FindNextVolume(hFind, volname, ARRAYSIZE(volname));
		if (hasNext)
			continue;
		error = GetLastError();
		if (error==ERROR_NO_MORE_FILES)
			error = 0;
		break;
	}
	FindVolumeClose(hFind);
	if (error!=0)
		return Usage(error, L"ProcessLv failed");
	return 0;
}