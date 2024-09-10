wstring ConnectedShortcut::disconnectFileName(const wstring& shortcutName)
{
	const wstring suffix = L" + " SHORT_APP_NAME L".lnk";
	if (PathMatchSpec(shortcutName.data(), (L"*" + suffix).data()) == FALSE)
		return shortcutName;

	wstring newName = shortcutName;
	newName.erase(newName.length() - suffix.length());
	newName.append(L".lnk");
	return newName;
}