bool Engine::check_record(USN_RECORD * record, std::wstring s_filename)
{
	WCHAR * filename;
	WCHAR * filenameend;

	filename = (WCHAR *)(((BYTE *)record) + record->FileNameOffset);
	filenameend = (WCHAR *)(((BYTE *)record) + record->FileNameOffset + record->FileNameLength);

	if (filenameend - filename != 8) return FALSE;

	int buffer = s_filename.length();
	const wchar_t * wc_filename = s_filename.c_str();

	if (wcsncmp(filename, wc_filename, buffer) != 0) return FALSE;

	//show_record(record);
	return TRUE;
}