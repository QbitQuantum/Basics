UINT fileManage::getVolume(WCHAR* volumePathName, UINT num) const {
	HANDLE findHandle = NULL;
	DWORD charCount = MAX_PATH+1;
	WCHAR volumeName[MAX_PATH+1];
	WCHAR deviceName[MAX_PATH+1];
	DWORD index = 0;
	UINT result = 0;
	UINT count = 0;

	findHandle = FindFirstVolume(volumeName, ARRAYSIZE(volumeName));
	if(INVALID_HANDLE_VALUE==findHandle) return 0;
	while(TRUE) {
		index = wcslen(volumeName)-1;
		volumeName[index] = L'\0';
		result = QueryDosDevice(&volumeName[4], deviceName, ARRAYSIZE(deviceName));
		volumeName[index] = L'\\';

		if(ERROR_INSUFFICIENT_BUFFER==result || 0==result) {
			result = 0;
			break;
		}
		result = retrieveDevName(deviceName);
		if(!result) {
			size_t temp = wcslen(volumePathName);
			if(volumePathName[temp]==L'\0') result=1;
			break;
		}
		result = GetVolumePathNamesForVolumeName(volumeName, volumePathName, charCount, &charCount);
		if(result) {
			if(count++==num) {
				size_t temp = wcslen(volumePathName);
				if(volumePathName[temp]==L'\0') result=1;
				break;
			}
			result = FindNextVolume(findHandle, volumeName, ARRAYSIZE(volumeName));
		}
	}

	FindVolumeClose(findHandle);
	findHandle = INVALID_HANDLE_VALUE;
	return result;
}