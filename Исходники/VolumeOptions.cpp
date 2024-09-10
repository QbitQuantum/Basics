std::tuple<std::string, std::string, unsigned long> ntfs::VolOps::getVolInfo()
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	wchar_t			volNameBuf[MAX_PATH + 1] = { 0 };
	wchar_t			fsNameBuf[MAX_PATH + 1] = { 0 };
	std::string		volName;
	std::string		fsName;
	unsigned long	maxCompLen = 0;
	unsigned long	serial = 0;
	unsigned long	fsFlags = 0;

	if (!GetVolumeInformationByHandleW(vhandle.get(), volNameBuf, MAX_PATH, &serial, &maxCompLen, &fsFlags, fsNameBuf, MAX_PATH)) {
		throw VOL_API_INTERACTION_LASTERROR("Unable to query volume information!");
	}
	volName = conv.to_bytes(volNameBuf);
	fsName = conv.to_bytes(fsNameBuf);

	return std::make_tuple(volName, fsName, maxCompLen);
}