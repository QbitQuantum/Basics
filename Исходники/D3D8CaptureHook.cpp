//Todo Support It
//Don't Support D3D8 Game In Xp And Vista
bool h3d::BeginD3D8CaptureHook() {

	wchar_t sD3D8Path[MAX_PATH];
	SHGetFolderPathW(NULL, CSIDL_SYSTEM, NULL, SHGFP_TYPE_CURRENT, sD3D8Path);
	wcscat_s(sD3D8Path, MAX_PATH, L"\\D3D8.dll");

	HMODULE hD3D8Dll = GetModuleHandle(sD3D8Path);
	if (hD3D8Dll) {
		PTR addr = reinterpret_cast<PTR>(hD3D8Dll);
		PTR end_sceneoffset = 0;

		UINT version = GetOSVersion();

		if (version == 7)
			end_sceneoffset = 0x44530;
		if (version >= 8)
			end_sceneoffset = 0x33540;

		if (end_sceneoffset) {
			d3d8end_scene.Do((WINAPIPROC)(addr + end_sceneoffset), (WINAPIPROC)EndScne);
			return true;
		}
	}

	return false;
}