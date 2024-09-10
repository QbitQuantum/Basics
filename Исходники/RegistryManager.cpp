void takeOwnership(HKEY root, LPCTSTR subkey, Persona &admin)
{
	//RegSetKeySecurity(NULL,NULL,NULL);
	SECURITY_INFORMATION setOwner = OWNER_SECURITY_INFORMATION;
	HKEY hkey;
	DWORD psdsize = 1;

	LONG err = RegOpenKeyEx(root, subkey, 0, KEY_ALL_ACCESS /*KEY_READ*/, &hkey);

	if(err == 0 && hkey != 0) {
		BOOL ownerDefaulted = 0;

		// first call gets the %$#@ size!
		RegGetKeySecurity(hkey, OWNER_SECURITY_INFORMATION, NULL, &psdsize); 

		PSECURITY_DESCRIPTOR psd = LocalAlloc(LMEM_FIXED, psdsize);
		RegGetKeySecurity(hkey, OWNER_SECURITY_INFORMATION, psd, &psdsize); 
		SetSecurityDescriptorOwner(psd, admin.getSid(), 0);
		RegSetKeySecurity(hkey, setOwner, psd);
		LocalFree(psd);
	}
	else
		displayError(err, subkey);
}