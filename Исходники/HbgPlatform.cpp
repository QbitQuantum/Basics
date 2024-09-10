BOOL HbgScanHex2byte(const std::wstring& text, WORD& value)
{
	WORD tmpVal = 0;
	if (swscanf_s(text.c_str(), HbgFmtValStr_2byte, &tmpVal) > 0) {
		value = tmpVal;
		return TRUE;
	}

	return FALSE;
}