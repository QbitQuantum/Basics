		// SAS handling
		int  GinaChain::LoggedOutSAS(DWORD dwSasType, PLUID pAuthenticationId, PSID pLogonSid, PDWORD pdwOptions, 
									 PHANDLE phToken, PWLX_MPR_NOTIFY_INFO pMprNotifyInfo, PVOID *pProfile)
		{
			// If configured to pass through to MS GINA, or auto-logon is enabled, we 
			// pass through, and let the MS GINA handle the logon.
			if(m_passthru || IsAutoLogonEnabled())
			{
				return m_wrappedGina->LoggedOutSAS(dwSasType, pAuthenticationId, pLogonSid, pdwOptions, phToken, pMprNotifyInfo, pProfile);				
			}

			// We auth'd in another session - this session is the real one though, need to tell the service to add!
			if(dwSasType == WLX_SAS_TYPE_AUTHENTICATED)
			{
				// We could do this, but we don't get password (without additional wrapping of our own in WlxGetConsoleSwitchCredentials
				//  So instead we grab it post SAS processing via msgina.				
				WLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0 credInfo;
				if(m_winlogon->WlxQueryConsoleSwitchCredentials(&credInfo))
				{
					pDEBUG(L"LoggedOutSAS: CredInfo=%p PrivateDataLen: 0x%08x PrivateData: %p", &credInfo, credInfo.PrivateDataLen, credInfo.PrivateData);
				}				
				
				int msresult = m_wrappedGina->LoggedOutSAS(dwSasType, pAuthenticationId, pLogonSid, pdwOptions, phToken, pMprNotifyInfo, pProfile);
				//pGina::Transactions::LoginInfo::Add(pMprNotifyInfo->pszUserName, pMprNotifyInfo->pszDomain, pMprNotifyInfo->pszPassword);
				return msresult;
			}

			// Gather username/password from user.  If remote, we get it from rdp client if provided,
			//  otherwise show the logged out sas dialog to get it.
			std::wstring username;
			std::wstring password;
			std::wstring domain;
						
			bool showDialog = true;

			if(pGina::Helpers::UserIsRemote())
			{
				WLX_CLIENT_CREDENTIALS_INFO_V2_0 creds;
				creds.dwType = WLX_CREDENTIAL_TYPE_V2_0;				
				if(m_winlogon->WlxQueryTsLogonCredentials(&creds))
				{
					if(creds.pszUserName) username = creds.pszUserName;
					if(creds.pszPassword) password = creds.pszPassword;
					if(creds.pszDomain) domain = creds.pszDomain;
					if(!creds.fPromptForPassword) showDialog = false;

					pDEBUG(L"fPromptForPassword: %s", creds.fPromptForPassword ? L"TRUE" : L"FALSE");
					pDEBUG(L"fDisconnectOnLogonFailure: %s", creds.fDisconnectOnLogonFailure ? L"TRUE" : L"FALSE");
				}				
			}
			
			if(showDialog)
			{
				DialogLoggedOutSAS dialog(m_winlogon);						
				dialog.Username(username);
				dialog.Password(password);

				int dialogResult = dialog.ShowDialog();
				if(dialogResult == DialogLoggedOutSAS::SAS_ACTION_LOGON)
				{
					// Harvest u/p for passing along to msgina
					username = dialog.Username();
					password = dialog.Password();
				}
				else if(dialogResult >= DialogLoggedOutSAS::SAS_ACTION_MIN && dialogResult <= DialogLoggedOutSAS::SAS_ACTION_MAX)
				{
					// Just do as told
					return dialogResult;
				}
				else
				{
					// Unknown ret value, default to no action
					return DialogLoggedOutSAS::SAS_ACTION_NONE;
				}
			}

			// We now have the login info, let's give it a shot!
			pDEBUG(L"GinaChain::LoggedOutSAS: Processing login for %s", username.c_str());
			pGina::Transactions::User::LoginResult result = pGina::Transactions::User::ProcessLoginForUser(username.c_str(), NULL, password.c_str(), pGina::Protocol::LoginRequestMessage::Login);
			if(!result.Result())
			{
				std::wstring failureMsg = result.Message();
				pERROR(L"GinaChain::LoggedOutSAS: %s", failureMsg.c_str());
				m_winlogon->WlxMessageBox(NULL, const_cast<wchar_t *>(failureMsg.c_str()), L"Login Failure", MB_ICONEXCLAMATION | MB_OK);
				return WLX_SAS_ACTION_NONE;					
			}			

			pDEBUG(L"inaChain::LoggedOutSAS: Successful, resulting username: %s", result.Username().c_str());						

			// Invoke the msgina logged out sas dialog, intercept it, set username/password, and hit ok!
			HookedLoggedOutSAS::Enabled(true);
			HookedLoggedOutSAS::SetLoginInfo(result);
			int msresult = m_wrappedGina->LoggedOutSAS(dwSasType, pAuthenticationId, pLogonSid, pdwOptions, phToken, pMprNotifyInfo, pProfile);
			HookedLoggedOutSAS::Enabled(false);				
			return msresult;			
		}