//
// Function	: PrintPermissions
// Role		: Print and interpret the permissions for threads and processes
// Notes	: 
//
void PrintPermissions( HANDLE hObject, bool bDesktop)
{

	DWORD					dwRet=0;
	DWORD					dwCount=0;
	PACL					DACL;
	PSECURITY_DESCRIPTOR	PSD;
	ACCESS_ALLOWED_ACE		*ACE;
	
	// http://msdn2.microsoft.com/en-us/library/aa446654.aspx
	dwRet = GetSecurityInfo(hObject, 
							SE_WINDOW_OBJECT, 
							OWNER_SECURITY_INFORMATION|DACL_SECURITY_INFORMATION,
							NULL,
							NULL,
							&DACL,
							NULL,
							&PSD
	);

	if(hObject==NULL || hObject==INVALID_HANDLE_VALUE) return;

	if (dwRet!=ERROR_SUCCESS) 
	{
		DWORD dwError = GetLastError();
		fprintf(stderr,"[!] Error - %d %d - GetSecurityInfo\n", dwError,dwRet);
		return;
	} else {
		// http://msdn2.microsoft.com/en-us/library/aa379142.aspx
		if(IsValidAcl(DACL) == TRUE){

			// Now for each ACE in the DACL
			for(dwCount=0;dwCount<DACL->AceCount;dwCount++){
				// http://msdn2.microsoft.com/en-us/library/aa446634.aspx
				// http://msdn2.microsoft.com/en-us/library/aa379608.aspx
				if(GetAce(DACL,dwCount,(LPVOID*)&ACE)){
					// http://msdn2.microsoft.com/en-us/library/aa374892.aspx		
					SID *sSID = (SID*)&(ACE->SidStart);
					if(sSID != NULL)
					{
						DWORD dwSize = 2048;
						char lpName[2048];
						char lpDomain[2048];
						SID_NAME_USE SNU;
						
						switch(ACE->Header.AceType){

							// Allowed ACE
							case ACCESS_ALLOWED_ACE_TYPE:
								// Lookup the account name and print it.										
								// http://msdn2.microsoft.com/en-us/library/aa379554.aspx
								if( !LookupAccountSidA( NULL, sSID, lpName, &dwSize, lpDomain, &dwSize, &SNU ) ) {
									
									DWORD dwResult = GetLastError();
									if( dwResult == ERROR_NONE_MAPPED){
										fprintf(stdout,"[i]    |\n");
										fprintf(stdout,"[i]    +-+-> Allowed - NONMAPPED - SID %s\n", sidToText(sSID));
									} else if (dwResult != ERROR_NONE_MAPPED){
										fprintf(stderr,"[!] LookupAccountSid Error 	%u\n", GetLastError());
										fprintf(stdout,"[i]    |\n");
										fprintf(stdout,"[i]    +-+-> Allowed - ERROR     - SID %s\n", sidToText(sSID));
										//return;
									} else {
										continue;
									}
								} else {
									
									fprintf(stdout,"[i]    |\n");
									fprintf(stdout,"[i]    +-+-> Allowed - %s\\%s\n",lpDomain,lpName);
								}
								
								// print out the ACE mask
								fprintf(stdout,"[i]      |\n");
								fprintf(stdout,"[i]      +-> Permissions - ");
								
								if(!bDesktop){
						
									if(ACE->Mask & WINSTA_ALL_ACCESS) fprintf(stdout,",All");
									if(ACE->Mask & WINSTA_ACCESSCLIPBOARD ) fprintf(stdout,",Clipboard");
									if(ACE->Mask & WINSTA_ACCESSGLOBALATOMS ) fprintf(stdout,",Global Atoms");
									if(ACE->Mask & WINSTA_CREATEDESKTOP ) fprintf(stdout,",Create Desktop");
									if(ACE->Mask & WINSTA_ENUMDESKTOPS  ) fprintf(stdout,",Enum Desktop");
									if(ACE->Mask & WINSTA_ENUMERATE) fprintf(stdout,",Enumerate");
									if(ACE->Mask & WINSTA_EXITWINDOWS ) fprintf(stdout,",Exit Windows");
									if(ACE->Mask & WINSTA_READATTRIBUTES ) fprintf(stdout,",Read Attributes");
									if(ACE->Mask & WINSTA_READSCREEN ) fprintf(stdout,",Read Screen");
									if(ACE->Mask & WINSTA_WRITEATTRIBUTES ) fprintf(stdout,",Write Attributes");
									if(ACE->Mask & SYNCHRONIZE  ) fprintf(stdout,",Synchronize");
									if(ACE->Mask & DELETE) fprintf(stdout,",Delete");
									if(ACE->Mask & READ_CONTROL) fprintf(stdout,",Read Security");
									if(ACE->Mask & WRITE_OWNER) fprintf(stdout,",Change Owner");
									if(ACE->Mask & WRITE_DAC) fprintf(stdout,",Change Permissions");
									if(ACE->Mask & GENERIC_READ) fprintf(stdout,",Generic Read");
									if(ACE->Mask & GENERIC_WRITE ) fprintf(stdout,",Generic Write");
									if(ACE->Mask & GENERIC_EXECUTE) fprintf(stdout,",Generic Execute");
									if(ACE->Mask & GENERIC_ALL ) fprintf(stdout,",All");

								} else {
									if(ACE->Mask & DELETE ) fprintf(stdout,",Desktop Delete");
									if(ACE->Mask & READ_CONTROL ) fprintf(stdout,",Read Security Descriptor");
									if(ACE->Mask & DESKTOP_CREATEMENU ) fprintf(stdout,",Create Menu");
									if(ACE->Mask & DESKTOP_CREATEWINDOW ) fprintf(stdout,",Create Window");
									if(ACE->Mask & DESKTOP_ENUMERATE  ) fprintf(stdout,",Enumerate");
									if(ACE->Mask & DESKTOP_HOOKCONTROL) fprintf(stdout,",Hook Windows");
									if(ACE->Mask & DESKTOP_JOURNALPLAYBACK ) fprintf(stdout,",Journal Playpack");
									if(ACE->Mask & DESKTOP_JOURNALRECORD  ) fprintf(stdout,",Journal Record");
									if(ACE->Mask & DESKTOP_READOBJECTS) fprintf(stdout,",Read Objects");
									if(ACE->Mask & DESKTOP_SWITCHDESKTOP ) fprintf(stdout,",Switch Desktop");
									if(ACE->Mask & DESKTOP_WRITEOBJECTS) fprintf(stdout,",Write Objects");
									if(ACE->Mask & GENERIC_READ) fprintf(stdout,",Generic Read");
									if(ACE->Mask & GENERIC_WRITE ) fprintf(stdout,",Generic Write");
									if(ACE->Mask & GENERIC_EXECUTE) fprintf(stdout,",Generic Execute");
									if(ACE->Mask & GENERIC_ALL ) fprintf(stdout,",All");

								}
								fprintf(stdout,"\n");
								break;

							// Denied ACE
							case ACCESS_DENIED_ACE_TYPE:
								break;

							// Uh oh
							default:
								break;

						}
					}
				} else {
					DWORD dwError = GetLastError();
					fprintf(stderr,"[!] Error - %d - GetAce\n", dwError);
					return;
				}

			}
		} else {
			DWORD dwError = GetLastError();
			fprintf(stderr,"[!] Error - %d - IsValidAcl\n", dwError);
			return;
		}
	}

	LocalFree(PSD);

}