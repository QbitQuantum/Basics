NDASVOL_LINKAGE
HRESULT
NDASVOL_CALL
NdasIsNdasPathW(
	__in LPCWSTR FilePath)
{
	HRESULT hr;

	if (IsBadStringPtrW(FilePath, UINT_PTR(-1)))
	{
		return E_INVALIDARG;
	}

	XTLTRACE2(NdasVolTrace, 4, "NdasIsNdasPathW(%ls)\n", FilePath);

	LPWSTR mountPoint;
	hr = pGetVolumeMountPointForPathW(FilePath, &mountPoint);

	if (FAILED(hr))
	{
		XTLTRACE2(NdasVolTrace, TRACE_LEVEL_ERROR, 
			"pGetVolumeMountPointForPath(%ls) failed, hr=0x%X\n", 
			FilePath, hr);
		return hr;
	}

	XTL::AutoProcessHeapPtr<WCHAR> mountPointPtr = mountPoint;

	LPWSTR deviceName;
	hr = pGetVolumeDeviceNameForMountPointW(mountPoint, &deviceName);

	if (FAILED(hr))
	{
		XTLTRACE2(NdasVolTrace, TRACE_LEVEL_ERROR, 
			"pGetVolumeDeviceNameForMountPoint(%ls) failed, hr=0x%X\n", 
			mountPoint, hr);
		return hr;
	}

	XTL::AutoProcessHeapPtr<TCHAR> deviceNamePtr = deviceName;

	// Volume is a \\.\C:
	XTL::AutoFileHandle volumeHandle = CreateFileW(
		deviceName,
		GENERIC_READ, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		0,
		NULL);

	if (INVALID_HANDLE_VALUE == static_cast<HANDLE>(volumeHandle))
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		XTLTRACE2(NdasVolTrace, TRACE_LEVEL_ERROR,
			"CreateFile failed, path=%ls, hr=0x%X\n",
			deviceName, hr);
		return hr;
	}

	return NdasIsNdasVolume(volumeHandle);
}