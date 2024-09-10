/**
 * Generates a new UID in outlook format. Format is described in VConverter::HrMakeBinaryUID
 *
 * @param[out]	lpStrData	returned generated UID string
 * @return		MAPI error code
 */
HRESULT HrGenerateUid(std::string *lpStrData)
{
	HRESULT hr = hrSuccess;
	std::string strByteArrayID = "040000008200E00074C5B7101A82E008";
	std::string strBinUid;
	GUID sGuid;
	FILETIME ftNow;
	ULONG ulSize = 1;

	hr = CoCreateGuid(&sGuid);
	if (hr != hrSuccess)
		goto exit;

	hr = UnixTimeToFileTime(time(NULL), &ftNow);
	if (hr != hrSuccess)
		goto exit;

	strBinUid = strByteArrayID;	// Outlook Guid
	strBinUid += "00000000";	// InstanceDate
	strBinUid += bin2hex(sizeof(FILETIME), (LPBYTE)&ftNow);
	strBinUid += "0000000000000000"; // Padding
	strBinUid += bin2hex(sizeof(ULONG), (LPBYTE)&ulSize); // always 1
	strBinUid += bin2hex(sizeof(GUID), (LPBYTE)&sGuid);	// new guid

	lpStrData->swap(strBinUid);

exit:
	return hr;
}