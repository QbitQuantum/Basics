int Mutex_Create(PVOID pVoid, const char *szName)
{
	PMUTEX pMutex;
#if FIX_NAMED_OBJECT_NAMESPACE
    char szFixedUpNameBuffer[255] = {0};
#endif
    const char* lpszFixedObjectName = szName;
    LPSECURITY_ATTRIBUTES pSecurityAttributes = 0;

    SECURITY_DESCRIPTOR secDesc = {0};
    SECURITY_ATTRIBUTES attr = {0};
    PSECURITY_DESCRIPTOR pSD = NULL;

	if(!pVoid)
		return ERROR_INVALID_ARGUMENT;

	pMutex = (PMUTEX)pVoid;
	if(pMutex->hMutex != NULL)
		return SUCCESS;
  
    //if this is a named object then we are going to open up the permissions on it
    //so people in other accounts / sessions can also use the same shared named object.
    //Starting w/ vista services and the logged in users are no longer in the same session anymore aswell.
    if(szName)
    {
#if FIX_SECURITY_DACL
        if(InitializeSecurityDescriptor(&secDesc,SECURITY_DESCRIPTOR_REVISION))
        {
            //Give a NULL DACL for all access to everyone
            if(SetSecurityDescriptorDacl(&secDesc, TRUE, NULL, FALSE))
            {
                attr.nLength = sizeof(attr);
                attr.lpSecurityDescriptor = &secDesc;
                pSecurityAttributes = &attr;

                //Vista introduces "integrity" check levels.  We are going to set this to "low"
                //to prevent us from locking out a low-integrity process if someone in 
                //a service uses the api to open the mutex first.
                if(IsVistaOrBetter())
                {
                    if(ConvertStringSecurityDescriptorToSecurityDescriptor( "S:(ML;;NW;;;LW)", // "low integrity"
                        SDDL_REVISION_1,
                        &pSD,
                        NULL))
                    {
                        PACL pSacl = NULL;                  // not allocated
                        BOOL fSaclPresent = FALSE;
                        BOOL fSaclDefaulted = FALSE;
                        GetSecurityDescriptorSacl(
                            pSD,
                            &fSaclPresent,
                            &pSacl,
                            &fSaclDefaulted);
                        //Set the SACL w/ low-integrity checks
                        SetSecurityDescriptorSacl(attr.lpSecurityDescriptor, TRUE, pSacl, FALSE);
                    }
                }
            }
        }
#endif        

#if FIX_NAMED_OBJECT_NAMESPACE
        //now fix up the namespace on the object...
        strcat(szFixedUpNameBuffer,"Global\\");
        strcat(szFixedUpNameBuffer,szName);
        lpszFixedObjectName = szFixedUpNameBuffer;
#endif
    }

	/* Create a mutex with specified params */
	pMutex->hMutex = CreateMutex(	
							pSecurityAttributes,
							FALSE,
							lpszFixedObjectName
						);

    //local free if needed
    if(pSD)
    {
        //preserve last error
        DWORD dwLastError = GetLastError();
        LocalFree((HLOCAL)pSD);
        SetLastError(dwLastError);
    }

	if(pMutex->hMutex == NULL)
		return ERROR_CREATE_MUTEX_FAILED;
	return SUCCESS;
}