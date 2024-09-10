std::string FxStringFromResource(void* module, const std::string& id, const std::string& type)
{
	HMODULE hModule = reinterpret_cast<HMODULE>(module);
	const int idValue = atoi(id.c_str());
	const char* idResource = MAKEINTRESOURCEA(idValue);
	HRSRC info = FindResourceA(hModule, idResource, type.c_str());
	if (NULL == info)
	{
		return string();
	}
	HGLOBAL handle = LoadResource(hModule, info);
	if (NULL == handle)
	{
		return string();
	}
	char* text = reinterpret_cast<char*>(LockResource(handle));
	DWORD size = SizeofResource(hModule, info);
	string result;
	try
	{
		result = string(text, text + size);
	}
	catch (const exception&)
	{
	}
	UnlockResource(handle);
	return result;
}