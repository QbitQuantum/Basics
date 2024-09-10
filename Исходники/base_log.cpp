std::string GetCurrentModuleName() {
	std::string name;
	char buffer[MAX_PATH];
	HMODULE hModule = NULL;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, 
		(LPCSTR)&GetCurrentModuleName, //这是函数名，强转
		&hModule);
	DWORD len = GetModuleFileNameA(hModule, buffer, MAX_PATH);
	if (len) {
		name =  PathHelp::_base_get_noext_name(buffer);
	}
	return name;
}