int MachineInstaller::PerformMachineInstallSetup()
{
	wchar_t packageName[512];

	if (!findPackageFromEmbeddedZip(packageName, sizeof(packageName))) {
		MessageBox(NULL, L"Corrupt installer", L"Cannot find package name for installer, is it created correctly?", MB_OK);
		return ERROR_INVALID_PARAMETER;
	}

	wchar_t machineInstallFolder[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_CURRENT, machineInstallFolder);
	wcscat(machineInstallFolder, L"\\SquirrelMachineInstalls");

	// NB: This is the DACL for Program Files
	wchar_t sddl[512] = L"D:PAI(A;;FA;;;S-1-5-80-956008885-3418522649-1831038044-1853292631-2271478464)(A;CIIO;GA;;;S-1-5-80-956008885-3418522649-1831038044-1853292631-2271478464)(A;;0x1301bf;;;SY)(A;OICIIO;GA;;;SY)(A;;0x1301bf;;;BA)(A;OICIIO;GA;;;BA)(A;;0x1200a9;;;BU)(A;OICIIO;GXGR;;;BU)(A;OICIIO;GA;;;CO)";

	if (IsWindows8OrGreater()) {
		// Add ALL APPLICATION PACKAGES account (Only available on Windows 8 and greater)
		wcscat(sddl, L"(A;;0x1200a9;;;AC)(A;OICIIO;GXGR;;;AC)");
	}

	PSECURITY_DESCRIPTOR descriptor;
	ConvertStringSecurityDescriptorToSecurityDescriptor(
		sddl,
		SDDL_REVISION_1,
		&descriptor, NULL);

	SECURITY_ATTRIBUTES attrs;
	attrs.nLength = sizeof(SECURITY_ATTRIBUTES);
	attrs.bInheritHandle = false;
	attrs.lpSecurityDescriptor = descriptor;

	if (!CreateDirectory(machineInstallFolder, &attrs) && GetLastError() != ERROR_ALREADY_EXISTS) {
		LocalFree(descriptor);
		return GetLastError();
	}

	LocalFree(descriptor);

	wcscat(machineInstallFolder, L"\\");
	wcscat(machineInstallFolder, packageName);
	wcscat(machineInstallFolder, L".exe");

	wchar_t ourFile[MAX_PATH];
	HMODULE hMod = GetModuleHandle(NULL);
	GetModuleFileName(hMod, ourFile, _countof(ourFile));

	if (!CopyFile(ourFile, machineInstallFolder, false)) {
		return GetLastError();
	}

	HKEY runKey;
	DWORD dontcare;
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &runKey, &dontcare) != ERROR_SUCCESS) {
		return GetLastError();
	}

	wcscat_s(machineInstallFolder, L" --checkInstall");

	if (RegSetValueEx(runKey, packageName, 0, REG_SZ, (BYTE*)machineInstallFolder, (wcsnlen(machineInstallFolder, sizeof(machineInstallFolder)) + 1) * sizeof(wchar_t)) != ERROR_SUCCESS) {
		return GetLastError();
	}

	RegCloseKey(runKey);
	return 0;
}