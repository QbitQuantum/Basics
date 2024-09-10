string GetSpecialPath(KNOWNFOLDERID kfid) {
	PWSTR res = nullptr;
	string result;
	if (SHGetKnownFolderPath(kfid, 0, nullptr, &res) == S_OK) {
		result = str::u16string(res);
	}
	if (res)
		::CoTaskMemFree(res);
	return result;
}