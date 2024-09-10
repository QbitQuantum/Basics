void checkPinned() {
	if (!Dlls::PropVariantToString) return;

	static const int maxFileLen = MAX_PATH * 10;

	HRESULT hr = CoInitialize(0);
	if (!SUCCEEDED(hr)) return;

	QString path = pinnedPath();
	std::wstring p = QDir::toNativeSeparators(path).toStdWString();

	WCHAR src[MAX_PATH];
	GetModuleFileName(GetModuleHandle(0), src, MAX_PATH);
	BY_HANDLE_FILE_INFORMATION srcinfo = { 0 };
	HANDLE srcfile = CreateFile(src, 0x00, 0x00, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (srcfile == INVALID_HANDLE_VALUE) return;
	BOOL srcres = GetFileInformationByHandle(srcfile, &srcinfo);
	CloseHandle(srcfile);
	if (!srcres) return;
	LOG(("Checking..."));
	WIN32_FIND_DATA findData;
	HANDLE findHandle = FindFirstFileEx((p + L"*").c_str(), FindExInfoStandard, &findData, FindExSearchNameMatch, 0, 0);
	if (findHandle == INVALID_HANDLE_VALUE) {
		LOG(("Init Error: could not find files in pinned folder"));
		return;
	}
	do {
		std::wstring fname = p + findData.cFileName;
		LOG(("Checking %1").arg(QString::fromStdWString(fname)));
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			continue;
		} else {
			DWORD attributes = GetFileAttributes(fname.c_str());
			if (attributes >= 0xFFFFFFF) continue; // file does not exist

			ComPtr<IShellLink> shellLink;
			HRESULT hr = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shellLink));
			if (!SUCCEEDED(hr)) continue;

			ComPtr<IPersistFile> persistFile;
			hr = shellLink.As(&persistFile);
			if (!SUCCEEDED(hr)) continue;

			hr = persistFile->Load(fname.c_str(), STGM_READWRITE);
			if (!SUCCEEDED(hr)) continue;

			WCHAR dst[MAX_PATH];
			hr = shellLink->GetPath(dst, MAX_PATH, 0, 0);
			if (!SUCCEEDED(hr)) continue;

			BY_HANDLE_FILE_INFORMATION dstinfo = { 0 };
			HANDLE dstfile = CreateFile(dst, 0x00, 0x00, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (dstfile == INVALID_HANDLE_VALUE) continue;
			BOOL dstres = GetFileInformationByHandle(dstfile, &dstinfo);
			CloseHandle(dstfile);
			if (!dstres) continue;

			if (srcinfo.dwVolumeSerialNumber == dstinfo.dwVolumeSerialNumber && srcinfo.nFileIndexLow == dstinfo.nFileIndexLow && srcinfo.nFileIndexHigh == dstinfo.nFileIndexHigh) {
				ComPtr<IPropertyStore> propertyStore;
				hr = shellLink.As(&propertyStore);
				if (!SUCCEEDED(hr)) return;

				PROPVARIANT appIdPropVar;
				hr = propertyStore->GetValue(getKey(), &appIdPropVar);
				if (!SUCCEEDED(hr)) return;
				LOG(("Reading..."));
				WCHAR already[MAX_PATH];
				hr = Dlls::PropVariantToString(appIdPropVar, already, MAX_PATH);
				if (SUCCEEDED(hr)) {
					if (std::wstring(getId()) == already) {
						LOG(("Already!"));
						PropVariantClear(&appIdPropVar);
						return;
					}
				}
				if (appIdPropVar.vt != VT_EMPTY) {
					PropVariantClear(&appIdPropVar);
					return;
				}
				PropVariantClear(&appIdPropVar);

				hr = InitPropVariantFromString(getId(), &appIdPropVar);
				if (!SUCCEEDED(hr)) return;

				hr = propertyStore->SetValue(getKey(), appIdPropVar);
				PropVariantClear(&appIdPropVar);
				if (!SUCCEEDED(hr)) return;

				hr = propertyStore->Commit();
				if (!SUCCEEDED(hr)) return;

				if (persistFile->IsDirty() == S_OK) {
					persistFile->Save(fname.c_str(), TRUE);
				}
				return;
			}
		}
	} while (FindNextFile(findHandle, &findData));
	DWORD errorCode = GetLastError();
	if (errorCode && errorCode != ERROR_NO_MORE_FILES) { // everything is found
		LOG(("Init Error: could not find some files in pinned folder"));
		return;
	}
	FindClose(findHandle);
}