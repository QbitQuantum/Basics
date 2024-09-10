HRESULT CSecurityInformation::SetSecurity(
			SECURITY_INFORMATION SecurityInformation,
			PSECURITY_DESCRIPTOR pSecurityDescriptor)
{
	HRESULT hr = 1;

	// Get the Dacl
	PACL pDACL = NULL;
	BOOL fPresent, fDefaulted;
	GetSecurityDescriptorDacl(pSecurityDescriptor, &fPresent, &pDACL, &fDefaulted);

	// Get the SACL
	PACL pSACL = NULL;
	GetSecurityDescriptorSacl(pSecurityDescriptor, &fPresent, &pSACL, &fDefaulted);

	// Get the owner
	PSID psidOwner = NULL;
	GetSecurityDescriptorOwner(pSecurityDescriptor, &psidOwner, &fDefaulted);

	// Get the group
	PSID psidGroup = NULL;
	GetSecurityDescriptorOwner(pSecurityDescriptor, &psidGroup, &fDefaulted);

	// Find out if DACL and SACL inherit from parent objects
	SECURITY_DESCRIPTOR_CONTROL sdCtrl = NULL;
	ULONG ulRevision;
	GetSecurityDescriptorControl(pSecurityDescriptor, &sdCtrl, &ulRevision);

	if ((sdCtrl & SE_DACL_PROTECTED) != SE_DACL_PROTECTED)
		SecurityInformation  |= UNPROTECTED_DACL_SECURITY_INFORMATION;
	else
		SecurityInformation  |= PROTECTED_DACL_SECURITY_INFORMATION;

	if ((sdCtrl & SE_SACL_PROTECTED) != SE_SACL_PROTECTED)
		SecurityInformation  |= UNPROTECTED_SACL_SECURITY_INFORMATION;
	else
		SecurityInformation  |= PROTECTED_SACL_SECURITY_INFORMATION;

	// Set the security
	ULONG lErr;
	if (m_Info.m_szName[0] != 0) // Is it named
	{
		lErr = SetNamedSecurityInfo(m_Info.m_szName, 
					m_Type.m_objSecurType, SecurityInformation, psidOwner, 
					psidGroup, pDACL, pSACL);
	}
	else
	{
		// Is it a handle case
		lErr = SetSecurityInfo(m_Info.m_hHandle, m_Type.m_objSecurType,
					SecurityInformation, psidOwner, psidGroup, pDACL, pSACL);
	}

	// Report error
	if (lErr != ERROR_SUCCESS)
	{
		MessageBox(NULL,
			TEXT("An error occurred saving security information for this object,\n")
			TEXT("possibly due to insufficient access rights.\n"),
			TEXT("Security Notice"), MB_OK);
	}
	else
	{
		hr = S_OK;
	}

	return(hr);
}