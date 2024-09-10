LONG OverrideClassesRoot(HKEY hKeyBase, LPCWSTR szOverrideKey)
{
	HKEY hKey;
	LONG l = RegOpenKey(hKeyBase, szOverrideKey, &hKey);
	
	if (l == ERROR_SUCCESS)
	{
		l = RegOverridePredefKey(HKEY_CLASSES_ROOT, hKey);

		RegCloseKey(hKey);
	}

	return l;
}