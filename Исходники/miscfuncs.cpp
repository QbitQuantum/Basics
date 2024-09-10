int CheckFiles(HANDLE hFile1, HANDLE hFile2)
{

	BY_HANDLE_FILE_INFORMATION info1;
	BY_HANDLE_FILE_INFORMATION info2;
    BOOL r1 = GetFileInformationByHandle(hFile1, &info1);
    BOOL r2 = GetFileInformationByHandle(hFile2, &info2);

	if (!r1 && !r2) {
		return 0;
	}
	else if (r1 && !r2) {
		return 1;
	}
	else if (!r1 && r2) {
		return -1;
	}

	if (info1.dwVolumeSerialNumber != info2.dwVolumeSerialNumber) {
		return info1.dwVolumeSerialNumber - info2.dwVolumeSerialNumber;
	}

	if (info1.nFileIndexHigh != info2.nFileIndexHigh) {
		return info1.nFileIndexHigh - info2.nFileIndexHigh;
	}
	return info1.nFileIndexLow - info2.nFileIndexLow;
}