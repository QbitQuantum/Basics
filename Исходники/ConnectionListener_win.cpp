ConnectionListener::ConnectionListener(const std::wstring &name, TelldusCore::EventRef waitEvent)
{
	d = new PrivateData;
	d->hEvent = 0;

	d->running = true;
	d->waitEvent = waitEvent;
	d->pipename = L"\\\\.\\pipe\\" + name;

	PSECURITY_DESCRIPTOR pSD = NULL;
	PACL pACL = NULL;
	EXPLICIT_ACCESS ea;
	PSID pEveryoneSID = NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;

	pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH); 
	if (pSD == NULL) {
		return;
	} 
 
	if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) {  
		LocalFree(pSD);
		return;
	}

	if(!AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pEveryoneSID)) {
		LocalFree(pSD);
	}

	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
	ea.grfAccessPermissions = STANDARD_RIGHTS_ALL;
	ea.grfAccessMode = SET_ACCESS;
	ea.grfInheritance= NO_INHERITANCE;
	ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea.Trustee.ptstrName  = (LPTSTR) pEveryoneSID;

 
	// Add the ACL to the security descriptor. 
	if (!SetSecurityDescriptorDacl(pSD, 
				TRUE,     // bDaclPresent flag   
				pACL, 
				FALSE))   // not a default DACL 
	{  
		LocalFree(pSD);
		FreeSid(pEveryoneSID);
	}


	d->sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	d->sa.lpSecurityDescriptor = pSD;
	d->sa.bInheritHandle = false;

	start();
}