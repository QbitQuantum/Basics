/*
 * GetSD: Accessor function for SecurityDescriptor
 *        Creates an (absolute) SD from the GetACL return value
 */
PSECURITY_DESCRIPTOR
vncAccessControl::GetSD(){
	PSECURITY_DESCRIPTOR pSD;
	PSECURITY_DESCRIPTOR pSelfRelativeSD;
	PACL pACL = NULL;
	DWORD dwBufferLength = 0;

	// If we can't retrieve a valid ACL we create an empty one (i.e. no access).
	if (!(pACL = GetACL()) || !IsValidAcl(pACL)) {
		pACL = (PACL) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,	sizeof(ACL));
		// Initialize the new ACL.
		if (!InitializeAcl(pACL, sizeof(ACL), ACL_REVISION)) {
			; // Todo: Report an error.
		}
	}

	// Construct SD
	pSD = HeapAlloc(GetProcessHeap(), 
		HEAP_ZERO_MEMORY, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if(InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION) &&
		// Set our ACL to the SD.
		SetSecurityDescriptorDacl(pSD, TRUE, pACL, FALSE) &&
		// AccessCheck() is picky about what is in the SD.
		SetSecurityDescriptorOwner(pSD, GetOwnerSID(), FALSE) &&
		SetSecurityDescriptorGroup(pSD, GetOwnerSID(), FALSE)) {
	} else {
		// Todo: Report an error.
	}
	// Make SD self-relative and use LocalAlloc
	MakeSelfRelativeSD(pSD, NULL, &dwBufferLength);
	pSelfRelativeSD = (PSECURITY_DESCRIPTOR) LocalAlloc(0, dwBufferLength);
	MakeSelfRelativeSD(pSD, pSelfRelativeSD, &dwBufferLength);
	FreeSD(pSD);
	return pSelfRelativeSD;
}