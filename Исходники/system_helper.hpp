			PVOID built(PSECURITY_DESCRIPTOR pSD) 
			{
				PSID   psidEveryone = NULL;
				PACL   pDACL   = NULL;
				BOOL   bResult = FALSE;

				__try 
				{
					SID_IDENTIFIER_AUTHORITY siaWorld = SECURITY_WORLD_SID_AUTHORITY;
					//SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;

					if (!::InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
						__leave;

					if (!::AllocateAndInitializeSid(&siaWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &psidEveryone)) 
						__leave;

					DWORD dwAclLength = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + GetLengthSid(psidEveryone);

					pDACL = (PACL)::HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwAclLength);
					if (!pDACL) 
						__leave;

					if (!::InitializeAcl(pDACL, dwAclLength, ACL_REVISION)) 
						__leave;

					if (!::AddAccessAllowedAce(pDACL, ACL_REVISION, GENERIC_ALL, psidEveryone)) 
						__leave;

					if (!::SetSecurityDescriptorDacl(pSD, TRUE, pDACL, FALSE)) 
						__leave;
					bResult = TRUE;
				} 
				__finally 
				{
					if (psidEveryone) 
						::FreeSid(psidEveryone);
				}

				if (bResult == FALSE) 
				{
					if (pDACL) ::HeapFree(::GetProcessHeap(), 0, pDACL);
					pDACL = NULL;
				}

				return (PVOID) pDACL;
			}